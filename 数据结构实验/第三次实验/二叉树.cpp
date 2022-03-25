#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
 //����Ԫ�����Ͷ���
typedef int status;                                                    

typedef  struct {
	int key ;
	int value ;
} Elemtype;

typedef struct node{                                                    
    Elemtype data;
    struct node *lchild ,* rchild;
}Tnode,*Bitree;

typedef struct { 
	int  * elem;
	int length;;
}SqList;
 
 Tnode **T;
 Tnode *q,*c,*L1,*L2,*L3;
 int j=0,i=0,x=0,xx=0,res=0;
 int a[6];
//case 1 ��ʼ��������
status InitBiTree(Bitree   &T)
{ 
	T=(Bitree)malloc(sizeof(Tnode)) ;
	T->lchild=T->rchild=NULL;                                                                                 
	return OK;
}  
//case2 ���ٶ�����
status DestroyBiTree(Bitree  &T)
{
	if(T)
    {
        if((T)->lchild) 
            DestroyBiTree(T->lchild); 
        if((T)->rchild) 
            DestroyBiTree(T->rchild); 
        free(T); 
        T=NULL;
    }
	return OK;
}
//case3 ����������
status CreateBiTree(Bitree & T,int * p){                               
	
	if(*(p+xx)==-1) 
		 {xx++;
	  return OK;
	  }
		 T=(Bitree)malloc(sizeof(Tnode)) ;
	     T->lchild=T->rchild=NULL;      
	     T->data.key=*(p+xx);
		 xx++;
	     T->data.value=*(p+xx);
	     xx++;
		   CreateBiTree(T->lchild,(p));
	       CreateBiTree(T->rchild,(p));
		 return OK;
			
}
//case4 ��ն�����
status ClearBiTree(Bitree  T)
{                                                  
	 if(T)
    {
        if((T)->lchild) 
            DestroyBiTree(T->lchild); 
        if((T)->rchild) 
            DestroyBiTree(T->rchild); 
        free(T); 
        T=NULL;
    }
	T=(Bitree)malloc(sizeof(Tnode)) ; 
	T->lchild=T->rchild=NULL;     
	return OK;
}
//case 5 �ж϶������Ƿ�Ϊ��
status BiTreeEmpty(Bitree  T)
{                                             
	if((T)->lchild||T->rchild)
	return ERROR;
	else return OK;
}
//case 6 ����������
status BiTreeDepth(Bitree T,int j,int &x){                                 
	if(T)
	     {    j=j+1;                                    
              if(j>x)x=j;                                    
              BiTreeDepth(T->lchild,j,x);                
              BiTreeDepth(T->rchild,j,x);
          }
       return x;
}
//case7  ����ڵ�
status Root(Bitree  T)
{      printf("�ö������ĸ����ֵΪ:%d\n\n",T->data.value);
       return OK;                                                    
}
//case8  ��ڵ�
Tnode * Value(Bitree T,int e)
{   Tnode * t1;
    if(T==NULL)
		return NULL;
	if(T->data.key==e)
		return T;
	t1=Value(T->lchild,e);
	if(t1!=NULL)
		return t1;
	return Value (T->rchild,e);
}   
//case9  �ı�ڵ��ֵ
 status Assign(Bitree T,int e,int d)
{     if( Value(T,e)) 
           Value(T,e)->data.value=d;  return OK;
		   return ERROR;
} 
//case10 ��˫�׽ڵ�
Tnode * Parent(Bitree T,int e)
{   Tnode * t1;
    if(T)
	{
		if(T->data.key==e)return NULL;
	    else 
	    {
	 	    if(T->lchild!=NULL&&T->lchild->data.key==e||T->rchild!=NULL&&T->rchild->data.key==e)
	         return T;
		     else if (t1=Parent( T->lchild, e))return t1;
		     else if (t1=Parent( T->rchild, e))return t1;
	     }
	}
	return NULL;
}
//case11 �����ӽڵ�
Tnode * LeftChild(Bitree T,int e)
{   
	if(Value(T,e)==NULL) return NULL;
	else return Value(T,e)->lchild;
}
//case12 ���Һ��ӽڵ�
Tnode * RightChild(Bitree T,int e)
{   
	if(Value(T,e)==NULL) return NULL;
	else return Value(T,e)->rchild;
}
//case13 �����ֵ�
Tnode * LeftSibling(Bitree T,int e)
{   
	 if(Parent( T, e)&&Parent( T, e)->lchild)
	 {
		 if(Parent(T, e)->lchild->data.key == e)
			 return NULL;
		 return Parent( T, e)->lchild;
	 }

	else return NULL;
}
//case14 �����ֵ�
Tnode * RightSibling(Bitree T,int e)
{   if(Parent( T, e)&&Parent( T, e)->rchild)
	 {
		 if(Parent(T, e)->rchild->data.key == e)
			 return NULL;
		 return Parent( T, e)->rchild;
	 }

	else return NULL;
}
//case15  ��������
status InsertChild(Bitree T,int e,int LR,Bitree c)
{  if(Value(T,e))
         {
		  if(LR==0)
		  {
		         c->rchild=Value(T,e)->lchild;
		          Value(T,e)->lchild=c;
		  }
          if(LR==1)
		  {
		          c->rchild=Value(T,e)->rchild;
		           Value(T,e)->rchild=c;
		  }
          return OK;
          }
 else return ERROR;
}
//case16 ɾ������
status DeleteChild(Bitree T,int e ,int LR)
{  if(Value(T,e))
         {
		  if(LR==0&&Value(T,e)->lchild)DestroyBiTree(T->lchild);
          if(LR==1&&Value(T,e)->rchild)DestroyBiTree(T->rchild);
		return OK;
          }
           else return ERROR;
}
//case17 ǰ�����
status PreOrderTraverse(Bitree T)
{  if(T)
     {       printf("%d.%d ",T->data.key,T->data.value);
             PreOrderTraverse(T->lchild);
			 PreOrderTraverse(T->rchild);
			 return OK;
}
return ERROR;
}
//case18 �������
status InOrderTraverse(Bitree T)
{  if(T)
     {       InOrderTraverse(T->lchild);
		     printf("%d.%d ",T->data.key,T->data.value);
			 InOrderTraverse(T->rchild);
			 return OK;
}
return ERROR;
}
//case19 �������
status PostOrderTraverse(Bitree T)
{  if(T)
     {       PostOrderTraverse(T->lchild);
			 PostOrderTraverse(T->rchild);
			 printf("%d.%d ",T->data.key,T->data.value);
			 return OK;
}
return ERROR;
}
//case20 �������
status LevelOrderTraverse(Bitree T)
{     int i=0,n=0;
      Bitree temp[100],p;
	  temp[n]=T;
	  while(i<=n)
	  {p=temp[i];
	 printf("%d.%d ",p->data.key,p->data.value);
	 if(p->lchild)temp[++n]=p->lchild;
	 if(p->rchild)temp[++n]=p->rchild;
	 i++;
	  }
	  return OK;
}
//case 21 �ļ�����
status LoadToFile(Bitree T, char * filename,FILE *fp)
{   
	int a=-1;
	if(!T)
	{
		fwrite(&a, sizeof(int),1, fp);
		return 0;
	}
		fwrite(&(T->data.key), sizeof(int),1, fp);
		fwrite(&(T->data.value), sizeof(int), 1, fp);
		 LoadToFile( T->lchild, filename,fp);
	     LoadToFile( T->rchild, filename,fp);

	return 0;
}
//case 22 �ļ����
int LoadFromFile(Bitree & T, char * filename)                           
{   
	FILE * fp;
	SqList *L;
	L=NULL;
	L=(SqList *)malloc(  sizeof (int));
    L->elem = (int *)malloc( 100 * sizeof (int));
	L->length=0;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		
		printf("File open error!\n");
		return 1;
	}
	if(T->lchild||T->rchild)
		return 1;
	while (fread(&L->elem[L->length], sizeof(int), 1, fp))
	{
		L->length++;
	}
	fclose(fp);
	CreateBiTree(T,L->elem);
	return 0;
}
          
void main(void){ 
    int op=1,d=0;
    char filename[30];
	SqList *L;
	L=(SqList *)malloc(  sizeof (int));
          L->elem = (int *)malloc( 100 * sizeof (int));
          L->length=0;
	while(op){
	system("cls");	printf("\n\n");
	printf("      �������˵� \n");
	printf("-------------------------------------------------\n");
	printf("    	  1.InitBiTree              12. LeftChild\n");
	printf("    	  2. DestroyBitree        13. LeftSibling \n");
	printf("    	  3. CreateBitree        14. RightSibling\n");
	printf("    	  4. ClearBitree         15. InsertBitree\n");
	printf("    	  5. BiTreeEmpty         16. DeleteBitree\n");
	printf("    	  6. Depth           17. PreOrderTraverse\n");
	printf("    	  7. Root             18. InOrderTraverse\n");
	printf("    	  8. Value          19. PostOrderTraverse\n");
	printf("    	  9. Assign        20. LevelOrderTraverse\n");
	printf("    	  10. Parent               21. LoadToFile\n");
	printf("    	  11.LeftChild           22. LoadFromFile\n");
	printf("    	  23. ChangeBiTree                0. Exit\n");
	printf("-------------------------------------------------\n");	
	T=&L1;
	printf("    ��ѡ����Ĳ���[0~23]:");
		while (scanf("%d", &op) != 1 || (op < 0 || op > 23))
		{
			printf("�������������ѡ����Ĳ���[0~23]: ");	                         
			while (getchar() != '\n');
		}
 
    switch(op){
 //��ʼ��������
	   case 1:
		 if(InitBiTree(*T)==OK)
		 {
		 printf("��������ʼ���ɹ���\n"); a[d]=1;
		 }                                                                      
		     else printf("��������ʼ��ʧ�ܣ�\n");   
			
		 getchar();getchar();
		 break;
 //����������
	   case 2:
		 if(a[d]==0)
		     printf("�����������ڣ�\n"); 
		 else {
			 if(DestroyBiTree(*T)==OK)
			 { 
				 printf("���������ٳɹ���\n");  a[d]=0;
			 }                                                                   
		 else printf("����������ʧ�ܣ�\n"); 
		 }
		 getchar();getchar();
		 break;
//����������
	   case 3:
		 if(a[d]==0)
		     printf("�����������ڣ�\n"); 
		 else {xx=0;
          int *p,fl=0,n=0;
          p=L->elem+1;
		  printf("����Ҫ�����Ķ������ܱ����\n");
		  scanf("%d",&j);
          printf("����Ҫ�����Ķ�����\n");
		  while (n<j )
          { printf("�����%d����\n",n+1);
            scanf("%d",&fl);
	       *p=fl;
            p++;
			n++;
          }	
         if (CreateBiTree(*T,(L->elem+1))==OK)
		 {
		 printf("�����������ɹ���\n");
		 a[d]=1;
		 }                                                                          
		 else printf("����������ʧ�ܣ�\n");  }
		 getchar();getchar();
		 break;
//���������
	   case 4:
		  if(a[d]==0)
		     printf("�����������ڣ�\n");                                             
		   else 
			 {
			 if(ClearBiTree(*T)==OK)
			 { 
				 printf("��������ճɹ���\n"); a[d]=2;
			 }                                                                    
		    else printf("���������ʧ�ܣ�\n"); 
		     }
		 getchar();getchar();
		 break;
//�ж��������Ƿ�Ϊ��
	   case 5:
		 if(a[d]==0)
		     printf("�����������ڣ�\n");                                       
		   else 
		   {
			if(   BiTreeEmpty(*T)==OK)  printf("������Ϊ�գ�\n");
			else printf("��������Ϊ�գ�\n");
		   }
		 getchar();getchar();
		 break;
 //������������
	   case 6:      
		 if(a[d]==0){
		     printf("�����������ڣ�\n"); 
			 getchar();getchar();
		 }
		 else  if(a[d]==2){
		     printf("������Ϊ�գ�\n");  
			 getchar();getchar();
		 }
		 else{
         printf("%d\n",BiTreeDepth(*T,0,x));                                         
		getchar();getchar();
		 }
		 break;
//��������ĸ��ڵ�
	   case 7:
		 if(a[d]==0){
		     printf("�����������ڣ�\n");  
			 getchar();getchar();
		 }
		 else if(a[d]==2){
		     printf("������Ϊ�գ�\n");  
			 getchar();getchar();
		  }
			 else   {
				 Root( *T)      ;                                         
		         getchar();getchar();
			 }
		 break;
//��ýڵ�
	   case 8:
		   int e;
		  if(a[d]==0){
		     printf("�����������ڣ�\n");  
			 getchar();getchar();
		  }
		  else if(a[d]==2){
		     printf("������Ϊ�գ�\n");  
			 getchar();getchar();
		   }
		 else  {
			 printf("����һ��ֵ\n"); 
		        scanf("%d",&e);
		 if(Value(*T,e)) {
			 printf("�ýڵ��ֵΪ%d ",Value(*T,e)->data.value); 
			 getchar();getchar();
		 }
		 else{
			 printf("�޸ýڵ�");  
		 getchar();getchar();
		 } 
		 }
		 break;
//�ڵ㸳ֵ
	   case 9:
		  if(a[d]==0) {                                                           
		     printf("�����������ڣ�\n"); 
			 getchar();getchar();
		  }
		  else if(a[d]==2){
		     printf("������Ϊ�գ�\n"); 
			  getchar();getchar();
		  }
		   else {
		     int e,d;
		     printf("Ҫ�ı�ֵ�Ľڵ�\n"); 
		     scanf("%d",&e);
			 printf("Ҫ�ı��ֵ\n"); 
		     scanf("%d",&d);			 
		     if (Assign(*T,e,d)==OK) {
				 printf("��ֵ���");    
				  getchar();getchar();
		  }
		     else{
				 printf("û�ж�Ӧ�Ľڵ㣡\n"); 
			 getchar();getchar();
		    }
		   }
	
		 break;
//��˫�׽ڵ�
	   case 10:
		 if(a[d]==0){                                                              
		     printf("�����������ڣ�\n"); 
			  getchar();getchar();
		  }
		 else if(a[d]==2){
		     printf("������Ϊ�գ�\n");
			  getchar();getchar();
		  }
		   else
		   {
		 printf("Ҫ��ѯ��ֵ\n"); 
		 scanf("%d",&e);
		 if(e==1||Parent(*T,e)==NULL){
			 printf ("��ֵû��˫�׽ڵ�");
			  getchar();getchar();
		  }
		 else {  	
		 printf("Ҫ��ڵ��ֵΪ:%d",Parent(*T,e)->data.value);
		  getchar();getchar();
		  }
		}
		 break;
//�����ӽڵ�
	   case 11:
		 if(a[d]==0){                                                           
		     printf("�����������ڣ�\n"); 
			  getchar();getchar();
		  }
		 else  if(a[d]==2){
		     printf("������Ϊ�գ�\n");
			  getchar();getchar();
		  }
		   else{
			   printf("Ҫ��ѯ��ֵ\n"); 
		 scanf("%d",&e);
		 if(LeftChild(*T,e)==NULL){
			 printf ("��ֵû�����ӽڵ�");
			  getchar();getchar();
		  }
		 else {  	
		 printf("Ҫ��ڵ��ֵΪ:%d",LeftChild(*T,e)->data.value);
		  getchar();getchar();
		 }
		   }
		 break; 
//���Һ��ӽڵ�
	   case 12:  
	 if(a[d]==0) {                                                               
		     printf("�����������ڣ�\n");
			  getchar();getchar();
		  }
	 else  if(a[d]==2){
		     printf("������Ϊ�գ�\n"); 
			  getchar();getchar();
		  }
		   else{
			   printf("Ҫ��ѯ��ֵ\n"); 
		 scanf("%d",&e);
		if(RightChild(*T,e)==NULL){
			printf ("��ֵû���Һ��ӽڵ�");
			 getchar();getchar();
		  }
		 else {  	
		 printf("Ҫ��ڵ��ֵΪ:%d",RightChild(*T,e)->data.value);
		  getchar();getchar();
		 }
		   }
		 break; 
//�����ֵܽڵ�
		 case 13:
		 if(a[d]==0) {                                                            
		     printf("�����������ڣ�\n"); 
			  getchar();getchar();
		  }
		 else  if(a[d]==2){
		     printf("������Ϊ�գ�\n");  
			  getchar();getchar();
		  }
		   else
		   {
			   printf("Ҫ��ѯ��ֵ\n"); 
		 scanf("%d",&e);
		if(LeftSibling(*T,e)==NULL){
			printf ("��ֵû�����ֵܽڵ�");
			 getchar();getchar();
		  }
		 else {  	
		 printf("Ҫ��ڵ��ֵΪ:%d",LeftSibling(*T,e)->data.value);
		 getchar();getchar();
		 }
		  }
		 break; 
//�����ֵܽڵ�
		case 14:
		 if(a[d]==0) {                                                          
		     printf("�����������ڣ�\n"); 
			  getchar();getchar();
		  }
		 else if(a[d]==2){
		     printf("������Ϊ�գ�\n"); 
			  getchar();getchar();
		  }
		   else{
			   printf("Ҫ��ѯ��ֵ\n"); 
		 scanf("%d",&e);
		if(RightSibling(*T,e)==NULL){
			printf ("��ֵû�����ֵܽڵ�");
			 getchar();getchar();
		  }
		 else {  	
		 printf("Ҫ��ڵ��ֵΪ:%d",RightSibling(*T,e)->data.value);
		getchar();getchar();
		 }
		   }
		 break; 
//  ��������
          case 15:
		 if(a[d]==0) {                                                              
		     printf("�����������ڣ�\n");
			  getchar();getchar();
		  }
		 else if(a[d]==2){
		     printf("������Ϊ�գ�\n"); 
			  getchar();getchar();
		  }
		 else
		    {     int *p1,fl1=0,n1=0,LR;
		          Bitree T1;
				  T1=NULL;
          p1=L->elem+1;
		  printf("����Ҫ�������¶�������\n");
		  scanf("%d",&j);
          printf("����Ҫ�������¶�����\n");
		  while (n1<j )
          { printf("�����%d����\n",n1+1);
            scanf("%d",&fl1);
	       *p1=fl1;
            p1++;
			n1++;
          }	
		  xx=0;
         if (CreateBiTree(T1,(L->elem+1))==OK)	{ 
			 printf("�¶����������ɹ���\n"); 
		  getchar();getchar();
		  }
		 else {printf("�¶���������ʧ�ܣ�\n");
		  getchar();getchar();
		  }
		  printf("�������������Ľڵ�e\n");
		  scanf("%d",&e);
		 printf("������������Ϊ����������������LR(0 or 1 ��\n");
			scanf("%d",&LR);
			if(InsertChild(*T,e,LR,T1)==OK){
				printf("����ɹ�");
				 getchar();getchar();
		  }
			else{ printf("����ʧ��");
			 getchar();getchar();
		  }
		 }
		 break; 
// ɾ������
		case 16:
			 if(a[d]==0){                                                              
		     printf("�����������ڣ�\n"); 
			  getchar();getchar();
		  }
			 else  if(a[d]==2){
		     printf("������Ϊ�գ�\n"); 
			  getchar();getchar();
		  }
		 else {
			int LR;
			printf("���������ɾ���Ľڵ�e\n");
			scanf("%d",&e);
			printf("����ɾ��������Ϊ����������������LR(0 or 1 ��\n");
			scanf("%d",&LR);
			DeleteChild(*T,e,LR);
			if(DeleteChild(*T,e,LR)==OK){
				printf("ɾ���ɹ�");
				 getchar();getchar();
		  }
			else{
			 printf("ɾ��ʧ��");
			 getchar();getchar();
		  }
		 }
		 break; 
//ǰ�����
case 17:
			if(a[d]==0)   {                                                             
		     printf("�����������ڣ�\n"); 
			  getchar();getchar();
			 }
	    else if(a[d]==2){
		     printf("������Ϊ�գ�\n");  
			  getchar();getchar();
			 }
		 else{
		     PreOrderTraverse(*T);
			  getchar();getchar();
		 }
		 break; 
//�������
case 18:
		if(a[d]==0)   {                                                             
		     printf("�����������ڣ�\n"); 
			  getchar();getchar();
			 }
	    else if(a[d]==2){
		     printf("������Ϊ�գ�\n");  
			  getchar();getchar();
			 }
		 else{
		     InOrderTraverse(*T);
			  getchar();getchar();
		 }
		 break; 
//�������
case 19:
		 if(a[d]==0) {                                                           
		     printf("�����������ڣ�\n"); 
			 getchar();getchar();
			 }
		 else if(a[d]==2){
		     printf("������Ϊ�գ�\n");  
			 getchar();getchar();
			  }
		 else{
		     PostOrderTraverse(*T);
			  getchar();getchar();
		 }
		 break; 
//�������
case 20:
			if(a[d]==0)   {                                                             
		     printf("�����������ڣ�\n"); 
			  getchar();getchar();
			 }
	    else if(a[d]==2){
		     printf("������Ϊ�գ�\n");  
			  getchar();getchar();
			 }
		 else{
		     LevelOrderTraverse(*T);
			  getchar();getchar();
		 }
		 break;
//�ļ�����
case 21:
	 if(a[d]==0)                                                             
	printf("�����������ڣ�\n");
	  else if(a[d]==2)
	printf("������Ϊ�գ�\n");  

			else{   FILE * fp;  
				printf("input file name: ");
				scanf("%s", filename);
				if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("File open error!\n");
	}
				res = LoadToFile(*T, filename,fp);
				if (res == 0)
					printf("�ɹ�������ļ�!\n");
		
				else
					printf("�ļ���ʧ��!\n");
				 fclose(fp);
		
			}
	  getchar();getchar();
	 
			break;
//�����ļ�	
case 22:
			 if(a[d]==0)                                                           
		     printf("�����������ڣ�\n"); 
			 else if(a[d]==2)
		     printf("������Ϊ�գ�\n"); 
			 else { 
				printf("input file name: ");
				scanf("%s", filename);
				xx=0;
				res = LoadFromFile(*T, filename);
				if (res == 1)
					printf("���������Ѵ���Ԫ�أ�����պ��ٴ��ļ�����!\n");
		
				else
					printf("����ɹ�!\n");
		
			}
			 getchar();getchar();
			break;
case 23:
	printf("��������Ҫ�����Ķ�����[1~3]:");
	int m;
	scanf("%d",&m);
	if(m==1){
		T=&L1;
		d=1;
		printf("�л��ɹ���");
		getchar();getchar();
	}
	else if(m==2){
		T=&L2;
		d=2;
		printf("�л��ɹ���");
		getchar();getchar();

	}
	else if(m==3){
		T=&L3;
		d=3;
		printf("�л��ɹ���");
		getchar();getchar();
	}
	else{
		printf("�л�ʧ��!\n");
		getchar();getchar();
	}
	break;
	}//end of switch
  }//end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()