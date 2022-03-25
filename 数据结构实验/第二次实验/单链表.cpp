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
typedef struct Node{  //������Ķ���
	ElemType  elem;
	struct Node *next;
}Node,*pNode;
            

/*-----page 19 on textbook ---------*/
status IntiaList(pNode  &L);
status DestroyList(pNode & L);
status ClearList(pNode &L);
status ListEmpty(pNode L);
int ListLength(pNode L);
status GetElem(pNode  L,int seq,ElemType & e);
status LocateElem(pNode  L,ElemType e); //�򻯹�
status PriorElem(pNode L,ElemType cue,ElemType &pre);
status NextElem(pNode  L,ElemType cue,ElemType & next);
status ListInsert(pNode  & L,int seq,ElemType e);
status ListDelete(pNode & L,int seq,ElemType &e);
status ListTrabverse(pNode L);  //�򻯹�
status StoreInFile(pNode  L,char * filename);
status ReadFromFile(pNode & L,char * filename);
/*--------------------------------------------*/
int main(void){
  int op=1;
  pNode* L;
  pNode L1,L2,L3;
  L1=NULL;L2=NULL;L3=NULL;
  L=&L1;
  int seq,result;//seq��ʾ�����,result���ؽ����e�������뺯����ȡ���
  ElemType e,cue,pre,next;
  int Initial=0;//�ж������Ƿ���� 
  while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Linked Structure \n");
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
		 if(IntiaList(*L) == OK) {
			 printf("���������ɹ���\n");
			 Initial=1;
		     getchar();getchar();
		 }
		     else{
				 printf("��������ʧ�ܣ�\n");
		         getchar();getchar();
			 }
		 break;
	   case 2:
		   // printf("\n----DestroyList���ܴ�ʵ�֣�\n");  
		   if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
		  if(DestroyList(*L) == OK){
			   printf("���������ٳɹ���\n");
			   Initial=0;
			   getchar();getchar();
		  }
		  else {
			  printf("����������ʧ�ܣ�\n");
		      getchar();getchar();
		  }
		   }
		 break;
	   case 3: 
		   //printf("\n----ClearList���ܴ�ʵ�֣�\n");
		     if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
		  if(ClearList(*L) == OK){
			   printf("��������ճɹ�!\n");
			   getchar();getchar();
		  }
		   else {
			  printf("���������ʧ�ܣ�\n");
			  getchar();getchar();
		   }
		   }
		 break;
	   case 4:
		   //printf("\n----ListEmpty���ܴ�ʵ�֣�\n"); 
		     if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
		   if(ListEmpty(*L) == TRUE){
			   printf("����������գ�\n");
			   getchar();getchar();
		   }
		  else { 
			  printf("������δ��գ�\n");
		      getchar();getchar();
		  }
		   }
			  break;
	   case 5:
		   //printf("\n----ListLength���ܴ�ʵ�֣�\n");
		     if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }
		 else{
         printf("��������Ϊ%d\n",ListLength(*L));
		 getchar();getchar();
		}
		 break;
	   case 6:
		 //printf("\n----GetElem���ܴ�ʵ�֣�\n");
		     if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
		   printf("������Ҫ��ѯ��������");
		   scanf("%d",&seq);	
		      if( GetElem(*L,seq,e)==OK) {
			   printf("���еĵ�%d������Ϊ%d\n",seq,e);
			   getchar();getchar();}
			  else{
				  printf("��ѯʧ�ܣ�\n");
				  getchar();getchar();
			  }
		   }
		       break;
	   case 7:
		   //printf("\n----LocateElem���ܴ�ʵ�֣�\n");
		     if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
		   printf("������Ҫ��ѯ�����ݣ�");
		   scanf("%d",&e);
		   result=LocateElem(*L,e);
	    if(result!=ERROR){
		      printf("��һ����%d��ȵ�Ԫ�������%d\n",e,result);
			  getchar();getchar();}
		else {
			printf("����������Ԫ�ز����ڣ�\n");
			getchar();getchar();
		}
		   }
				   
		  
	
		 break;
	   case 8:
		//printf("\n----PriorElem���ܴ�ʵ�֣�\n");
		    if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
			   	 printf("������Ҫ��ѯ��Ԫ�أ�");
		         scanf("%d",&cue);
		   if(PriorElem(*L,cue,pre) == OK){
			   printf("ǰ��Ϊ%d\n",pre);
			   getchar();getchar();
		   }
		   else {
			   printf("�޴�ǰ��\n");
			   getchar();getchar();
		   }
		   }
		 break;
	   case 9:
		// printf("\n----NextElem���ܴ�ʵ�֣�\n"); 
		    if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
		   printf("������Ҫ��ѯ��Ԫ�أ�");
		   scanf("%d",&cue);
		   if(NextElem(*L,cue,next) == OK){
			   printf("���Ϊ%d\n",next);
			   getchar();getchar();
		   }
		   else if(NextElem(*L,cue,next) == FALSE){
			   printf("�޴˺��\n");
		       getchar();getchar();
		   }
		   else{
		    printf("����ʧ�ܣ�\n");
		    getchar();getchar();
		   }
		   }
		   break;
	     case 10:
		// printf("\n----ListInsert���ܴ�ʵ�֣�\n");
			  if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
		   printf("������Ҫ�����λ�ã�");
		   scanf("%d",&seq);
		   printf("������Ҫ�����Ԫ�أ�");
		   scanf("%d",&e);
		   if(ListInsert(*L,seq,e) == OK){
			   printf("���������ɹ�\n");
			   getchar();getchar();
		   }
		   else{
			   printf("���������ʧ��\n");
		       getchar();getchar();
		   }
		   }
		 break;
	   case 11:
		// printf("\n----ListDelete���ܴ�ʵ�֣�\n");
		    if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
		   printf("������Ҫɾ����Ԫ�ص����У�");
		   scanf("%d",&seq);
		   if(ListDelete(*L,seq,e) == OK){
			   printf("Ԫ��ɾ���ɹ�\n");
			   getchar();getchar();
		   }
		   else{
			   printf("Ԫ��ɾ��ʧ��\n");
		       getchar();getchar();
		   }
		   }
		 break;
	   case 12:
		 //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");     
		 if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
			   if(ListTrabverse(*L)==ERROR){
				   printf("����Ϊ�գ�\n");
			   }
			   getchar();getchar();
		   }
		 break;
		  case 13:
		    if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
              printf("input file name: ");
			  char filename[30];
				  scanf("%s",filename);//д�ļ��ķ��� 
             if(StoreInFile(*L,filename)==ERROR){
				 printf("д�����\n");
				 getchar();getchar();
			 }
			 else{
				 printf("д��ɹ���\n");
				 getchar();getchar();
			 }
		   }
		  	 break;
		   
	   case 14:
		    if(!Initial){
			   printf("���ȳ�ʼ����\n");
			   getchar();getchar();
		   }

		   else{
		   printf("input file name: ");
		   char filename[30];
           scanf("%s",filename);//д�ļ��ķ��� 
           if(ReadFromFile(*L,filename)==ERROR){
			   printf("����ʧ�ܣ�\n");
		       getchar();getchar();
		   }
		   else{
			   printf("����ɹ���\n");
			   getchar();getchar();
		   }
		   }
		   break;
         case 15:
			 int m;
			 printf("������Ҫ����������[1~3]��");
			 scanf("%d",&m);
			 if(m==1){
				 L=&L1;
				 printf("�л��ɹ���\n");
				 if(!L1)
				     Initial=0;
				 else
					 Initial=1;
				 getchar();getchar();
			 }
			 if(m==2){
				 L=&L2;
				 printf("�л��ɹ���\n");
				 if(!L2)
				     Initial=0;
				  else
					 Initial=1;
				 getchar();getchar();
			 }
			 if(m==3){
				 L=&L3;
				 printf("�л��ɹ���\n");
				 if(!L3)
				     Initial=0;
				  else
					 Initial=1;
				 getchar();getchar();
			 }
			 if(m<1||m>3){
				 printf("�л�ʧ�ܣ�\n");
				 getchar();getchar();
			 }
			 break;
	     case 0:
         break;
		 
		


   }//end of switch
  } //end of while
   printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()

/*--------page 23 on textbook --------------------*/
status IntiaList(pNode& L){
	L=(pNode)malloc(2*sizeof(pNode));
	L->elem=0;
	L->next=NULL;
	return OK;
}//��ʼ����
status DestroyList(pNode &L){
    pNode Lp;
	if(L->elem==0){
		free(L);
		return OK;
	}
	while(L->next!=NULL){
		Lp=L;
		L=L->next;
		free(Lp);
	}
	free(L);
	return OK;
}//���ٱ�
status ClearList(pNode & L){
	pNode Lp,Lq;
	if(L->elem==0)
		return ERROR;
	Lp=L->next;
	while(Lp->next!=NULL){
		Lq=Lp;
		Lp=Lp->next;
		free(Lq);
	}
	free(Lp);
	L->elem=0;
	return OK;
}//��ձ�
status ListEmpty(pNode L){
	
    if(L->elem == 0)
	return TRUE;
	else 
	return FALSE;
}//�ж��ձ�
int ListLength(pNode L){
	return L->elem;
} //���
status GetElem(pNode  L,int i,ElemType &e){
	if(i<1||i>L->elem)
		return ERROR;
	pNode Lp=L;
	int k;
	for(k=0;k<i;k++){
		Lp=Lp->next;
	}
	e=Lp->elem;
	return OK;
}//���Ԫ��
int LocateElem(pNode L,ElemType e){
	int k=0;
	pNode Lp=L->next;
	while(Lp!=NULL){
		k++;
		if(Lp->elem==e){
			return k;
		}
		Lp=Lp->next;
	}
	return ERROR;
}//����Ԫ��
status PriorElem(pNode L,ElemType cue,ElemType &pre){
	if(!L->elem){
		return FALSE;
	}
	int k=0;
	pNode Lp,Lq;
	Lp=L;
	while(Lp!=NULL){
		k++;
		Lq=Lp;
		Lp=Lp->next;
		if(Lp==NULL)
			return FALSE;
		if(cue==Lp->elem&&k!=1){
			pre=Lq->elem;
			return OK;
		}
	}
	return FALSE;
}//���ǰ��
status NextElem(pNode L,ElemType cue,ElemType &next){
	if(!L->elem)
		return FALSE;
	pNode Lp=L;
	while(Lp->next!=NULL){
		Lp=Lp->next;
		if(cue==Lp->elem){
			if(Lp->next==NULL)
				return ERROR;
			next=Lp->next->elem;
			return OK;}
	}
	return FALSE;
}//��ú��
status ListInsert(pNode &L,int i,ElemType e){
	if(i<1||i>L->elem+1)
		return ERROR;
	pNode p=L,q,newNode;
	newNode=(pNode)malloc(2*sizeof(pNode));
	newNode->elem=e;
	int k=0;
	while(p!=NULL&&k<i){
		q=p;
		p=p->next;
		k++;}
	q->next=newNode;
	newNode->next=p;
	L->elem=L->elem+1;
	return OK;
}//����Ԫ��
status ListDelete(pNode & L,int i,ElemType &e){
		if(i<1||i>L->elem)
			return ERROR;
		pNode p=L,q;
		int k=0;
		while(p!=NULL&&k<i-1){
			p=p->next;
			k++;
		}
		q=p->next;
		p->next=q->next;
		e=q->elem;
		free(q);
		L->elem=L->elem-1;
		return OK;
}//ɾ��Ԫ��
status ListTrabverse(pNode L){
	if(L->elem==0)
		return ERROR;
	pNode p=L->next;
	printf("\n-----------all elements -----------------------\n");
	while(p!=NULL){
		printf("%d ",p->elem);
		p=p->next;
	}
   printf("\n------------------ end ------------------------\n");
   return OK;
}//������
status StoreInFile(pNode L,char * filename){
	if(L->elem==0)
		return ERROR;
	pNode p=L->next;
	FILE *fp;
        if ((fp=fopen(filename,"wb"))==NULL){
	            printf("File open error\n ");
				return ERROR;
		}
		while(p!=NULL){
              fwrite(p,2*sizeof(pNode),1,fp);//������1����д�룬������������ṹ����ͨ�������������������Ԫ�ز�д�뵽�ļ���
			  p=p->next;
		}
              fclose(fp);
			  return OK;

}
status ReadFromFile(pNode &L,char * filename){
	ClearList(L);
	L->elem=0;
	pNode p=L;
	FILE *fp;
	  if ((fp=fopen(filename,"rb"))==NULL){
	       printf("File open error\n ");
		   return ERROR;
	    }
    Node temp;
	   while(fread(&temp,2*sizeof(pNode),1,fp)){
		   p->next=(pNode)malloc(2*sizeof(pNode));
		   p=p->next;
		   *p=temp;
		   L->elem++;
	   }
	   p->next=NULL;
	   fclose(fp);
		   return OK;
	
}