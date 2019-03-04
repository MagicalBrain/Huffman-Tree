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

//结点中数据类型
#define ElemType char

//树中的结点
struct TNode
{
	ElemType data;					//结点的值
	int weight;						//结点的权值
	int parent, left,right;		//父节点、左右子结点的下标地址
};


//哈夫曼编码类型
struct hfCode
{
	ElemType data;
	string code;
};

//哈夫曼树结构体
struct hfTree
{
	TNode *rcd;
	int length;
	//hfCode *result;

};


void BuildHftree(hfTree &T,int size,int w[],char v[])
//T:	要构建的哈夫曼树
//size:		编码个数
//w:	权重数组
//v：	被编码数组
{
	int min1, min2;
	int x, y;

	//长度置初值
	T.length = 2 * size;
	//分配空间
	T.rcd = (TNode*)malloc(T.length * sizeof(TNode));

	//初始化
	for (int i = size; i < T.length; i++)
	{
		T.rcd[i].weight = w[i - size];
		T.rcd[i].data = v[i - size];
		T.rcd[i].parent = T.rcd[i].left = T.rcd[i].right = 0;

	}

	//归并
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


//从哈夫曼树生成哈弗曼编码
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