#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "DPLL.h"
int *f;
int tmin;
int sudo[81];
int main(){
	int op=1;
	int a;
	root head;
	clock_t start, end;
	double duration;
	char filename1[1000];
	char filename2[1000];
	//LoadinFile(filename1, &head);
	while(op){
	system("cls");	printf("\n\n");
	printf("-------------------------------------------------\n");
	printf("    	  1. LoadinFile       \n");
	printf("    	  2. DPLL1\n");
	printf("    	  3. DPLL2\n");
	printf("          4. LoadtoFile\n");
	printf("          5. Trans_sudoku\n");
	printf("          0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���:");
	scanf("%d",&op);
	switch(op){
	case 1:
	  printf("�������ļ���:");
	  scanf("%s",filename1);
	  LoadinFile(filename1, &head); 
	  printf("����ɹ�!\n");
	  getchar();getchar();
	  break;
	case 2:
	  start = clock();
	  if (a=DPLL1(&head))
		 printf("TRUE\n");
	  else
		 printf("FALSA\n");
	  end = clock();
	  duration = (double)(end - start) ;
	  printf("the DPLL uses %f ms\n", duration);
	  getchar();getchar();
	  break;
	case 3:
			  start = clock();
	  if (a=DPLL2(&head))
		 printf("TRUE\n");
	  else
		 printf("FALSA\n");
	  end = clock();
	  duration = (double)(end - start) ;
	  printf("the DPLL uses %f ms\n", duration);
	  getchar();getchar();
	  break;
	case 4:
       if (a == TRUE) {
		   int h;
		   printf("�Ƿ��ǲ���������y-1/n-0\n");
		   scanf("%d",&h);
		   if(h==0){
	   for (int t = 0; t < head.NumOfVari; t++) {
	 				printf("%2d %d\n", *(f + t),t+1);
				}
		   }
		   else if(h==1){
			   int d,o,l,k;
		        k=0;
			    d=0;
			for (int t = 0; t < head.NumOfVari; t++){
				if(*(f+t)==1){
					if((t+1)%9==0)
						sudo[d]=9;
					else
					sudo[d]=(t+1)%9;
					d++;
				}
			}
				for(o=0;o<19;o++){
			if(o%2==0){
			for(l=0;l<37;l++){
				if(l%4==0)
					printf("\033[;31m+\033[0m");
				else
					printf("\033[;33m-\033[0m");
			}
			printf("\n");
			}
			else{
				for(l=0;l<37;l++){
					if(l%4==0&&l!=36){
						printf("\033[;31m+\033[0m");	
						printf("\033[;;1m %d \033[0m",sudo[k]);
						k++;
					}	
					if(l==36)
						printf("\033[;31m+\033[0m");
		}
				printf("\n");
		}
		}
		   }
				printf("TRUE!\n");
				int length = strlen(filename1);
				filename1[length - 1] = 's';
				filename1[length - 2] = 'e';
				filename1[length - 3] = 'r';
				FILE *fp;
				if ((fp = fopen(filename1, "w")) == NULL) {
					printf("File open error!\n");
					break;
				}
				fprintf(fp, "s 1\n");
				fprintf(fp, "v");
				for (int t = 0; t < head.NumOfVari; t++) {
					if(*(f+t)==1)fprintf(fp," %d",t+1);
					else fprintf(fp, " %d", -t - 1);
				}
				fprintf(fp, "\n");
				fprintf(fp, "t %f ms\n", duration);
				fclose(fp);
			}
			else {
				printf("FALSE!\n");
				int length = strlen(filename1);
				filename1[length - 1] = 's';
				filename1[length - 2] = 'e';
				filename1[length - 3] = 'r';
				FILE *fp;
				if ((fp = fopen(filename1, "w")) == NULL) {
					printf("File open eror!\n");
					break;
				}
				fprintf(fp, "s 0\n");
				fprintf(fp, "v\n");
				fprintf(fp, "t %f ms\n", duration);
				fclose(fp);
			}
			printf("�����ɹ���\n");
			memset(f,0,sizeof(f));
			getchar();getchar();
		break;
	case 5:
		printf("�������ļ���:");
		scanf("%s",filename2);
		FILE *f2;
		f2=fopen(filename2,"r");
		if(f2==NULL){
			printf("wrong!\n");
			break;
		}
		int i,o,l,k;
		k=0;
		for(i=0;i<81;i++){
				sudo[i]=fgetc(f2)-48;
		}
		for(o=0;o<19;o++){
			if(o%2==0){
			for(l=0;l<37;l++){
				if(l%4==0)
					printf("\033[;31m+\033[0m");
				else
					printf("\033[;33m-\033[0m");
			}
			printf("\n");
			}
			else{
				for(l=0;l<37;l++){
					if(l%4==0&&l!=36){
						printf("\033[;31m+\033[0m");
						if(sudo[k]==0)
							printf("   ");
						else
						printf("\033[;;1m %d \033[0m",sudo[k]);
						k++;
					}	
					if(l==36)
						printf("\033[;31m+\033[0m");
		}
				printf("\n");
		}
		}
		transudo(filename2);
	getchar();getchar();
       break;
	case 0:
		break;
	return 0;
	}
	}
} 
int Destroy(Node2 *p, root *head){
	Node1 *temp1, *temp2;
	for (; p->pL != NULL;){
		for (temp1 = p->pL, temp2 = p->pL; temp1->next1 != NULL; temp1 = temp1->next1)
			temp2 = temp1;
		if (temp1 ==p->pL){
			p->pL = NULL;
			free(temp1);
		}
		else
		{
			free(temp1);
			temp2->next1 = NULL;
		}
	}
	free(p);
	head->NumOfClause--;
	return 0;
}//����һ���Ӿ�ָ�룬���ո��Ӿ估����������
int IsUnitClause(root head, int *Elem){
	int i;
	Node2 *temp2;
	for (temp2 = head.p, i = 1; temp2 != NULL; temp2 = temp2->next2, i++){
		if (temp2->pL->next1 == NULL)
		{
			*Elem = temp2->pL->Elem;
			return i;
		}
	}
	return i = 0;
}//����һ��cnf��ʽ����һ������ָ�룬���е��Ӿ��򷵻ص�һ�����Ӿ��λ�ú͸õ��Ӿ����ֵ�ֵ�����򷵻�0
int RemoveClause(root *head, int Elem){
	int i, j, k;//i��ʶ�Ӿ��Ƿ������Ӿ䣬j��ʶ��ǰ�Ӿ��Ƿ�L��iΪ0��ʶ���Ӿ京L��iΪ1��ʶ���Ӿ䲻��L
	Node1 *temp11, *temp12;
	Node2 *temp21 = head->p, *temp22 = head->p;
	for (i = 1; temp21 != NULL; i++){//�����Ӿ�ѭ��
		j = 1;
		for (temp11 = temp21->pL, temp12 = temp21->pL, k = 1; temp11 != NULL; k++){//ѭ���Ӿ��е�ÿһ������
			if (temp11->Elem == Elem){//�����ڵ��Ӿ����Ҫ�򻯵�����L�����
				if (i == 1){//����һ���Ӿ京��L
					head->p = temp21->next2;
					Destroy(temp21, head);
					i--;//ʹiΪ0�����µ�һ���Ӿ�
				}
				else{//�����Ӿ京��L
					temp22->next2 = temp21->next2;
					Destroy(temp21, head);
					i++;
				}
				j = 0;
				break;//�����ڶ���ѭ��
			}
			if (temp11->Elem == -Elem){
				if (k == 1){
					temp21->pL = temp11->next1;
					free(temp11);
					temp11 = temp21->pL;
					temp12 = temp21->pL;
					k--;
				}
				else{
					temp12->next1 = temp11->next1;
					free(temp11);
					temp11 = temp12->next1;
				}
				continue;
			}
			temp12 = temp11;
			temp11 = temp11->next1;
		}
			if (i == 0)
			{
				temp21 = head->p; temp22 = head->p;
			}
			else if (i == 1 || (i>1 && j == 0))
				temp21 = temp22->next2;
			else{
				temp22 = temp21;
				temp21 = temp22->next2;
			}

		}
	return 0;
}//����һ��root�ͺ�һ��elem��ɾ��root�����а���elem���ֵ��Ӿ�
root* AddClause(root *head, int VariElem){
	Node2 *tempCp, *tempCp2, *tempCp3;
	Node1 *tempLp, *tempLp2, *tempLp3;
	root * NewHead;
	int i;
	NewHead = (root*)malloc(sizeof(root));
	NewHead->NumOfClause = head->NumOfClause + 1;
	NewHead->NumOfVari = head->NumOfVari;
	tempLp = (Node1*)malloc(sizeof(Node1));
	tempCp = (Node2*)malloc(sizeof(Node2));
	tempCp->pL = tempLp;
	tempLp->next1 = NULL;
	tempLp->Elem = VariElem;
	NewHead->p = tempCp;
	for (tempCp2 = head->p, tempCp3 = tempCp; tempCp2 != NULL; tempCp2 = tempCp2->next2){
		tempCp = (Node2*)malloc(sizeof(Node2));
		tempCp3->next2 = tempCp;
		for (tempLp2 = tempCp2->pL, i = 1; tempLp2 != NULL; tempLp2 = tempLp2->next1){
			if (i == 1){
				tempLp = (Node1*)malloc(sizeof(Node1));
				tempCp->pL = tempLp;
				tempLp3 = tempLp;
				tempLp->Elem = tempLp2->Elem;
				i++;
			}
			else{
				tempLp3 = tempLp;
				tempLp = (Node1*)malloc(sizeof(Node1));
				tempLp3->next1 = tempLp;
				tempLp->Elem = tempLp2->Elem;
			}
		}
		tempLp->next1 = NULL;
		tempCp3 = tempCp;
	}
	tempCp->next2 = NULL;
	return NewHead;
}//����Ӿ�
int IsEmptyClause(root *head){//�������Ӿ䣬�򷵻�0�����򷵻�1
	Node2 *tempCp;
	for (tempCp = head->p; tempCp != NULL; tempCp = tempCp->next2)
		if (tempCp->pL == NULL)
			return 0;
	return 1;
}
int IsOver(root *head){
	if (head->p == NULL)
		return 1;
	return 0;
}//�Ƿ�ɾ������
int DestroyHead(root *head){
	Node2 *tempCp, *tempCp2;
	for (tempCp = head->p; tempCp != NULL; tempCp = tempCp2){
		tempCp2 = tempCp->next2;
		Destroy(tempCp, head);
	}
	free(head);
	return 0;
}
int LoadinFile(char filename[], root *head){
	FILE * file;
	char str[LENGTH], stemp[LENGTH], ch = '0';
	int i, j, k, l, m;//��ʱ����
	Node1 *temp1;
	Node2 *temp2;
	
	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("wrong!\n");
		return FALSE;
	}
	for (; fgets(str, LENGTH, file);)//����ע�ͣ�����"p cnf "
		if (strstr(str, DESCRIPTION) != NULL)
			break;
	for (i = 6; str[i] != ' '; i++)
		stemp[i - 6] = str[i];
	stemp[i - 6] = '\0';//stemp��¼��Ԫ��
	for (m = i; str[i] != '\0'; i++)
		str[i - m] = str[i];
	str[i - m] = '\0';//str��¼�Ӿ���
	head->NumOfVari = atoi(stemp);//��ȡ��Ԫ����atoi(�ַ���ת���Σ�
	f=(int*)malloc(sizeof(int)*atoi(stemp));
	memset(f,0,atoi(stemp));
	head->NumOfClause = atoi(str);//��ȡ�Ӿ���
	head->p = (Node2*)malloc(sizeof(Node2));//�����һ���Ӿ�
	temp2 = head->p;
	fgets(str, LENGTH, file);
	ch = '0';
	for (i = 0, j = 0, l = 0; str[i] != '0' || ch != ' '; i++){//i���Ƶ�ǰ�Ӿ��ַ�λ��,j���Ƶ�ǰ��λ�ã�l�ж��Ƿ�Ϊ��һ��,��forѭ��������һ���Ӿ�
		if (str[i] != ' ')
			stemp[j++] = str[i];
		else{
			stemp[j] = '\0';
			if (l == 0){
				temp1 = (Node1*)malloc(sizeof(Node1));
				temp2->pL = temp1;
				temp1->Elem = atoi(stemp);
				l++, j = 0;
			}
			else{
				temp1->next1 = (Node1*)malloc(sizeof(Node1));
				temp1 = temp1->next1;
				temp1->Elem = atoi(stemp);
				j = 0;
			}
		}
		ch = str[i];
	}
	temp1->next1 = NULL;//�����һ�е�ָ�������
	for (k = 1; k < head->NumOfClause; k++){//k�����Ӿ���Ŀ
		temp2->next2 = (Node2*)malloc(sizeof(Node2));
		temp2 = temp2->next2;
		fgets(str, LENGTH, file);//����ǰ�Ӿ��ַ���
		ch = '0';//��ǰһ���ַ�Ϊ��0��
		for (i = 0, j = 0, l = 0; str[i] != '0' || ch != ' '; i++){//i���Ƶ�ǰ�Ӿ��ַ�λ��,j���Ƶ�ǰ��λ�ã�l�ж��Ƿ�Ϊ��һ��,��forѭ��������һ���Ӿ�
			if (str[i] != ' ')
				stemp[j++] = str[i];
			else{
				stemp[j] = '\0';
				if (l == 0){
					temp1 = (Node1*)malloc(sizeof(Node1));
					temp2->pL = temp1;
					temp1->Elem = atoi(stemp);
					l++, j = 0;
				}
				else{
					temp1->next1 = (Node1*)malloc(sizeof(Node1));
					temp1 = temp1->next1;
					temp1->Elem = atoi(stemp);
					j = 0;
				}
			}
			ch = str[i];
		}
		temp1->next1 = NULL;//�����һ�е�ָ�������
	}
	temp2->next2 = NULL;//�����һ���Ӿ��ָ�������
	fclose(file);
	return 0;
}
int DPLL1(root *head){
	int e;
	root *p;
	while (IsUnitClause(*head, &e) != 0){
		RemoveClause(head, e);
	if(e>0)
		*(f+e-1)=TRUE;
	else
		*(f-e-1)=FALSE;//�ļ��������
		if (IsEmptyClause(head) == 0)
			return FALSE;
		if (IsOver(head) == 1)
			return TRUE;
	}
	if (e = DPLL1(p = AddClause(head, head->p->pL->Elem))){
		DestroyHead(p);
		return TRUE;
	}
	if (e == 0)
		DestroyHead(p);
	e = DPLL1(p = AddClause(head, -head->p->pL->Elem));
	DestroyHead(p);
	return e;
}
int DPLL2(root *head){
	int e;
	int ifmin=99;
	int min;
	Node1 *m;
	Node2 *n;
		root *p;
	while (IsUnitClause(*head, &e) != 0){
		RemoveClause(head, e);
	if(e>0)
		*(f+e-1)=TRUE;
	else
		*(f-e-1)=FALSE;//�ļ��������
		if (IsEmptyClause(head) == 0)
			return FALSE;
		if (IsOver(head) == 1)
			return TRUE;
	}
	for (n=head->p; n != NULL;n=n->next2){//�����Ӿ�ѭ��
		min=0;
			for (m = n->pL; m != NULL;m=m->next1){//ѭ���Ӿ��е�ÿһ������
				min=m->Elem;
				}
			if (min<ifmin){
				ifmin=min;
				tmin=n->pL->Elem;
			}
			}
	if (e = DPLL2(p = AddClause(head,tmin))){
		DestroyHead(p);
		return TRUE;
	}
	if (e == 0)
		DestroyHead(p);
	e = DPLL2(p = AddClause(head, -tmin));
	DestroyHead(p);
	return e;
}
int sudos(int x,int y,int d){
    return ((x-1)*9 +y-1)*9 +d;
}
int transudo(char filename[]){
    int clause = 0;
    clause += 81+324*27;
    FILE *fp_out;
    fp_out = fopen("sudoku.cnf","w");
    fprintf(fp_out,"p cnf 729 %d\n",clause);
    
    for(int i =1;i <=9; i++){
        for(int j = 1; j<=9;j++)
            if(sudo[(i-1)*9 +j-1] == 0){
                for(int d = 1;d <= 9;d++)
                    fprintf(fp_out,"%d ",sudos(i,j,d));
                fprintf(fp_out,"0\n");
                for(int d =1;d <=9;d++)
                    for(int l = d+1;l <=9;l++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d),-1*sudos(i,j,l));
            }
            else{
                for(int d = 1;d <= 9;d++)
                    if(sudo[(i-1)*9 +j-1] != d)
                        fprintf(fp_out, "%d 0\n",-1*sudos(i,j,d));
                    else
                        fprintf(fp_out, "%d 0\n",sudos(i,j,d));      
            }
            
    }//���в�ͬ

    for(int i = 1;i <=9; i++){
        for(int j = 1;j <= 9; j++)
            for(int k = j+1; k<=9; k++)
                for(int d =1; d<=9; d++)
                    fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(i,k,d));
    }//ÿ������һ��

    for(int i = 1;i <=9; i++){
        for(int j = 1;j <= 9; j++)
            for(int k = j+1; k<=9; k++)
                for(int d =1; d<=9; d++)
                    fprintf(fp_out,"%d %d 0\n",-1*sudos(j,i,d), -1*sudos(k,i,d));
    }//ÿ������һ��
	//����Ϊ�Ź���ͬ
    for(int i = 1;i <= 3;i++){
        for(int j = 1;j <=3;j++)
            for(int k =1;k <= 3;k++)
                for(int l = 1;l <=3;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 1;i <= 3;i++){
        for(int j = 4;j <=6;j++)
            for(int k =1;k <= 3;k++)
                for(int l = 4;l <=6;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 1;i <= 3;i++){
        for(int j = 7;j <=9;j++)
            for(int k =1;k <= 3;k++)
                for(int l = 7;l <=9;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }



    for(int i = 4;i <= 6;i++){
        for(int j = 1;j <=3;j++)
            for(int k =4;k <= 6;k++)
                for(int l = 1;l <=3;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 4;i <= 6;i++){
        for(int j = 4;j <=6;j++)
            for(int k =4;k <= 6;k++)
                for(int l = 4;l <=6;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 4;i <= 6;i++){
        for(int j = 7;j <=9;j++)
            for(int k =4;k <= 6;k++)
                for(int l = 7;l <=9;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    
    for(int i = 7;i <= 9;i++){
        for(int j = 1;j <=3;j++)
            for(int k =7;k <= 9;k++)
                for(int l = 1;l <=3;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 7;i <= 9;i++){
        for(int j = 4;j <=6;j++)
            for(int k =7;k <= 9;k++)
                for(int l = 4;l <=6;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }

    for(int i = 7;i <= 9;i++){
        for(int j = 7;j <=9;j++)
            for(int k =7;k <= 9;k++)
                for(int l = 7;l <=9;l++){
                    if((i-1)*3 +j >= (k-1)*3 +l )
                        continue;
                    for(int d= 1; d<= 9;d++)
                        fprintf(fp_out,"%d %d 0\n",-1*sudos(i,j,d), -1*sudos(k,l,d));
                
                }
    }
    fclose(fp_out);
	return 0;
}