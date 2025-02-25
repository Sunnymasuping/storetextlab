#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char s[10000];
	int l;
}Lnode;


void input(Lnode* L); //����һ������ 
void show(Lnode L);//��ʾ�����һ������
void sta(Lnode L);//ͳ�ƽ��
void query(Lnode L);//���ʼ���
void replace(Lnode* L);//�滻�ַ��� 
void query_n(Lnode L); //��ʾ�������ֵ�����

int main()
{
	Lnode L;
	int c;

	input(&L); //����һ������ 
	while (1)
	{
		printf("1. ��ʾ�����һ������\n");
		printf("2. ͳ�ƽ��\n");
		printf("3. ���ʼ���\n");
		printf("4. �滻�ַ���\n");
		printf("5. ��ʾ�������ֵ�����\n");
		printf("0. �˳�ϵͳ\n");
		printf("��ѡ��: ");
		scanf("%d", &c);
		switch (c)
		{
		case 1: show(L); break;//��ʾ�����һ������
		case 2: sta(L); break;//ͳ�ƽ��
		case 3: query(L); break;//���ʼ���
		case 4: replace(&L); break;//�滻�ַ���
		case 5: query_n(L); break;//��ʾ�������ֵ�����
		case 0: return 0;
		}
	}
	return 0;
}

//����һ������ 
void input(Lnode* L)
{
	char c;
	int l = 0;

	printf("����һ������,�Իس���������\n");
	while ((scanf("%c", &c)) != EOF)
	{
		L->s[l++] = c;
	}
	L->s[l] = '\0';
	L->l = l;
}

//��ʾ�����һ������
void show(Lnode L)
{
	printf("%s\n", L.s);
}

//ͳ�ƽ��
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

	printf("�����ַ�: %d\n", sum[3] / 2);
	printf("Ӣ���ַ�: %d\n", sum[1]);
	printf("�ո�: %d\n", sum[2]);
	printf("�����ַ�: %d\n", sum[0]);
	printf("������: %d\n",L.l);
}

//��ȡnextֵ 
void GetNext(char* p, int* next, int len)
{
	int i = 2;//��ǰi�±�
	int k = 0;//ǰһ���k
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

//KMPƥ���㷨 
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

//KMP�㷨�ó���� 
int KMP(char* s, char* p)
{
	int pos = 0, count = 0;
	int next[11];

	GetNext(p, next, (int)(strlen(p)));//���next����

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

//���ʼ���
void query(Lnode L)
{
	char p[1000];
	printf("����һ������: ");
	scanf("%s", p);
	printf("�õ��ʵĳ��ִ�����: %d\n", KMP(L.s, p));
}

//��posλ�ð�p�Ӵ��滻��c_p 
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

//�滻�ַ���
void replace(Lnode* L)
{
	char p[1000], c_p[1000];
	int pos = 0;
	int next[11];
	printf("����Ҫ�滻�ĵ���: ");
	scanf("%s", p);
	printf("�����滻��ĵ���: ");
	scanf("%s", c_p);



	GetNext(p, next, (int)(strlen(p)));//���next����

	while (1) {
		pos = KMP_(L->s, p, pos, next);
		if (pos == -1) {
			break;
		}
		swop(L, p, c_p, pos); //��posλ�ð�p�Ӵ��滻��c_p
	}

	printf("�滻���\n");
}

//��ʾ�������ֵ�����
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

	printf("һ��: %d��\n", sum);
}


