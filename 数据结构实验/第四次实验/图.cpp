#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_CHAR 3
#define MAX_VERTEX_NUM 20

typedef int status;
typedef int InfoType;//����ص���Ϣ
typedef struct VertexType{
	char key[MAX_CHAR];
	int value;
	int isInit;
};
typedef enum{DG,DN}GraphKind;//{����ͼ��������}
typedef struct ArcNode{
	int adjvex;//�û�ָ��Ķ����λ��
	struct ArcNode *nextarc;//ָ����һ������ָ��
	InfoType *info;//�û������Ϣ��ָ��
};
typedef struct VNode{
	VertexType data;//������Ϣ
	ArcNode *firstarc;//ָ���һ�������ö���Ļ���ָ��
}List[MAX_VERTEX_NUM];
typedef struct Graph{
	List vertices;
	int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͻ���
	int type;//ͼ�������־
};
typedef int QElemType;
typedef struct QNode{
	QElemType data;
	struct QNode *next;
}*QueuePtr;
typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;
int visited[MAX_VERTEX_NUM];
int count=1;
status LocateVex(Graph G,VertexType elem);
status CreatGraph(Graph&G){//����ͼ
	int i,j;
	int weigh;//�ߵ�Ȩ
	VertexType vtail,vhead;
	int headloc,tailloc;
	ArcNode *cur,*last;
	printf("������Ҫ����ͼ�����ͣ�0������ͼ��/1������������");
	scanf("%d",&G.type);
	printf("������ͼ�Ķ�������");
	scanf("%d",&G.vexnum);
	printf("������ͼ�ı���:");
	scanf("%d",&G.arcnum);
	for(i=0;i<G.vexnum;i++){
		printf("�������%d�������ֵ:",i+1);
		scanf("%s",G.vertices[i].data.key);
		G.vertices[i].firstarc=NULL;
		G.vertices[i].data.isInit=0;
	}
	if(G.type==0){
		printf("����������ÿ�����Ļ�β�ͻ�ͷ���м��ûس�����\n");
	}
	else{
		printf("����������ÿ������Ȩֵ����β�ͻ�ͷ���м��ûس�����\n");
	}
		for(i=0;i<G.arcnum;i++){
			printf("���������%d�黡�Ĳ���\n",i+1);
			if(G.type==0){
				printf("�����뻡β���ַ�������");
				scanf("%s",vtail.key);
				printf("�����뻡ͷ���ַ�������");
				scanf("%s",vhead.key);
			}
			else{
				printf("�����뻡β���ַ�������");
				scanf("%s",vtail.key);
				printf("�����뻡ͷ���ַ�������");
				scanf("%s",vhead.key);
				printf("������Ȩֵ����������");
				scanf("%d",&weigh);
			}
			if((tailloc=LocateVex(G,vtail))==-1)
				return ERROR;
			if((headloc=LocateVex(G,vhead))==-1)
				return ERROR;
			cur=(ArcNode *)malloc(sizeof(ArcNode));
			cur->adjvex=headloc;
			if(G.type==0){
				cur->info=NULL;
			}
			else{
				cur->info=(int*)malloc(sizeof(int));
				*(cur->info)=weigh;
			}
			cur->nextarc=G.vertices[tailloc].firstarc;
			G.vertices[tailloc].firstarc=cur;
		}
		return OK;
}
status DestroyGraph(Graph&G){//����ͼ
	G.vexnum=0;
	G.arcnum=0;
	ArcNode *cur,*temp;
	int i;
	for(i=0;i<G.vexnum;++i){
		cur=G.vertices[i].firstarc;
		G.vertices[i].firstarc=NULL;
		while(cur!=NULL){
			temp=cur->nextarc;
			if(G.type==1){
				free(cur->info);
			}
			free(cur);
			cur=temp;
		}
	}
	return OK;
}
status LocateVex(Graph G,VertexType elem){//���Ҷ���
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(elem.key,G.vertices[i].data.key)==0){
			return i;
		}
	}
	return -1;
}
status GetVex(Graph G,VertexType elem,int &value){//��ý��ֵ
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(elem.key,G.vertices[i].data.key)==0){
			if(G.vertices[i].data.isInit==0){
				return INFEASIBLE;
			}
			else{
				value=G.vertices[i].data.value;
				return OK;
			}
		}
	}
	return FALSE;
}
status PutVex(Graph&G,VertexType elem,int value){//����㸳ֵ
	int i;
	for(i=0;i<=G.vexnum;i++){
		if(strcmp(elem.key,G.vertices[i].data.key)==0){
			G.vertices[i].data.isInit=1;
			G.vertices[i].data.value=value;
			return OK;
		}
	}
	return FALSE;
}
int FirstAdjVex(Graph G,VertexType elem){//��õ�һ���ڽӽ��
	int n;
	n=LocateVex(G,elem);
	if(n==-1)
		return -2;
	ArcNode *p=G.vertices[n].firstarc;
	if(p!=NULL){
		return p->adjvex;
	}
	else{
		return -1;
	}
}
int NextAdjVex(Graph G,VertexType elem,VertexType elem2){//�����һ���ڽӽ��
	int n,n2;
	n=LocateVex(G,elem);
	n2=LocateVex(G,elem2);
	if(n==-1||n2==-1)
		return -1;
	ArcNode *p=G.vertices[n].firstarc;
	if(p!=NULL){
		while(p){
			if(p->adjvex==n2){
				if(p->nextarc!=NULL){
					return p->nextarc->adjvex;
				}
				else{
					return -4;//�ý�㲻������һ�����
				}
			}
			p=p->nextarc;
		}
		return -3;//����elem����elem2����
	}
	else{
		return -2;//����elem�������ڽӽ��
	}
}
status InsertVex(Graph&G,VertexType elem){//���һ���¶���
	strcpy(G.vertices[G.vexnum].data.key,elem.key);
	G.vertices[G.vexnum].data.isInit=0;
	G.vertices[G.vexnum].firstarc=NULL;
	G.vexnum++;
	return OK;
}
status DeleteVex(Graph &G,VertexType elem){//ɾ��һ������Լ��������
	int n,i;
	ArcNode *temp,*q,*pretemp;
	n=LocateVex(G,elem);
	if(n==-1)
		return FALSE;
	temp=G.vertices[n].firstarc;
	while(temp!=NULL){
		q=temp;
		if(G.type==-1){
			free(temp->info);
		}
		temp=temp->nextarc;
		free(q);
		G.arcnum--;
	}
	for(i=n;i<G.vexnum-1;i++){
		G.vertices[i]=G.vertices[i+1];
	}
	G.vexnum--;
	for(i=0;i<G.vexnum;i++){
		temp=G.vertices[i].firstarc;
		if(temp!=NULL&&temp->adjvex==n){
			G.vertices[i].firstarc->nextarc=G.vertices[i].firstarc->nextarc->nextarc;
			if(G.type==1){
				free(temp->info);
			}
			free(temp);
			G.arcnum--;
		}
		else if(temp==NULL){
			G.arcnum=G.arcnum;
		}
		else{
			if(temp->adjvex>n){
				temp->adjvex--;
			}
			pretemp=temp;
			temp=temp->nextarc;
			while(temp!=NULL){
				q=temp;
				if(temp->adjvex>n){
					temp->adjvex--;
				}
				if(temp->adjvex==n){
					pretemp->nextarc=pretemp->nextarc->nextarc;
					temp=temp->nextarc;
					if(G.type==1){
						free(q->info);
					}
					free(q);
					G.arcnum--;
				}
				pretemp=pretemp->nextarc;
				temp=temp->nextarc;
			}
		}
	}
	return OK;
}
status InsertArc(Graph&G,VertexType elem,VertexType elem2){//c����һ���ڱ�
	int n,n2;
	n=LocateVex(G,elem);
	n2=LocateVex(G,elem2);
	if(n==-1||n2==-1)
		return ERROR;
	ArcNode *p;
	p=G.vertices[n].firstarc;
	while(p!=NULL){
		if(p->adjvex==n2){
			return -2;
		}
		p=p->nextarc;
	}
	ArcNode *temp;
	temp=(ArcNode *)malloc(sizeof(ArcNode));
	temp->adjvex=n2;
	if(G.type==1){
		temp->info=(int*)malloc(sizeof(int));
		int weigh;
		printf("\n���������ߵ�Ȩֵ:");
		scanf("%d",&weigh);
		*(temp->info)=weigh;
	}
	else if(G.type==0){
		temp->info=NULL;
	}
	temp->nextarc=G.vertices[n].firstarc;
	G.vertices[n].firstarc=temp;
	G.arcnum++;
	return OK;
}
status DeleteArc(Graph&G,VertexType elem,VertexType elem2){//ɾ��һ���ڱ�
	int n,n2;
	n=LocateVex(G,elem);
	n2=LocateVex(G,elem2);
	if(n==-1||n2==-1)
		return ERROR;
	ArcNode *p,*q,*temp;
	p=G.vertices[n].firstarc;
	int found=0;
	if(p==NULL)
		return ERROR;
	if(p->adjvex==n2){
		q=p;
		G.vertices[n].firstarc=p->nextarc;
		if(G.type==1){
			free(q->info);
		}
		found=1;
		free(q);
		G.arcnum--;
	}
	else{
		while(p!=NULL){
			q=p;
			p=p->nextarc;
			if(p->adjvex==n2){
				found=1;
				q->nextarc=p->nextarc;
				if(G.type==1){
					free(p->info);
				}
				free(p);
				break;
			}
		}
	}
	if(!found){
		return INFEASIBLE;
	}
	return OK;
}
void DFS(Graph G,int num){//������ȱ���
	ArcNode *temp;
	int t;
	printf("��%d�����Ϊ��%s\n",count,G.vertices[num].data.key);
	count++;
	visited[num]=TRUE;
	for(temp=G.vertices[num].firstarc;temp!=NULL;temp=temp->nextarc){
		t=temp->adjvex;
		if(visited[t]!=1)
			DFS(G,t);
	}
}
status DFSTraverse(Graph G){
	int i;
	for(i=0;i<G.vexnum;i++){
		visited[i]=FALSE;
	}
	for(i=0;i<G.vexnum;i++){
		if(visited[i]!=1)
			DFS(G,i);
	}
	return OK;
}
status InitQueue(LinkQueue &Q){
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front)
		exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}
status QueueEmpty(LinkQueue Q){
	if(Q.front==Q.rear)
		return TRUE;
	else
		return FALSE;
}
status EnQueue(LinkQueue &Q,QElemType e){
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)
		exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}
status DeQueue(LinkQueue &Q,QElemType &e){
	QueuePtr p;
	if(Q.front==Q.rear)
		return ERROR;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;
	free(p);
	return OK;
}
status BFSTraverse(Graph G,LinkQueue Q){
	int v,u;
	ArcNode *temp;
	for(v=0;v<G.vexnum;v++){
		visited[v]=FALSE;
	}
	for(v=0;v<G.vexnum;v++){
		if(!visited[v]){
			visited[v]=TRUE;
			printf("��%d�����Ϊ: %s\n",v+1,G.vertices[v].data.key);
			EnQueue(Q,v);
			while(!QueueEmpty(Q)){
				DeQueue(Q,u);
				for(temp=G.vertices[u].firstarc;temp!=NULL;temp=temp->nextarc){
					if(visited[temp->adjvex]!=1){
						visited[temp->adjvex]=TRUE;
						printf("��%d�����Ϊ��%s\n",++count,G.vertices[temp->adjvex].data.key);
						EnQueue(Q,temp->adjvex);
					}
				}
			}
		}
	}
	return OK;
}
status LoadToFile(Graph *G, char * filename)
{
	int i;
	int number = -1;
	ArcNode * node;
	FILE * fp = fopen(filename, "w");
	if (fp == NULL)
		return ERROR;		//file open error

	fwrite(&(G->vexnum), sizeof(int), 1, fp);
	fwrite(&(G->arcnum), sizeof(int), 1, fp);

	for (i = 0; i < G->arcnum; i++)
		fwrite(&(G->vertices[i].data), sizeof(VertexType), 1, fp);

	for (i = 0; i < G->vexnum; i++)
	{
		node = G->vertices[i].firstarc;
		while (node != NULL)
		{
			fwrite(&(node->adjvex), sizeof(int), 1, fp);
			fwrite(&(node->info), sizeof(int), 1, fp);
			node = node->nextarc;
		}
		fwrite(&number, sizeof(int), 1, fp);
		fwrite(&number, sizeof(int), 1, fp);
	}
	fclose(fp);
	return OK;
}

status LoadFromFile(Graph *G, char * filename)
{
	int i;
	ArcNode * node;
	ArcNode * tempnode;
	FILE * fp = fopen(filename, "r");
	if (fp == NULL)
		return ERROR;		//file open error

	fread(&(G->vexnum), sizeof(int), 1, fp);
	fread(&(G->arcnum), sizeof(int), 1, fp);
	for (i = 0; i < G->vexnum; i++)
		fread(&(G->vertices[i].data), sizeof(VertexType), 1, fp);

	for (i = 0; i < G->vexnum; i++)
	{
		tempnode = (ArcNode *)malloc(sizeof(ArcNode));
		fread(&(tempnode->adjvex), sizeof(int), 1, fp);
		fread(&(tempnode->info), sizeof(int), 1, fp);
		if (tempnode->adjvex == -1)
			G->vertices[i].firstarc = NULL;
		else
		{
			G->vertices[i].firstarc = tempnode;
			node = tempnode;
			while (1)
			{
				tempnode = (ArcNode *)malloc(sizeof(ArcNode));
				fread(&(tempnode->adjvex), sizeof(int), 1, fp);
				fread(&(tempnode->info), sizeof(int), 1, fp);
				if (tempnode->adjvex == -1)
				{
					node->nextarc = NULL;
					break;
				}
				node->nextarc = tempnode;
				node = node->nextarc;
			}
		}
	}
	fclose(fp);
	return OK;
}
int main(void){
  int reCreate=2;
  Graph *G;
  Graph G1,G2,G3;
  G1.vexnum=0;
  G2.vexnum=0;
  G3.vexnum=0;
  G=&G1;
  VertexType elem,elem2;
  VertexType insertElem;
  int value=0;
  int Initial=0;
  int i,j;
  QElemType e;
  LinkQueue Q;
  char filename[30];
  int op=1;
  while(op){
	system("cls");	printf("\n\n");
	printf("      ��  ��  ��  ��  ��  ��  ͼ  ��  ʾ  ϵ  ͳ \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateGraph       7. NextAdjVex\n");
	printf("    	  2. DestroyGraph      8. InsertVex\n");
	printf("    	  3. LocateVex         9. DeleteVex \n");
	printf("    	  4. GetVex            10. InsertArc\n");
	printf("    	  5. PutVex            11. DeleteArc\n");
	printf("    	  6. FirstAdjVex       12. DFSTrabverse\n");
	printf("    	  13.BFSTraverse       14. LoadToFile\n");
	printf("    	  15.LoadFromFile      16. ChangeGraph\n");
	printf("    	  0.exit\n");
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~13]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 if(Initial){
			 printf("ͼ�Ѵ������Ƿ񸲸ǣ���1/0--YES/NO��\n");
			 scanf("%d",&reCreate);
		 }
			 if(reCreate==0)
				 break;
			 if(CreatGraph(*G)==OK){
				 printf("�����ɹ���\n");
				 getchar();getchar();
				 Initial=1;
			 }
			 else{
				 printf("����ʧ��!\n");
				 getchar();getchar();
			 }
		 break;
	   case 2:
		   if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		   if(DestroyGraph(*G)==OK){
			   printf("���ٳɹ���\n");
			   Initial=0;
			   getchar();getchar();
		   }
		   else{
			   printf("����ʧ�ܣ�\n");
			   getchar();getchar();
		   }
		 break;
	   case 3:
		  if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		  printf("��������Ҫ���ҵĶ��㣺");
		  scanf("%s",elem.key);
		  if((i=LocateVex(*G,elem))>-1){
			  printf("�ý��λ���ڽӱ�ĵ�%d��������Ϊ%d\n",i+1,i);
		      getchar();getchar();
		  }
		  else{
			  printf("δ�ҵ��ö��㣡\n");
			  getchar();getchar();
		  }
		 break;
	   case 4:
		 if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		  printf("��������Ҫ���ҵĶ��㣺");
		  scanf("%s",elem.key);
		  if((i=GetVex(*G,elem,value))==OK){
			  printf("����%s��ֵΪ%d\n",elem.key,value);
			  getchar();getchar();
		  }
		  else if(i=INFEASIBLE){  
		    printf("�ö��㻹δ��ֵ��\n");
			getchar();getchar();
		  }
		  else if(i==FALSE){
			  printf("δ�ҵ��ö��㣡\n");
			  getchar();getchar();
		  }
		 break;
	   case 5:
		if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		printf("���������븳ֵ�Ķ��㣺");
		scanf("%s",elem.key);
		printf("��������Ҫ����ֵ��");
		scanf("%d",&value);
		if((i=PutVex(*G,elem,value))==OK){
			printf("��ֵ�ɹ�������%s��ֵΪ%d\n",elem.key,value);
		getchar();getchar();
		}
		else if(i==FALSE){
			printf("δ�ҵ��ö��㣡\n");
			getchar();getchar();
		}
		 break;
	   case 6:
		 if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		 printf("������������ҵĶ��㣺");
		 scanf("%s",elem.key);
		 if((i=FirstAdjVex(*G,elem))>=0){
			 printf("����%s���ڽӽ��Ϊ%s\n",elem.key,G->vertices[i].data.key);
			 getchar();getchar();
		 }
		 else if(i==-2){
			 printf("δ�ҵ��ý�㣡\n");
		 getchar();getchar();
		 }
		 else if(i==-1){
			 printf("�ý�����ڽӽ��\n");
			 getchar();getchar();
		 }
		 else{
			 printf("����ʧ�ܣ�\n");
			 getchar();getchar();
		 }

		 break;
	   case 7:
		  if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		 printf("������������ҵĶ��㣺");
		 scanf("%s",elem.key);
		 printf("��������ö���������һ�����㣺");
		 scanf("%s",elem2.key);
		 if((i=NextAdjVex(*G,elem,elem2))>=0){
			 printf("����ѯ�Ľ��Ϊ%s\n",G->vertices[i].data.key);
		 getchar();getchar();
		 }
		 else if(i==-1){
			 printf("δ�ҵ��ý�㣡\n");
		 getchar();getchar();
		 }
		 else if(i==-2){
			 printf("�ý�㲻�����ڽӽ�㣡\n");
			 getchar();getchar();
		 }
		 else if(i==-3){
			 printf("������Ķ���%s����%s����\n",elem2.key,elem.key);
			 getchar();getchar();
		 }
		 else if(i==-4){
			 printf("����%s��������һ�����\n",elem2.key);
			 getchar();getchar();
		 }			
		break;
	   case 8:
		 if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		 printf("�������������Ķ��㣺");
		 scanf("%s",insertElem.key);
		 if(InsertVex(*G,insertElem)==OK){
			 printf("����ɹ���\n");
			 getchar();getchar();
		 }
		 else{
			 printf("����ʧ�ܣ�\n");
			 getchar();getchar();
		 }
		 break;
	   case 9:
		 if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		 printf("����������ɾ���Ķ��㣺");
		 scanf("%s",elem.key);
		 if(DeleteVex(*G,elem)==OK){
			 printf("ɾ���ɹ���\n");
		     getchar();getchar();
		 }
		 else{
			 printf("ɾ��ʧ�ܣ�\n");
			 getchar();getchar();
		 }
		 break;
	   case 10:
		 if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		 printf("�������������ߵ�β���㣺");
		 scanf("%s",elem.key);
		 printf("�������������ߵ�ͷ���㣺");
		 scanf("%s",elem2.key);
		 if(InsertArc(*G,elem,elem2)==OK){
			 printf("����ɹ���\n");
			 getchar();getchar();
		 }
		 else{
			 printf("����ʧ�ܣ�\n");
			 getchar();getchar();
		 }
		 break;
	   case 11:
			 if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		 printf("����������ɾ�����Ļ�β���㣺");
		 scanf("%s",elem.key);
		 printf("����������ɾ�����Ļ�ͷ���㣺");
		 scanf("%s",elem2.key);
		 if(DeleteArc(*G,elem,elem2)==OK){
			 printf("ɾ���ɹ���\n");
			 getchar();getchar();
		 }
		 else{
			 printf("ɾ��ʧ�ܣ�\n");
			 getchar();getchar();
		 }
		 break;
	   case 12:
		 if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		 count=1;
		 DFSTraverse(*G);
		 getchar();getchar();
		 break;
	   case 13:
		   if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
		   InitQueue(Q);
		   count=1;
		   BFSTraverse(*G,Q);
		   getchar();getchar();
		   break;
		  case 14:
			 if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
			else
			{
				printf("������洢���ļ���: ");
				scanf("%s", filename);
				if (LoadToFile(G,filename) == ERROR){
					printf("�ļ���ʧ��!\n");
					getchar();getchar();
				}
				else{
					printf("�ɹ�������ļ�!\n");
					getchar();getchar();
			}
			 }
			break;
		case 15:
			 if(!Initial){
			   printf("���ȴ���ͼ��\n");
			   getchar();getchar();
			   break;
		   }
			 else{
				printf("�������ȡ���ļ���: ");
				scanf("%s", filename);
				if (LoadFromFile(G,filename) == ERROR){
					printf("�ļ���ʧ��!\n");
					getchar();getchar();
				}
				else{
					printf("�ɹ�����������!\n");
	            	getchar(); getchar();
				}
			 }
			break;
		case 16:
			int m;
			printf("���������������ͼ[1~3]:");
			scanf("%d",&m);
			if(m==1){
				G=&G1;
				if(G->vexnum==0){
					Initial=0;
				}
				else{
					Initial=1;
				}
				printf("�л��ɹ���\n");
				getchar();getchar();
			}
			else if(m==2){
				G=&G2;
				if(G->vexnum==0){
					Initial=0;
				}
				else{
					Initial=1;
				}
				printf("�л��ɹ���\n");
				getchar();getchar();
			}
			else if(m==3){
				G=&G3;
				if(G->vexnum==0){
					Initial=0;
				}
				else{
					Initial=1;
				}
				printf("�л��ɹ���\n");
				getchar();getchar();
			}
			else{
				printf("�л�ʧ�ܣ�\n");
				getchar();getchar();
			}
	   case 0:
         break;
	}//end of switch
  }//end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}//end of main()
