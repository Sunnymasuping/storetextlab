#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 1000

typedef struct
{
	char ID[20];     //ID
	char goods[20];  //��Ʒ�� 
	float price;     //���� 
	int num;         //���� 
}Goods;

typedef struct
{
	Goods e[N];      //��Ʒ 
	int l;           //��Ʒ���� 
}Lnode;

int login() ; //��¼ 
void input( Lnode *L );//��¼��Ʒ
void work( Lnode *L );//�۳���Ʒ
void del( Lnode *L );//�����Ʒ
void alter( Lnode *L );//�޸Ļ�Ʒ
void sort_p( Lnode *L );//�������������
void sort_n( Lnode *L );//�������������
void query_ID( Lnode *L );//��ID��ѯ��Ʒ��Ϣ
void query_good( Lnode *L );//����Ʒ����ѯ��Ʒ��Ϣ
void load( Lnode* L ); //�����ļ��е���Ʒ��Ϣ
void save( Lnode* L ); //��Ʒ��Ϣ���浽�ļ��� 

int main()
{
	int c;
	Lnode L;
	
	if( login() ){
		return 0;
	}	
	
	printf("\n��¼�ɹ�\n");
	L.l = 0;
	load( &L ); //�����ļ��е���Ʒ��Ϣ
	while(1)
	{
		printf("�ִ�����ϵͳ\n");
		printf("1. ��¼��Ʒ\n");
		printf("2. �۳���Ʒ\n");
		printf("3. �����Ʒ\n");
		printf("4. �޸Ļ�Ʒ\n");
		printf("5. �������������\n");
		printf("6. �������������\n");
		printf("7. ��ID��ѯ��Ʒ��Ϣ\n");
		printf("8. ����Ʒ����ѯ��Ʒ��Ϣ\n");		  
		printf("0. �˳�ϵͳ\n");
		printf("��ѡ��: ");
		scanf("%d",&c);
		switch(c)
		{
			case 1: input( &L ); break; //��¼��Ʒ
			case 2: work( &L ); break; //�۳���Ʒ
			case 3: del( &L ); break; //�����Ʒ
			case 4: alter( &L ); break; //�޸Ļ�Ʒ
			case 5: sort_p( &L ); break; //�������������
			case 6: sort_n( &L ); break; //�������������
			case 7: query_ID( &L ); break;//��ID��ѯ��Ʒ��Ϣ
			case 8: query_good( &L ); break;//����Ʒ����ѯ��Ʒ��Ϣ
			case 0: return 0;	
		}	
	}
	return 0;
} 

//ͨ����ƷID�õ�һ����Ʒ��Ϣ 
int get_ID( Lnode* L , char *ID)
{
	int i;
	for(i=0;i<L->l;i++){
		if(strcmp(L->e[i].ID,ID) == 0){
			return i;
		}
	}
	return -1;
}

 //��¼��Ʒ
void input( Lnode *L )
{
	Goods e;
	int n , number;
	
	printf("�����ƷID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		printf("��ƷID�Ѿ�����,��ֱ�������������: ");
		scanf("%d",&number);
		L->e[n].num += number;
	} else {
		printf("��Ʒ��: ");
		scanf("%s",e.goods);
		printf("����: ");
		scanf("%f",&e.price);
		printf("����: ");
		scanf("%d",&e.num);
		L->e[ (L->l) ++] = e;
	}
	
	save( L ); //��Ʒ��Ϣ���浽�ļ��� 
	printf("��¼�ɹ�\n");
}

//�۳���Ʒ
void work( Lnode *L )
{
	Goods e;
	int n , number;
	
	printf("�����۳���ƷID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		printf("�����۳�����: ");
		scanf("%d",&number);
		if(number > L->e[n].num){
			printf("�۳�ʧ��,��Ʒʣ����������\n");
		} else {
			L->e[n].num -= number;
			save( L ); //��Ʒ��Ϣ���浽�ļ��� 
			printf("�۳��ɹ�\n");
		}
	} else {
		printf("��Ʒ��Ϣ������\n");
	}
}

//�����Ʒ
void del( Lnode *L )
{
	Goods e;
	int n;
	
	printf("���������ƷID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		
		(L->l)--;
		for( ; n<L->l ; n++)
		{
			L->e[n] = L->e[n+1];
		}
		
		save( L ); //��Ʒ��Ϣ���浽�ļ��� 
		printf("����ɹ�\n");
	} else {
		printf("��Ʒ��Ϣ������\n");
	}	
}

//�޸Ļ�Ʒ
void alter( Lnode *L )
{
	Goods e;
	int n;
	
	printf("�����޸Ļ�ƷID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		e = L->e[n]; 
		while(1){
			printf("�����޸ĺ��ID��: ");
			scanf("%s",e.ID);
			if( get_ID( L , e.ID) != -1)
			{
				printf("ID���Ѿ�����\n");
				continue;
			}
			break;
		}
		
		printf("�����޸ĺ�Ļ�Ʒ��: ");
		scanf("%s",e.goods);
		printf("�����޸ĺ�Ļ�Ʒ����: ");
		scanf("%f",&e.price);
		
		L->e[n] = e;
		save( L ); //��Ʒ��Ϣ���浽�ļ��� 
		printf("�޸ĳɹ�\n");
	} else {
		printf("��Ʒ��Ϣ������\n");
	}		
}

//��ID��ѯ��Ʒ��Ϣ
void query_ID( Lnode *L )
{
	Goods e;
	int n;
	
	printf("�����ѯ�Ļ�ƷID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		e = L->e[n]; 
		printf("%-20s%-20s%-20s%-20s\n","ID","��Ʒ��","����","����");
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
		printf("��ѯ�ɹ�\n");
	} else {
		printf("��Ʒ��Ϣ������\n");
	}		
}

//����Ʒ����ѯ��Ʒ��Ϣ
void query_good( Lnode *L )
{
	Goods e;
	int i , flag= 0;
	
	printf("�����ѯ�Ļ�Ʒ��: ");
	scanf("%s",e.goods);
	
	for(i=0;i<L->l;i++)
	{
		if(strcmp(e.goods,L->e[i].goods) == 0)
		{
			if(flag == 0){
				printf("%-20s%-20s%-20s%-20s\n","ID","��Ʒ��","����","����");
			}	
			e = L->e[i]; 
			printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
			flag = 1;
		}
	}
	
	if(flag == 0){
		printf("��ѯʧ��\n");
	}
}


//�������������
void sort_p( Lnode *L )
{
	int i , j ;
	Goods e;      //��Ʒ 	
	
	for(i=0 ; i<L->l-1 ; i++) //ð������ 
	{
		for(j=0 ; j<L->l-i-1; j ++)
		{
			if(L->e[j].price < L->e[j+1].price)
			{
				e = L->e[j];
				L->e[j] = L->e[j+1];
				L->e[j+1] = e;
			}
		}
	}
	
	printf("�����������:\n");
	printf("%-20s%-20s%-20s%-20s\n","ID","��Ʒ��","����","����");
	for(i=0 ; i<L->l-1 ; i++)
	{
		e = L->e[i];
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
	}

}

//��������
void quick( Lnode *L , int left , int right)
{
	int i, j;
	Goods temp , t;
	if(left > right)
		return ;
	temp = L->e[left];
	i = left ;
	j = right;
	while(i != j){
		while(L->e[j].num>=temp.num && i<j)
			j--;
		while(L->e[i].num<=temp.num && i<j)
			i++;
		if(i<j){
			t = L->e[i];
			L->e[i] = L->e[j];
			L->e[j] = t;
		}
	}
	L->e[left] = L->e[i];
	L->e[i] = temp;
	
	quick(L , left , i-1);
	quick(L , i+1 , right);
	return ;	
}

//�������������
void sort_n( Lnode *L )
{
	int i , j ;
	Goods e;      //��Ʒ 	
	
	quick( L , 0 , L->l-1 ); //��������   
	
	printf("�����������:\n");
	printf("%-20s%-20s%-20s%-20s\n","ID","��Ʒ��","����","����");
	for(i=0 ; i<L->l-1 ; i++)
	{
		e = L->e[i];
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
	}	
}

//�����ļ��е���Ʒ��Ϣ
void load( Lnode* L )
{
	FILE* fp;
	int i = 0;
	Goods e;
	
	if( (fp = fopen("good.txt" , "r")) == NULL ){
		return ;
	}
	
	while( (fscanf(fp,"%s",e.ID)) != EOF )
	{
		fscanf(fp,"%s %f %d\n",e.goods,&e.price,&e.num);
		L->e[i++] = e;
	}
		
	L->l = i;
	fclose(fp);
}

//��Ʒ��Ϣ���浽�ļ��� 
void save( Lnode* L )
{
	FILE* fp;
	int i = 0;
	Goods e;
	
	fp = fopen("good.txt" , "w");
	for(i=0;i<L->l;i++){
		e = L->e[i];
		fprintf(fp,"%s %s %f %d\n",e.ID,e.goods,e.price,e.num);
	}
	fclose(fp);
}

int login()
{
	char u[30] , p[30] ;
	int  i=0 , n ;
	
	printf("********************************************\n");
	printf("*               �ִ�����ϵͳ               *\n");
	printf("********************************************\n");
	printf("\n");
	
	printf("�����¼����: ");
	scanf("%d",&n);

	while(i<n)
	{
		printf("���������˺�: ");
		scanf("%s",u);
		printf("������������: ");
		scanf("%s",p);
		if(strcmp(u , "111111") == 0 && strcmp(p,"111111") == 0)
		{
			return 0;
		}
		
		printf("�˺Ż��������\n");
		i++; 
	} 
	
	printf("��¼�����Ѿ��ﵽ����\n");
	return 1;
}
 
 
 
 
 
 
 
