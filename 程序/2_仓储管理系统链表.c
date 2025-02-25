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

typedef struct Lnode
{
	Goods e;     
	struct Lnode* next; 
}Lnode;


void input( Lnode *L );//��¼��Ʒ
void sale( Lnode *L );//�۳���Ʒ
void del( Lnode *L );//�����Ʒ
void alter( Lnode *L );//�޸Ļ�Ʒ��Ϣ
void sort_p( Lnode *L );//����������
void sort_n( Lnode *L );//����������
void load( Lnode *L ); //�����ļ��е���Ʒ��Ϣ
void save( Lnode *L ); //��Ʒ��Ϣ���浽�ļ��� 
void find_ID( Lnode *L );//��ID���һ�Ʒ��Ϣ
void find_good( Lnode *L );//����Ʒ�����һ�Ʒ��Ϣ

Lnode* creat( );//����һ���ڵ�
Lnode* get_node(Lnode *L,const char *id);//����ID�õ�һ����Ʒ
void del_node(Lnode *L,const char *id); //����IDɾ��һ����Ʒ
void add_node(Lnode *L,Goods e); //���һ����Ʒ�Ľڵ㵽������  

int main()
{
	int c;
	Lnode *L = creat( );//����һ���ڵ�
	
	printf("********************************************\n");
	printf("*               �ִ�����ϵͳ               *\n");
	printf("********************************************\n");
	printf("\n");

	load( L ); //�����ļ��е���Ʒ��Ϣ
	while(1)
	{
		printf("�ִ�����ϵͳ\n");
		printf("1. ��¼��Ʒ\n");
		printf("2. �۳���Ʒ\n");
		printf("3. �����Ʒ\n");
		printf("4. �޸Ļ�Ʒ\n");
		printf("5. ����������\n");
		printf("6. ����������\n");
		printf("7. ��ID���һ�Ʒ��Ϣ\n");
		printf("8. ����Ʒ�����һ�Ʒ��Ϣ\n");
		printf("0. �˳�ϵͳ\n");
		printf("��ѡ��: ");
		scanf("%d",&c);
		switch(c)
		{
			case 1: input( L ); break; //��¼��Ʒ
			case 2: sale( L ); break; //�۳���Ʒ
			case 3: del( L ); break; //�����Ʒ
			case 4: alter( L ); break; //�޸Ļ�Ʒ
			case 5: sort_p( L ); break; //�������������
			case 6: sort_n( L ); break; //�������������
			case 7: find_ID( L ); break;//��ID���һ�Ʒ��Ϣ
			case 8: find_good( L ); break;//����Ʒ�����һ�Ʒ��Ϣ
			case 0: return 0;	
	; 	}	
	}
	return 0;
} 

 //��¼��Ʒ
void input( Lnode *L )
{
	Goods e;
	int number;
	Lnode *p = NULL;
	
	printf("�����ƷID: ");
	scanf("%s",e.ID);
	
	p = get_node(L,e.ID);
	if(p!= NULL) 
	{
		printf("��Ʒ�Ѵ���,�������������: ");
		scanf("%d",&number);
		p->e.num += number;
	} 
	else
	{
		printf("��Ʒ��: ");
		scanf("%s",e.goods);
		printf("����: ");
		scanf("%f",&e.price);
		printf("����: ");
		scanf("%d",&e.num);
		add_node(L , e); //���һ����Ʒ�Ľڵ㵽������  
	}
	
	save( L ); //��Ʒ��Ϣ���浽�ļ��� 
	printf("��¼�ɹ�\n");
}

//�۳���Ʒ
void sale(Lnode *L)
{
	Goods e;
	int number;
	Lnode *p = NULL;
	
	printf("�����۳���ƷID: ");
	scanf("%s",e.ID);
	
	p = get_node( L , e.ID);
	if( p != NULL ) 
	{
		printf("�����۳�����: ");
		scanf("%d",&number);
		if(number > p->e.num)
		{
			printf("�۳�ʧ��\n");
		}
		else 
		{
			p->e.num -= number;
			save( L ); //��Ʒ��Ϣ���浽�ļ��� 
			printf("�۳��ɹ�\n");
		}
	} 
	else 
	{
		printf("��Ʒ��Ϣ������\n");
	}
}

//�����Ʒ
void del( Lnode *L )
{
	Goods e;
	
	printf("���������ƷID: ");
	scanf("%s",e.ID);
	
	if( get_node( L , e.ID) != NULL ) 
	{
		
		del_node(L , e.ID); //����IDɾ��һ����Ʒ
		
		save( L ); //��Ʒ��Ϣ���浽�ļ��� 
		printf("����ɹ�\n");
	} 
	else 
	{
		printf("��Ʒ��Ϣ������\n");
	}	
}

//�޸Ļ�Ʒ
void alter(Lnode *L)
{
	Goods e;

	Lnode *p = NULL;
	
	printf("�����޸Ļ�ƷID: ");
	scanf("%s",e.ID);
	
	p = get_node(L,e.ID);
	if(p!= NULL) 
	{
		e = p->e; 
		while(1)
		{
			printf("�����޸ĺ��ID��: ");
			scanf("%s",e.ID);
			if(get_node(L,e.ID) != NULL)
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
		
		p->e=e;
		save(L); //��Ʒ��Ϣ���浽�ļ��� 
		printf("�޸ĳɹ�\n");
	}
	else 
	{
		printf("��Ʒ��Ϣ������\n");
	}		
}

//��ID��ѯ��Ʒ��Ϣ
void find_ID(Lnode *L)
{
	Goods e;
	Lnode *p = NULL;
	
	printf("������Ҫ�ҵĻ�ƷID: ");
	scanf("%s",e.ID);
	
	p = get_node(L,e.ID);
	if(p!=NULL)
	{
		e=p->e; 
		printf("%-20s%-20s%-20s%-20s\n","ID","��Ʒ��","����","����");
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
		printf("��ѯ�ɹ�\n");
	}
	else
	{
		printf("��Ʒ��Ϣ������\n");
	}		
}

//����Ʒ����ѯ��Ʒ��Ϣ
void find_good(Lnode *L)
{
	Goods e;
	Lnode *p =L->next;
	int flag= 0;

	printf("�����ѯ�Ļ�Ʒ��: ");
	scanf("%s",e.goods);
	
	while(p)
	{
		if(strcmp(e.goods,p->e.goods) == 0)
		{
			if(flag == 0)
			{
				printf("%-20s%-20s%-20s%-20s\n","ID","��Ʒ��","����","����");
			}	
			e = p->e; 
			printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
			flag = 1;
		}
		p = p->next;
	}
	
	if(flag == 0)
	{
		printf("��ѯʧ��\n");
	}
}

//������ð�������㷨 
Lnode *sort1(Lnode *L,int len)
 {
    Lnode *p,*n;
    int i , j ;
	Goods t;
	
	/*������ģ��ð�������㷨*/    
    for(i = 0; i < len; i++)
	{
        p = L;
        n = p->next;
        for(j = len - i - 1; j > 0; j--) 
		{
            if(p->e.price > n->e.price)
			{  //�жϴ�С 
                t = p->e;   //������С����ǰ 
                p->e = n->e;
                n->e = t;
            }
            p = p->next;
            n = n->next;
        }
    }
    return p;
}

//����������
void sort_p( Lnode *L )
{
	
	Goods e;      //��Ʒ 	
	Lnode *p = NULL;
	L = sort1(L, get_len(L));
		
	printf("�����������:\n");
	p = L->next;
	printf("%-20s%-20s%-20s%-20s\n","ID","��Ʒ��","����","����");
	while(p)
	{
		e = p->e;
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
		p = p->next;
	}
}

Lnode *sort2(Lnode *L, int len)
{
    Lnode *p,*n;
    int i , j ;
	Goods t;
	
	/*������ģ��ð�������㷨*/    
    for(i=0; i<len;i++) 
	{
        p = L;
        n = p->next;
        for(j = len - i - 1; j > 0; j--) 
		{
            if(p->e.num > n->e.num) 
			{  //�жϴ�С 
                t = p->e;   //������С����ǰ 
                p->e = n->e;
                n->e = t;
            }
            p = p->next;
            n = n->next;
        }
    }
    return p;
}

//����������
void sort_n(Lnode *L)
{
	Goods e;      //��Ʒ 	
	Lnode *p = NULL;
	L = sort2(L, get_len(L));
		
	printf("�����������:\n");
	p = L->next;
	printf("%-20s%-20s%-20s%-20s\n","ID","��Ʒ��","����","����");
	while(p){
		e = p->e;
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
		p = p->next;
	}	
}

//�����ļ��е���Ʒ��Ϣ
void load(Lnode* L)
{
	FILE* fp;
	Goods e;
	
	if( (fp = fopen("good.txt" , "r")) == NULL ){
		return ;
	}
	
	while( (fscanf(fp,"%s",e.ID)) != EOF )
	{
		fscanf(fp,"%s %f %d\n",e.goods,&e.price,&e.num);
		add_node(L , e); 
	}

	fclose(fp);
}

//��Ʒ��Ϣ���浽�ļ��� 
void save(Lnode* L)
{
	FILE* fp;
	Lnode* p = L->next;
	Goods e;
	
	fp = fopen("good.txt" , "w");
	
	while(p){
		e = p->e;
		fprintf(fp,"%s %s %f %d\n",e.ID,e.goods,e.price,e.num);
		p = p->next;
	}

	fclose(fp);
}

	

	
 //����һ���ڵ�
Lnode* creat( )
{
	Lnode* L = (Lnode* )malloc(sizeof(Lnode));
	L->next = NULL;
	return L;
}

//����ID�õ�һ����Ʒ
Lnode* get_node(Lnode* L,const char* id)
{
	Lnode* p = L->next; 
	while(p)
	{
		if(strcmp(p->e.ID,id) == 0)
		{
			return p;
		}
		p = p->next;
	}	
	return NULL;	
}

//����IDɾ��һ����Ʒ
void del_node(Lnode* L,const char* id)
{
	Lnode* p = L , *del = NULL; 
	while(p->next)
	{
		if(strcmp(p->next->e.ID,id) == 0)
		{
			del = p->next;
			p->next = p->next->next;
			free(del);
			return;
		}
		p = p->next;
	}	
}

//���һ����Ʒ�Ľڵ㵽������
void add_node(Lnode* L , Goods e)   
{
	Lnode* new_ = creat();
	Lnode* p = L ; 
	
	new_->e = e; 
	while(p->next)
	{
		p = p->next;
	}
	p->next= new_;  //β�巨 	
}

int get_len(Lnode* L)
{
	Lnode* p = L->next; 
	int c= 0;
	while(p)
	{
		c ++;
		p = p->next;
	}	
	return c;
}
 
 
 
