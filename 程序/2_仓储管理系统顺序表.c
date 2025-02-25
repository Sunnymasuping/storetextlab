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

typedef struct
{
	Goods e[N];      //货品 
	int l;           //货品个数 
}Lnode;

int login() ; //登录 
void input( Lnode *L );//收录货品
void work( Lnode *L );//售出货品
void del( Lnode *L );//清除货品
void alter( Lnode *L );//修改货品
void sort_p( Lnode *L );//按定价排序输出
void sort_n( Lnode *L );//按数量排序输出
void query_ID( Lnode *L );//按ID查询货品信息
void query_good( Lnode *L );//按货品名查询货品信息
void load( Lnode* L ); //加载文件中的商品信息
void save( Lnode* L ); //商品信息保存到文件中 

int main()
{
	int c;
	Lnode L;
	
	if( login() ){
		return 0;
	}	
	
	printf("\n登录成功\n");
	L.l = 0;
	load( &L ); //加载文件中的商品信息
	while(1)
	{
		printf("仓储管理系统\n");
		printf("1. 收录货品\n");
		printf("2. 售出货品\n");
		printf("3. 清除货品\n");
		printf("4. 修改货品\n");
		printf("5. 按定价排序输出\n");
		printf("6. 按数量排序输出\n");
		printf("7. 按ID查询货品信息\n");
		printf("8. 按货品名查询货品信息\n");		  
		printf("0. 退出系统\n");
		printf("请选择: ");
		scanf("%d",&c);
		switch(c)
		{
			case 1: input( &L ); break; //收录货品
			case 2: work( &L ); break; //售出货品
			case 3: del( &L ); break; //清除货品
			case 4: alter( &L ); break; //修改货品
			case 5: sort_p( &L ); break; //按定价排序输出
			case 6: sort_n( &L ); break; //按数量排序输出
			case 7: query_ID( &L ); break;//按ID查询货品信息
			case 8: query_good( &L ); break;//按货品名查询货品信息
			case 0: return 0;	
		}	
	}
	return 0;
} 

//通过货品ID得到一个货品信息 
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

 //收录货品
void input( Lnode *L )
{
	Goods e;
	int n , number;
	
	printf("输入货品ID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		printf("货品ID已经存在,请直接输入进货数量: ");
		scanf("%d",&number);
		L->e[n].num += number;
	} else {
		printf("货品名: ");
		scanf("%s",e.goods);
		printf("定价: ");
		scanf("%f",&e.price);
		printf("数量: ");
		scanf("%d",&e.num);
		L->e[ (L->l) ++] = e;
	}
	
	save( L ); //商品信息保存到文件中 
	printf("收录成功\n");
}

//售出货品
void work( Lnode *L )
{
	Goods e;
	int n , number;
	
	printf("输入售出货品ID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		printf("输入售出数量: ");
		scanf("%d",&number);
		if(number > L->e[n].num){
			printf("售出失败,货品剩余数量不足\n");
		} else {
			L->e[n].num -= number;
			save( L ); //商品信息保存到文件中 
			printf("售出成功\n");
		}
	} else {
		printf("货品信息不存在\n");
	}
}

//清除货品
void del( Lnode *L )
{
	Goods e;
	int n;
	
	printf("输入清除货品ID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		
		(L->l)--;
		for( ; n<L->l ; n++)
		{
			L->e[n] = L->e[n+1];
		}
		
		save( L ); //商品信息保存到文件中 
		printf("清除成功\n");
	} else {
		printf("货品信息不存在\n");
	}	
}

//修改货品
void alter( Lnode *L )
{
	Goods e;
	int n;
	
	printf("输入修改货品ID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		e = L->e[n]; 
		while(1){
			printf("输入修改后的ID号: ");
			scanf("%s",e.ID);
			if( get_ID( L , e.ID) != -1)
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
		
		L->e[n] = e;
		save( L ); //商品信息保存到文件中 
		printf("修改成功\n");
	} else {
		printf("货品信息不存在\n");
	}		
}

//按ID查询货品信息
void query_ID( Lnode *L )
{
	Goods e;
	int n;
	
	printf("输入查询的货品ID: ");
	scanf("%s",e.ID);
	
	n = get_ID( L , e.ID);
	if( n != -1 ) {
		e = L->e[n]; 
		printf("%-20s%-20s%-20s%-20s\n","ID","货品名","定价","数量");
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
		printf("查询成功\n");
	} else {
		printf("货品信息不存在\n");
	}		
}

//按货品名查询货品信息
void query_good( Lnode *L )
{
	Goods e;
	int i , flag= 0;
	
	printf("输入查询的货品名: ");
	scanf("%s",e.goods);
	
	for(i=0;i<L->l;i++)
	{
		if(strcmp(e.goods,L->e[i].goods) == 0)
		{
			if(flag == 0){
				printf("%-20s%-20s%-20s%-20s\n","ID","货品名","定价","数量");
			}	
			e = L->e[i]; 
			printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
			flag = 1;
		}
	}
	
	if(flag == 0){
		printf("查询失败\n");
	}
}


//按定价排序输出
void sort_p( Lnode *L )
{
	int i , j ;
	Goods e;      //货品 	
	
	for(i=0 ; i<L->l-1 ; i++) //冒泡排序 
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
	
	printf("按定价排序后:\n");
	printf("%-20s%-20s%-20s%-20s\n","ID","货品名","定价","数量");
	for(i=0 ; i<L->l-1 ; i++)
	{
		e = L->e[i];
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
	}

}

//快速排序
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

//按数量排序输出
void sort_n( Lnode *L )
{
	int i , j ;
	Goods e;      //货品 	
	
	quick( L , 0 , L->l-1 ); //快速排序   
	
	printf("按数量排序后:\n");
	printf("%-20s%-20s%-20s%-20s\n","ID","货品名","定价","数量");
	for(i=0 ; i<L->l-1 ; i++)
	{
		e = L->e[i];
		printf("%-20s%-20s%-20.2f%-20d\n",e.ID,e.goods,e.price,e.num);
	}	
}

//加载文件中的商品信息
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

//商品信息保存到文件中 
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
	printf("*               仓储管理系统               *\n");
	printf("********************************************\n");
	printf("\n");
	
	printf("输入登录次数: ");
	scanf("%d",&n);

	while(i<n)
	{
		printf("输入您的账号: ");
		scanf("%s",u);
		printf("输入您的密码: ");
		scanf("%s",p);
		if(strcmp(u , "111111") == 0 && strcmp(p,"111111") == 0)
		{
			return 0;
		}
		
		printf("账号或密码错误\n");
		i++; 
	} 
	
	printf("登录次数已经达到上限\n");
	return 1;
}
 
 
 
 
 
 
 
