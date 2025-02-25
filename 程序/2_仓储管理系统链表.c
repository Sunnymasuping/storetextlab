#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 1000

typedef struct
{
	char ID[20];     //ID
	char goods[20];  //货品名 
	float price;     //定价 
	int num;         //数量 
}Goods;

typedef struct Lnode
{
	Goods e;     
	struct Lnode* next; 
}Lnode;


void input( Lnode *L );//收录货品
void sale( Lnode *L );//售出货品
void del( Lnode *L );//清除货品
void alter( Lnode *L );//修改货品信息
void sort_p( Lnode *L );//按定价排序
void sort_n( Lnode *L );//按数量排序
void load( Lnode *L ); //加载文件中的商品信息
void save( Lnode *L ); //商品信息保存到文件中 
void find_ID( Lnode *L );//按ID查找货品信息
void find_good( Lnode *L );//按货品名查找货品信息

Lnode* creat( );//创建一个节点
Lnode* get_node(Lnode *L,const char *id);//根据ID得到一个货品
void del_node(Lnode *L,const char *id); //根据ID删除一个货品
void add_node(Lnode *L,Goods e); //添加一个货品的节点到链表中  

int main()
{
	int c;
	Lnode *L = creat( );//创建一个节点
	
	printf("********************************************\n");
	printf("*               仓储管理系统               *\n");
	printf("********************************************\n");
	printf("\n");

	load( L ); //加载文件中的商品信息
	while(1)
	{
		printf("仓储管理系统\n");
		printf("1. 收录货品\n");
		printf("2. 售出货品\n");
		printf("3. 清除货品\n");
		printf("4. 修改货品\n");
		printf("5. 按定价排序\n");
		printf("6. 按数量排序\n");
		printf("7. 按ID查找货品信息\n");
		printf("8. 按货品名查找货品信息\n");
		printf("0. 退出系统\n");
		printf("请选择: ");
		scanf("%d",&c);
		switch(c)
		{
			case 1: input( L ); break; //收录货品
			case 2: sale( L ); break; //售出货品
			case 3: del( L ); break; //清除货品
			case 4: alter( L ); break; //修改货品
			case 5: sort_p( L ); break; //按定价排序输出
			case 6: sort_n( L ); break; //按数量排序输出
			case 7: find_ID( L ); break;//按ID查找货品信息
			case 8: find_good( L ); break;//按货品名查找货品信息
			case 0: return 0;	
	; 	}	
	}
	return 0;
} 

 //收录货品
void input( Lnode *L )
{
	Goods e;
	int number;
	Lnode *p = NULL;
	
	printf("输入货品ID: ");
	scanf("%s",e.ID);
	
	p = get_node(L,e.ID);
	if(p!= NULL) 
	{
		printf("货品已存在,请输入进货数量: ");
		scanf("%d",&number);
		p->e.num += number;
	} 
	else
	{
		printf("货品名: ");
		scanf("%s",e.goods);
		printf("定价: ");
		scanf("%f",&e.price);
		printf("数量: ");
		scanf("%d",&e.num);
		add_node(L , e); //添加一个货品的节点到链表中  
	}
	
	save( L ); //商品信息保存到文件中 
	printf("收录成功\n");
}

//售出货品
void sale(Lnode *L)
{
	Goods e;
	int number;
	Lnode *p = NULL;
	
	printf("输入售出货品ID: ");
	scanf("%s",e.ID);
	
	p = get_node( L , e.ID);
	if( p != NULL ) 
	{
		printf("输入售出数量: ");
		scanf("%d",&number);
		if(number > p->e.num)
		{
			printf("售出失败\n");
		}
		else 
		{
			p->e.num -= number;
			save( L ); //商品信息保存到文件中 
			printf("售出成功\n");
		}
	} 
	else 
	{
		printf("货品信息不存在\n");
	}
}

//清除货品
void del( Lnode *L )
{
	Goods e;
	
	printf("输入清除货品ID: ");
	scanf("%s",e.ID);
	
	if( get_node( L , e.ID) != NULL ) 
	{
		
		del_node(L , e.ID); //根据ID删除一个货品
		
		save( L ); //商品信息保存到文件中 
		printf("清除成功\n");
	} 
	else 
	{
		printf("货品信息不存在\n");
	}	
}

//修改货品
void alter(Lnode *L)
{
	Goods e;

	Lnode *p = NULL;
	
	printf("输入修改货品ID: ");
	scanf("%s",e.ID);
	
	p = get_node(L,e.ID);
	if(p!= NULL) 
	{
		e = p->e; 
		while(1)
		{
			printf("输入修改后的ID号: ");
			scanf("%s",e.ID);
			if(get_node(L,e.ID) != NULL)
			{
				printf("ID号已经存在\n");
				continue;
			}
			break;
		}
		
		printf("输入修改后的货品名: ");
		scanf("%s",e.goods);
		printf("输入修改后的货品单价: ");
		scanf("%f",&e.price);
		
		p->e=e;
		save(L); //商品信息保存到文件中 
		printf("修改成功\n");
	}
	else 
	{
		printf("货品信息不存在\n");
	}		
}

//按ID查询货品信息
void find_ID(Lnode *L)
{
	Goods e;
	Lnode *p = NULL;
	
	printf("输入所要找的货品ID: ");
	scanf("%s",e.ID);
	
	p = get_node(L,e.ID);
	if(p!=NULL)
	{
		e=p->e; 
		printf("%-20s%-20s%-20s%-20s\n","ID","货品名","定价","数量");
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
		printf("查询成功\n");
	}
	else
	{
		printf("货品信息不存在\n");
	}		
}

//按货品名查询货品信息
void find_good(Lnode *L)
{
	Goods e;
	Lnode *p =L->next;
	int flag= 0;

	printf("输入查询的货品名: ");
	scanf("%s",e.goods);
	
	while(p)
	{
		if(strcmp(e.goods,p->e.goods) == 0)
		{
			if(flag == 0)
			{
				printf("%-20s%-20s%-20s%-20s\n","ID","货品名","定价","数量");
			}	
			e = p->e; 
			printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
			flag = 1;
		}
		p = p->next;
	}
	
	if(flag == 0)
	{
		printf("查询失败\n");
	}
}

//单链表冒泡排序算法 
Lnode *sort1(Lnode *L,int len)
 {
    Lnode *p,*n;
    int i , j ;
	Goods t;
	
	/*单链表模拟冒泡排序算法*/    
    for(i = 0; i < len; i++)
	{
        p = L;
        n = p->next;
        for(j = len - i - 1; j > 0; j--) 
		{
            if(p->e.price > n->e.price)
			{  //判断大小 
                t = p->e;   //交换，小的在前 
                p->e = n->e;
                n->e = t;
            }
            p = p->next;
            n = n->next;
        }
    }
    return p;
}

//按定价排序
void sort_p( Lnode *L )
{
	
	Goods e;      //货品 	
	Lnode *p = NULL;
	L = sort1(L, get_len(L));
		
	printf("按定价排序后:\n");
	p = L->next;
	printf("%-20s%-20s%-20s%-20s\n","ID","货品名","定价","数量");
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
	
	/*单链表模拟冒泡排序算法*/    
    for(i=0; i<len;i++) 
	{
        p = L;
        n = p->next;
        for(j = len - i - 1; j > 0; j--) 
		{
            if(p->e.num > n->e.num) 
			{  //判断大小 
                t = p->e;   //交换，小的在前 
                p->e = n->e;
                n->e = t;
            }
            p = p->next;
            n = n->next;
        }
    }
    return p;
}

//按数量排序
void sort_n(Lnode *L)
{
	Goods e;      //货品 	
	Lnode *p = NULL;
	L = sort2(L, get_len(L));
		
	printf("按数量排序后:\n");
	p = L->next;
	printf("%-20s%-20s%-20s%-20s\n","ID","货品名","定价","数量");
	while(p){
		e = p->e;
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
		p = p->next;
	}	
}

//加载文件中的商品信息
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

//商品信息保存到文件中 
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

	

	
 //创建一个节点
Lnode* creat( )
{
	Lnode* L = (Lnode* )malloc(sizeof(Lnode));
	L->next = NULL;
	return L;
}

//根据ID得到一个货品
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

//根据ID删除一个货品
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

//添加一个货品的节点到链表中
void add_node(Lnode* L , Goods e)   
{
	Lnode* new_ = creat();
	Lnode* p = L ; 
	
	new_->e = e; 
	while(p->next)
	{
		p = p->next;
	}
	p->next= new_;  //尾插法 	
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
 
 
 
