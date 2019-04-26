#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

/* This file contains the logic gate function bodies*/

int not_gate(int x)
{
	return (!x);
}
int and_gate(int x, int y) /* and gate only returns 1 if both A and B are 1*/
{
	return (x && y);
}

int nand_gate(int x, int y) /* nand gate returns 1 for the opposite of the and gate*/
{
	return !(x && y);
}

int or_gate(int x, int y) /* or gate returns 1 if A or B is 1*/
{
	return (x || y);
}

int nor_gate(int x, int y) /* nor gate returns 1 for the opposite of the or gate*/
{
	return !(x || y);
}

int xor_gate(int x, int y) /* xor gate returns 1 if A is 0 and B is 1 or if A is 1 and B is 0*/
{
	return ((!x) && y) || (x && (!y));
}

int xnor_gate(int x, int y) /* xnor gate returns the opposite of the xor gate*/
{
	return ((x && y) || (!x && !y));
}

int and_n(int x[], int size)
{
	int flag = 0;
	for (int i = 0; i < size; i++)
	{
		if (x[i] == 0)
			flag = 1;
	}

	if (flag == 1)
		return 0;
	else
		return 1;
}
int or_n(int x[], int size)
{
	int flag = 0;
	for (int i = 0; i < size; i++)
	{
		if (x[i] == 1)
			flag = 1;
	}

	if (flag == 1)
		return 1;
	else
		return 0;
}