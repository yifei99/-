// #include "def.h"
#include "semantic.h"

int LEV = 0;   //层号
int func_size; //1个函数的活动记录大小

void semantic_error(int line, char *msg1, char *msg2)
{
    // 这里可以只收集错误信息，最后在一次显示
    printf("在%d行,%s %s\n", line, msg1, msg2);
}

void prn_symbol()
{ //显示符号表
    int i = 0;
    char* symbolsType;
    printf("  %6s  %6s   %6s   %6s  %4s  %6s\n", "变量名", "别名", "层号", "类型", "标记", "偏移量");
    for (i = 0; i < symbolTable.index; i++)
    {
      if (symbolTable.symbols[i].type == INT)
      {
        symbolsType = "int";
      }
      if (symbolTable.symbols[i].type == FLOAT)
      {
        symbolsType = "float";
      }
      if (symbolTable.symbols[i].type == CHAR)
      {
        symbolsType = "char";
      }
      if (symbolTable.symbols[i].type == STRING)
      {
        symbolsType = "string";
      }
      printf("%6s %6s %6d  %6s %4c %6d\n", symbolTable.symbols[i].name,
               symbolTable.symbols[i].alias, symbolTable.symbols[i].level,
               symbolsType,
               symbolTable.symbols[i].flag, symbolTable.symbols[i].offset);
    }
}

int searchSymbolTable(char *name)
{
    int i;
    for (i = symbolTable.index - 1; i >= 0; i--)
        if (!strcmp(symbolTable.symbols[i].name, name))
            return i;
    return -1;
}

int fillSymbolTable(char *name, char *alias, int level, int type, char flag, int offset)
{ // 首先根据name查符号表，不能重复定义 重复定义返回-1

    int i;
    /*符号查重，考虑外部变量声明前有函数定义，
    其形参名还在符号表中，这时的外部变量与前函数的形参重名是允许的*/
    for (i = symbolTable.index - 1; symbolTable.symbols[i].level == level || (level == 0 && i >= 0); i--)
    {
        if (level == 0 && symbolTable.symbols[i].level == 1)
            continue; //外部变量和形参不必比较重名
        if (!strcmp(symbolTable.symbols[i].name, name))
            return -1;
    }
    //填写符号表内容
    strcpy(symbolTable.symbols[symbolTable.index].name, name);
    strcpy(symbolTable.symbols[symbolTable.index].alias, alias);
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
    return symbolTable.index++; //返回的是符号在符号表中的位置序号，中间代码生成时可用序号取到符号别名
}

//填写临时变量到符号表，返回临时变量在符号表中的位置
int fill_Temp(char *name, int level, int type, char flag, int offset)
{
    strcpy(symbolTable.symbols[symbolTable.index].name, "");
    strcpy(symbolTable.symbols[symbolTable.index].alias, name);
    symbolTable.symbols[symbolTable.index].level = level;
    symbolTable.symbols[symbolTable.index].type = type;
    symbolTable.symbols[symbolTable.index].flag = flag;
    symbolTable.symbols[symbolTable.index].offset = offset;
    return symbolTable.index++; //返回的是临时变量在符号表中的位置序号
}

int match_param(int i, struct node *T)
{ // 匹配函数参数
    int j, num = symbolTable.symbols[i].paramnum;
    int type1, type2;
    if (num == 0 && T == NULL)
        return 1;
    for (j = 1; j < num; j++)
    {
        if (!T)
        {
            semantic_error(T->pos, "", "函数调用参数太少");
            return 0;
        }
        type1 = symbolTable.symbols[i + j].type; //形参类型
        type2 = T->ptr[0]->type;
        if (type1 != type2)
        {
            semantic_error(T->pos, "", "参数类型不匹配");
            return 0;
        }
        T = T->ptr[1];
    }
    if (T->ptr[1])
    { //num个参数已经匹配完，还有实参表达式
        semantic_error(T->pos, "", "函数调用参数太多");
        return 0;
    }
    return 1;
}

void Exp(struct node *T)
{ //处理基本表达式，参考文献[2]p82的思想
    int rtn, num, width;
    struct node *T0;
    struct opn opn1, opn2, result;
    if (T)
    {
        switch (T->kind)
        {
        case ID: //查符号表，获得符号表中的位置，类型送type
            id_exp(T);
            break;
        case STRUCT_TAG: // TODO
            exp_struct_tag(T);
            break;
        case INT:
            int_exp(T);
            break;
        case FLOAT:
            float_exp(T);
            break;
        case CHAR:  // new
            char_exp(T);
            break;
        case STRING:  // TODO
            string_exp(T);
            break;
        case ASSIGNOP:
            assignop_exp(T);
            break;
        case PLUS_ONE: // TODO
        case MINUS_ONE:
        case ASSIGNOP_PLUS:
        case ASSIGNOP_MINUS:
        case ASSIGNOP_STAR:
        case ASSIGNOP_DIV:
            break;
        case AND:   //按算术表达式方式计算布尔值，未写完
        case OR:    //按算术表达式方式计算布尔值，未写完
        case RELOP: //按算术表达式方式计算布尔值，未写完
            relop_exp(T);
            break;
        case PLUS:
        case MINUS:
        case STAR:
        case DIV:
            op_exp(T);
            break;
        case NOT: //未写完整
            not_exp(T);
            break;
        case UMINUS: //未写完整
            // uminus_exp(T);
            break;
        case FUNC_CALL: //根据T->type_id查出函数的定义，如果语言中增加了实验教材的read，write需要单独处理一下
            func_call_exp(T);
            break;
        case ARGS: //此处仅处理各实参表达式的求值的代码序列，不生成ARG的实参系列
            args_exp(T);
            break;
        case EXP_ARRAY: // TODO
            exp_array(T);
            break;
        }
    }
}

void semantic_Analysis(struct node *T)
{ //对抽象语法树的先根遍历,按display的控制结构修改完成符号表管理和语义检查和TAC生成（语句部分）
    int rtn, num, width;
    struct node *T0;
    struct opn opn1, opn2, result;
    if (T)
    {
        switch (T->kind)
        {
        case EXT_DEF_LIST:
            ext_def_list(T);
            break;
        case EXT_VAR_DEF: //处理外部说明,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
            ext_var_def(T);
            break;
        case EXT_STRUCT_DEF: // TODO
            ext_struct_def(T);
            break;
        case STRUCT_DEF: // TODO
            struct_def(T);
            break;
        case STRUCT_DEC: // TODO
            struct_dec(T);
            break;
        case ARRAY_DEC:
            printf("array\n");
            array_dec(T);
            break;
        case FUNC_DEF:
            func_def(T);
            break;
        case FUNC_DEC: //根据返回类型，函数名填写符号表
            func_dec(T);
            break;
        case PARAM_LIST: //处理函数形式参数列表
            param_list(T);
            break;
        case PARAM_DEC:
            param_dec(T);
            break;
        case COMP_STM:
            comp_stm(T);
            break;
        case DEF_LIST:
            def_list(T);
            break;
        case VAR_DEF: //处理一个局部变量定义,将第一个孩子(TYPE结点)中的类型送到第二个孩子的类型域
                      //类似于上面的外部变量EXT_VAR_DEF，换了一种处理方法
            var_def(T);
            break;
        case STM_LIST:
            stm_list(T);
            break;
        case IF_THEN:
            if_then(T);
            break; //控制语句都还没有处理offset和width属性
        case IF_THEN_ELSE:
            if_then_else(T);
            break;
        case WHILE:
            while_dec(T);
            break;
        case EXP_STMT:
            exp_stmt(T);
            break;
        case RETURN:
            return_dec(T);
            break;
        case ID:
        case STRUCT_TAG:
        case INT:
        case FLOAT:
        case CHAR:
        case STRING:
        case ASSIGNOP:
        case AND:
        case OR:
        case RELOP:
        case PLUS:
        case PLUS_ONE:
        case ASSIGNOP_PLUS:
        case MINUS:
        case MINUS_ONE:
        case ASSIGNOP_MINUS:
        case STAR:
        case ASSIGNOP_STAR:
        case DIV:
        case ASSIGNOP_DIV:
        case NOT:
        case UMINUS:
        case FUNC_CALL:
        case EXP_ARRAY:
            Exp(T); //处理基本表达式
            break;
        }
    }
}

void semantic_Analysis0(struct node *T)
{
    symbolTable.index = 0;
    fillSymbolTable("read", "", 0, INT, 'F', 4);
    symbolTable.symbols[0].paramnum = 0; //read的形参个数
    fillSymbolTable("x", "", 1, INT, 'P', 12);
    fillSymbolTable("write", "", 0, INT, 'F', 4);
    symbolTable.symbols[2].paramnum = 1;
    symbol_scope_TX.TX[0] = 0; //外部变量在符号表中的起始序号为0
    symbol_scope_TX.top = 1;
    T->offset = 0; // 外部变量在数据区的偏移量
    semantic_Analysis(T);
    // prn_symbol();
    // 打印中间代码
    // printf("\n\n\n\n");
    // prnIR(T->code);
    // 生成目标代码
    objectCode(T->code);
}