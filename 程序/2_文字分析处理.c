#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char s[10000];
	int l;
}Lnode;


void input(Lnode* L); //输入一段文字 
void show(Lnode L);//显示输入的一段文字
void sta(Lnode L);//统计结果
void query(Lnode L);//单词计数
void replace(Lnode* L);//替换字符串 
void query_n(Lnode L); //显示输入文字的行数

int main()
{
	Lnode L;
	int c;

	input(&L); //输入一段文字 
	while (1)
	{
		printf("1. 显示输入的一段文字\n");
		printf("2. 统计结果\n");
		printf("3. 单词计数\n");
		printf("4. 替换字符串\n");
		printf("5. 显示输入文字的行数\n");
		printf("0. 退出系统\n");
		printf("请选择: ");
		scanf("%d", &c);
		switch (c)
		{
		case 1: show(L); break;//显示输入的一段文字
		case 2: sta(L); break;//统计结果
		case 3: query(L); break;//单词计数
		case 4: replace(&L); break;//替换字符串
		case 5: query_n(L); break;//显示输入文字的行数
		case 0: return 0;
		}
	}
	return 0;
}

//输入一段文字 
void input(Lnode* L)
{
	char c;
	int l = 0;

	printf("输入一段文字,以回车结束输入\n");
	while ((scanf("%c", &c)) != EOF)
	{
		L->s[l++] = c;
	}
	L->s[l] = '\0';
	L->l = l;
}

//显示输入的一段文字
void show(Lnode L)
{
	printf("%s\n", L.s);
}

//统计结果
void sta(Lnode L)
{
	int sum[4] = { 0 };
	int i;

	for (i = 0; i < L.l; i++)
	{
		if (L.s[i] >= '0' && L.s[i] <= '9') {
			sum[0] ++;
		}
		else if (L.s[i] >= 'a' && L.s[i] <= 'z' || L.s[i] >= 'A' && L.s[i] <= 'Z') {
			sum[1] ++;
		}
		else if (L.s[i] == ' ') {
			sum[2] ++;
		}
		else if (L.s[i] < 0) {
			sum[3] ++;
		}
	}

	printf("中文字符: %d\n", sum[3] / 2);
	printf("英文字符: %d\n", sum[1]);
	printf("空格: %d\n", sum[2]);
	printf("数字字符: %d\n", sum[0]);
	printf("总字数: %d\n",L.l);
}

//获取next值 
void GetNext(char* p, int* next, int len)
{
	int i = 2;//当前i下标
	int k = 0;//前一项的k
	next[0] = -1;
	next[1] = 0;
	while (i < len) {
		if (k == -1 || p[i - 1] == p[k]) {
			next[i] = k + 1;
			i++;
			k++;
		}
		else {
			k = next[k];
		}
	}
}

//KMP匹配算法 
int KMP_(char* s, char* p, int pos, int* next)
{
	int lens = strlen(s);
	int lenp = strlen(p);
	int i = pos;
	int j = 0;
	if (pos < 0 || pos >= lens)
		return -1;
	while (i < lens && j < lenp)
	{
		if (j == -1 || s[i] == p[j]) {
			i++; j++;
		}
		else {
			j = next[j];
		}
	}
	if (j >= lenp) {
		return i - j;
	}
	return -1;
}

//KMP算法得出结果 
int KMP(char* s, char* p)
{
	int pos = 0, count = 0;
	int next[11];

	GetNext(p, next, (int)(strlen(p)));//求出next数组

	while (1) {
		pos = KMP_(s, p, pos, next);
		if (pos == -1) {
			break;
		}
		count++;
		pos++;
	}

	return count;
}

//单词计数
void query(Lnode L)
{
	char p[1000];
	printf("输入一个单词: ");
	scanf("%s", p);
	printf("该单词的出现次数是: %d\n", KMP(L.s, p));
}

//从pos位置把p子串替换成c_p 
void swop(Lnode* L, char* p, char* c_p, int pos)
{
	int i, j, lenp = (int)(strlen(p));
	int lenp_c = (int)(strlen(c_p));

	if (lenp_c == lenp) {
		for (i = pos, j = 0; j < lenp_c; i++, j++) {
			L->s[i] = c_p[j];
		}
	}
	else if (lenp_c > lenp) {
		L->l += (lenp_c - lenp);
		for (i = L->l - 1; i > pos + lenp_c; i--)
		{
			L->s[i] = L->s[i - (lenp_c - lenp)];
		}
		for (i = pos, j = 0; j < lenp_c; i++ ,j++) {
			L->s[i] = c_p[j];
		}
		L->s[L->l] = '\0';
	}
	else {		
		L->l -= (lenp - lenp_c);
		for (i = pos; i < L->l; i++)
		{
			L->s[i] = L->s[i + (lenp - lenp_c)];
		}
		for (i = pos, j = 0; j < lenp_c; i++, j++) {
			L->s[i] = c_p[j];
		}
		L->s[L->l] = '\0';
	}
}

//替换字符串
void replace(Lnode* L)
{
	char p[1000], c_p[1000];
	int pos = 0;
	int next[11];
	printf("输入要替换的单词: ");
	scanf("%s", p);
	printf("输入替换后的单词: ");
	scanf("%s", c_p);



	GetNext(p, next, (int)(strlen(p)));//求出next数组

	while (1) {
		pos = KMP_(L->s, p, pos, next);
		if (pos == -1) {
			break;
		}
		swop(L, p, c_p, pos); //从pos位置把p子串替换成c_p
	}

	printf("替换完成\n");
}

//显示输入文字的行数
void query_n(Lnode L)
{
	int sum = 0;
	int i;

	for (i = 0; i < L.l; i++)
	{
		if (L.s[i] == '\n') {
			sum++;
		}
	}

	printf("一共: %d行\n", sum);
}


