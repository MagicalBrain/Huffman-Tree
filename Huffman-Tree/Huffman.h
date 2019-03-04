#pragma once
#include <iostream>
#include <string>

using namespace std;

#define TRUE 1
#define FALSE 0

#define OK 1
#define ERROR 0
//#define OVERFLOW -1

typedef int Status;

//�������������
#define ElemType char

//���еĽ��
struct TNode
{
	ElemType data;					//����ֵ
	int weight;						//����Ȩֵ
	int parent, left,right;		//���ڵ㡢�����ӽ����±��ַ
};


//��������������
struct hfCode
{
	ElemType data;
	string code;
};

//���������ṹ��
struct hfTree
{
	TNode *rcd;
	int length;
	//hfCode *result;

};


void BuildHftree(hfTree &T,int size,int w[],char v[])
//T:	Ҫ�����Ĺ�������
//size:		�������
//w:	Ȩ������
//v��	����������
{
	int min1, min2;
	int x, y;

	//�����ó�ֵ
	T.length = 2 * size;
	//����ռ�
	T.rcd = (TNode*)malloc(T.length * sizeof(TNode));

	//��ʼ��
	for (int i = size; i < T.length; i++)
	{
		T.rcd[i].weight = w[i - size];
		T.rcd[i].data = v[i - size];
		T.rcd[i].parent = T.rcd[i].left = T.rcd[i].right = 0;

	}

	//�鲢
	for (int i = size - 1; i > 0; i--)
	{
		min1 = min2 = 32767;
		x = y = 0;
		for (int j = i+1; j < T.length; j++)
		{
			if (T.rcd[j].parent == 0)
				if (T.rcd[j].weight < min1)
				{
					min2 = min1;
					min1 = T.rcd[j].weight;
					x = y;
					y = j;
				}
				else if (T.rcd[j].weight < min2)
				{
					//min1 = min2;
					min2 = T.rcd[j].weight;
					//y = x;
					x = j;
				}
			
		}

		T.rcd[i].weight = min1 + min2;
		T.rcd[i].parent = 0;
		T.rcd[i].right = y;
		T.rcd[i].left = x;
		T.rcd[x].parent = T.rcd[y].parent = i;
	}
	//return 0;
}


//�ӹ����������ɹ���������
void GetCode(hfTree T,hfCode result[])
{
	int size = T.length / 2;
	int p, s;

	for (int i = size; i < T.length; i++)
	{
		result[i - size].data = T.rcd[i].data;
		result[i - size].code = "";
		p = T.rcd[i].parent;
		s = i;
		string str00 = "0";
		string str01 = "1";
		while (p)
		{
			if (T.rcd[p].left == s)
				result[i - size].code = str00 + result[i - size].code;
			else
				result[i - size].code = str01 + result[i - size].code;
			s = p;
			p = T.rcd[p].parent;
		}
	}
}