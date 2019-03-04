#include <iostream>
#include "Huffman.h"

using namespace std;

int main()
{
	int ch[] = { 'a','e','i','s','t','d','n' };
	int w[] = { 10,15,12,3,4,13,1 };
	hfTree T;
	BuildHftree(T, 7, w, ch);
	hfCode result[7];
	GetCode(T, result);
	for (int i = 0; i < 7; i++)
	{
		cout << result[i].data <<"	"<<result[i].code<< endl;
	}
	return 0;
}