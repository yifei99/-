/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE -1
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct{  //˳���˳��ṹ���Ķ���
	ElemType * elem;
	int length;
	int listsize;
}SqList;
            

/*-----page 19 on textbook ---------*/
status IntiaList(SqList  *L);
status DestroyList(SqList * L);
status ClearList(SqList *L);
status ListEmpty(SqList* L);
int ListLength(SqList *L);
status GetElem(SqList *L,int i,ElemType & e);
status LocateElem(SqList *L,ElemType e); //�򻯹�
status PriorElem(SqList *L,ElemType cue,ElemType *pre);
status NextElem(SqList *L,ElemType cue,ElemType * next);
status ListInsert(SqList * L,int i,ElemType e);
status ListDelete(SqList * L,int i,ElemType * e);
status ListTrabverse(SqList *L);  //�򻯹�
int ReadFromFile(SqList * L,char * filename);
int StoreInFile(SqList * L,char * filename);


/*--------------------------------------------*/
int main(int argc, char *argv[]){

  SqList L1,L2,L3,*L=&L1;  int op=1;
  L1.elem=NULL;
  L2.elem=NULL;
  L3.elem=NULL;
  ElemType e;
  ElemType temp,*pre=&temp;
  ElemType temp1,*next=&temp1;
  ElemType cue;
  char filename[30];
  int i; 
  while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. IntiaList       7. LocateElem\n");
	printf("    	  2. DestroyList     8. PriorElem\n");
	printf("    	  3. ClearList       9. NextElem \n");
	printf("    	  4. ListEmpty     10. ListInsert\n");
	printf("    	  5. ListLength     11. ListDelete\n");
	printf("    	  6. GetElem       12. ListTrabverse\n");
	printf("          13.StoreInFile     14.ReadFromFile\n");
	printf("    	  15.ChangeList      0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~15]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 //printf("\n----IntiaList���ܴ�ʵ�֣�\n");
		 if(IntiaList(L) == OK) {
			 printf("���Ա����ɹ���\n");
		     getchar();getchar();
		 }
		     else{
				 printf("���Ա���ʧ�ܣ�\n");
		         getchar();getchar();
			 }
		 break;
	   case 2:
		   // printf("\n----DestroyList���ܴ�ʵ�֣�\n");     
		  if(DestroyList(L) == OK){
			   printf("���Ա����ٳɹ���\n");
			   getchar();getchar();
		  }
		  else {
			  printf("���Ա�����ʧ�ܣ�\n");
		      getchar();getchar();
		  }
		 break;
	   case 3: 
		   //printf("\n----ClearList���ܴ�ʵ�֣�\n");
		  if(ClearList(L) == OK){
			   printf("���Ա���ճɹ�!\n");
			   getchar();getchar();
		  }
		   else {
			  printf("���Ա����ʧ�ܣ�\n");
			  getchar();getchar();
		   }
		 break;
	   case 4:
		   //printf("\n----ListEmpty���ܴ�ʵ�֣�\n"); 
		   if(ListEmpty(L) == OK){
			   printf("���Ա�����գ�\n");
			   getchar();getchar();
		   }
		  else if(ListEmpty(L) ==FALSE){ 
			  printf("���Ա�δ��գ�\n");
		      getchar();getchar();
		  }
		  else if(ListEmpty(L)==ERROR){
			  printf("���Ա�δ��ʼ����\n");
		      getchar();getchar();
		  }
			  break;
	   case 5:
		   //printf("\n----ListLength���ܴ�ʵ�֣�\n");
		if( ListLength(L)!=ERROR){
         printf("���Ա���Ϊ%d\n",ListLength(L));
		 getchar();getchar();
		}
		else{
			printf("��ȡ����ʧ�ܣ�\n");
			getchar();getchar();
		}
		 break;
	   case 6:
		 //printf("\n----GetElem���ܴ�ʵ�֣�\n");
		   printf("������Ҫ��ѯ��������");
		   scanf("%d",&i);
		   if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)&&i<=L->length){
		       GetElem(L,i,e) ;
			   printf("���еĵ�%d������Ϊ%d\n",i,e);
			   getchar();getchar();
		   }
		   else{
			   printf("��ѯʧ�ܣ�\n");
		       getchar();getchar();
		   }
		 break;
	   case 7:
		   //printf("\n----LocateElem���ܴ�ʵ�֣�\n");
		   printf("������Ҫ��ѯ�����ݣ�");
		   scanf("%d",&e);
		   i=LocateElem(L,e);
		    if(i==FALSE) {
			   printf("����������Ԫ�ز����ڣ�\n");
		       getchar();getchar();
		   }
			else if(i==ERROR){
			   printf("��ѯʧ�ܣ�\n");
			   getchar();getchar();
		   }
		   else {
			   printf("L�е�һ�����ѯ������ȵ����ݵ�λ����%d\n",i);
			   getchar();getchar();
		   }
		 break;
	   case 8:
		//printf("\n----PriorElem���ܴ�ʵ�֣�\n");
	
		   if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
			   	 printf("������Ҫ��ѯ��Ԫ�أ�");
		         scanf("%d",&cue);
		   if(PriorElem(L,cue,pre) == OK){
			   printf("ǰ��Ϊ%d\n",*pre);
			   getchar();getchar();
		   }
		   else {
			   printf("�޴�ǰ��\n");
			   getchar();getchar();
		   }
		   }
		   else{
			   printf("��ѯʧ�ܣ�\n");
			   getchar();getchar();
		   }
		 break;
	   case 9:
		// printf("\n----NextElem���ܴ�ʵ�֣�\n"); 
		   printf("������Ҫ��ѯ��Ԫ�أ�");
		   scanf("%d",&cue);
		   if(NextElem(L,cue,next) == OK){
			   printf("���Ϊ%d\n",*next);
			   getchar();getchar();
		   }
		   else if(NextElem(L,cue,next) == FALSE){
			   printf("�޴˺��\n");
		       getchar();getchar();
		   }
		   else{
		    printf("����ʧ�ܣ�\n");
		    getchar();getchar();
		   }
		   break;
	     case 10:
		// printf("\n----ListInsert���ܴ�ʵ�֣�\n");
		   printf("������Ҫ�����λ�ã�");
		   scanf("%d",&i);
		   printf("������Ҫ�����Ԫ�أ�");
		   scanf("%d",&e);
		   if(ListInsert(L,i,e) == OK){
			   printf("���Ա����ɹ�\n");
			   getchar();getchar();
		   }
		   else{
			   printf("���Ա����ʧ��\n");
		       getchar();getchar();
		   }
		 break;
	   case 11:
		// printf("\n----ListDelete���ܴ�ʵ�֣�\n");
		   printf("������Ҫɾ����Ԫ�ص����У�");
		   scanf("%d",&i);
		   if(ListDelete(L,i,&e) == OK){
			   printf("Ԫ��ɾ���ɹ�\n");
			   getchar();getchar();
		   }
		   else{
			   printf("Ԫ��ɾ��ʧ��\n");
		       getchar();getchar();
		   }
		 break;
	   case 12:
		 //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");     
		 if(!ListTrabverse(L))
			 printf("���Ա��ǿձ�\n");
		 getchar();getchar();
		 break;
	   case 13:
		   if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
              printf("input file name: ");
              scanf("%s",filename);//д�ļ��ķ��� 
             if(StoreInFile(L,filename)==OK){
				 printf("д��ɹ���\n");
				 getchar();getchar();
			 }
			 else{
				 printf("д��ʧ�ܣ�\n");
				 getchar();getchar();
			 }
		   }
		   else{
			   printf("δ��ʼ����\n");
			   getchar();getchar();
		   }
			 break;
		   
	   case 14:
		   if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
		   printf("input file name: ");
           scanf("%s",filename);//д�ļ��ķ��� 
           if(ReadFromFile(L,filename)==OK){
			   printf("����ɹ���\n");
		       getchar();getchar();
		   }
		   else{
			   printf("����ʧ�ܣ�\n");
			   getchar();getchar();
		   }
		   }
		   else{
			   printf("δ��ʼ����\n");
			   getchar();getchar();
		   }
		   break;
	   case 15:
		   int m;
		   printf("��������Ҫ�����ı�[1-3]:");
		   scanf("%d",&m);
		   if(m==1){
			   L=&L1;
		      printf("�л��ɹ�\n");
		   getchar();getchar();
		   }
		   else if(m==2){
			   L=&L2;
		      printf("�л��ɹ�\n");
		   getchar();getchar();
		   }
		   else if(m==3){
			   L=&L3;
		   printf("�л��ɹ�\n");
		   getchar();getchar();
		   }
		   else {
			   printf("�л�ʧ�ܣ�\n");
				   getchar();getchar();
		   }
		   break;
	     case 0:
         break;
	}//end of switch
  }//end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");

}//end of main()
/*--------page 23 on textbook --------------------*/
status IntiaList(SqList * L){
	L->elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L->elem) 
		exit(OVERFLOW);
	L->length=0;
    L->listsize=LIST_INIT_SIZE;
	return OK;
}//��ʼ����
status DestroyList(SqList *L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	free(L->elem);
	L->elem = NULL;
	return OK;
	}
	else
		return ERROR;
}//���ٱ�
status ClearList(SqList* L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	L->length = 0;
	return OK;
	}
	else
		return ERROR;
}//��ձ�
status ListEmpty(SqList *L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
    if(L->length == 0)
	return TRUE;
	else 
	return FALSE;
	}
	else
		return ERROR;
}//�ж��ձ�
int ListLength(SqList *L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE))
	  return L->length;
	else
		return ERROR;
}//���
status GetElem(SqList* L,int i,ElemType &e){
	  e=*(L->elem+i-1);
	  return e;
}//���Ԫ��
int LocateElem(SqList *L,ElemType e){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	int k=1;
	while(*L->elem != e){
		L->elem++;
		k++;
		if(k >L->length){
			return FALSE;
		}
	}
	return k;
	}
	else
		return ERROR;
}//����Ԫ��
status PriorElem(SqList *L,ElemType cue,ElemType *pre){
	    int i;
        for(i=0;i<L->length;i++){
		if(L->elem[i] == cue){
			if(i==0)
				return FALSE;
			*pre=L->elem[i-1];
			return OK;
		}
		}
		return FALSE;
}//���ǰ��
status NextElem(SqList* L,ElemType cue,ElemType *next){
	int i;
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	for(i=0;i<L->length-1;i++){
		if(L->elem[i] == cue){
			if(i==L->length-1)
				return FALSE;
			*next = (int)L->elem[i+1];
			return OK;
		}
	}
	  return FALSE;
	}
	else
		return ERROR;
}//��ú��
status ListInsert(SqList *L,int i,ElemType e){
	ElemType *f,*t,*p;
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
	if(!L->elem)
		return ERROR;
	if(i<1||i>L->length+1)
		return ERROR;
	if(L->length >= L->length+1)
		return ERROR;
	if(L->length >= L->listsize){
		f = (ElemType *)realloc(L->elem,(L->listsize +LISTINCREMENT)*sizeof(ElemType));
		if(!f)
			return ERROR;
		L->elem = f;
		L->listsize += LISTINCREMENT;
	}
	t =&(L->elem[i-1]);
	for(p=&(L->elem[L->length-1]);p>=t;p--){
		*(p+1)=*p;
	}
	*t=e;
	++L->length;
	return OK;
	}
	else
		return ERROR;
}//����Ԫ��
status ListDelete(SqList *L,int i,ElemType*e){
	ElemType *t,*p;
	if(i<1||i>L->length||!L->elem)
		return ERROR;
	p=&(L->elem[i-1]);
	e=p;
	t=&(L->elem[L->length-1]);
	for(p++;p<=t;++p)
		*(p-1)=*p;
	--L->length;
	return OK;
}//ɾ��Ԫ��
status ListTrabverse(SqList *L){
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
   int i;
   printf("\n-----------all elements -----------------------\n");
   for(i=0;i<L->length;i++) printf("%d ",L->elem[i]);
   printf("\n------------------ end ------------------------\n");
   return L->length;
	}
	else
		return ERROR;
}//������
int StoreInFile(SqList *L,char * filename){
	FILE *fp;
	if (( L->elem!=NULL)&&( L->listsize>=LIST_INIT_SIZE)){
        if ((fp=fopen(filename,"w"))==NULL){
	            printf("File open error\n ");
		}
              fwrite(L->elem,sizeof(ElemType),L->length,fp);//������1����д�룬������������ṹ����ͨ�������������������Ԫ�ز�д�뵽�ļ���
              fclose(fp);
			  return OK;
	}
	else 
		return ERROR;

}
int ReadFromFile(SqList  *L,char * filename){
	L->length=0;
	FILE *fp;
	if (L->length<=LIST_INIT_SIZE){
  
	  if ((fp=fopen(filename,"r"))==NULL){
	       printf("File open error\n ");
		   return 1;
	    }
           while(fread(&(L->elem[L->length]),sizeof(ElemType),1,fp)){
           L->length++;//������ļ��������ȡ����Ԫ�ػָ�˳������ڲ�ͬ������ṹ����ͨ����ȡ������Ԫ�ػָ��ڴ��е�����ṹ��
		   }
           fclose(fp);
		   return OK;
	}
	
}
