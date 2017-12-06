// BioinfLab2.1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "stdio.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include"algorithm"
using namespace std;

int Count(int* V, int n)
{ //������� ��������� ������������ ��������� �������.
	int R_res = 1;
	for (int i = 0; i < n; i++)
		R_res *= V[i];
	return R_res;
}

void Enumeration_Of_Values(char* s, int I, int* count_elem, int n)
{
	//	������� ���������� ������������ ������ k-������� ������, ��� ������ ������� �����
	//	��������� ������ ������������ ��������, � ������ �������� ���������.
	//	������������ I ������ � ���� ������ ��������.
	int* count_in_block = new int[n];
	int  count = Count(count_elem, n);
	count_in_block[0] = count / count_elem[0];
	int* s1 = new int[n]; //�����
	for (int i = 1; i < n; i++)
		count_in_block[i] = count_in_block[i - 1] / count_elem[i];

	for (int i = 0; i < n; i++)
		s1[i] = (I / count_in_block[i]) % count_elem[i];
	for (int i = 0; i < n; i++)
	{
		if (s1[i] == 0)
			s[i] = 'A';
		else
			if (s1[i] == 1)
				s[i] = 'C';
			else
				if (s1[i] == 2)
					s[i] = 'G';
				else
					s[i] = 'T';
	}
	delete[] count_in_block;
	delete[] s1;
}

int TotalDistance(char* s, string* str, int t, int l)
{
	int score = 0;
	char new_s[100];	
	int* count = new int[t];
	int m = 0;
	for (int j = 0; j < t; j++)
	{
		int count_in_str = l;
		for (int i = 0; i < strlen(str[j].c_str()) - 1; i = i + l)
		{
			strncpy_s(new_s, str[j].c_str() + i, l);
			for (int k = 0; k < l; k++)
				if (new_s[k] != s[k])
					m++;
			if (m < count_in_str)
				count_in_str = m;
			m = 0;
		}
		count[j] = count_in_str;
		score += count[j];
	}

	delete[] count;

	return score;
}


char* SearchMotif(string* str, int t, int l)
{
	int N = l;//������� ���������� ����� � ���������
	char* bestWord = new char[l];
	int *R = new int[N];//������ ����� ���������� � ������
	for (int i = 0; i < N; i++)
		R[i] = 4;
	
	int M = Count(R, N);//������� �������� ������ �����

	char* s=new char[l]; //������ ������� �������� �������� ����������� ��������� ������	
	int bestDistance = TotalDistance(s, str, t, l);

	//�������� ����
	for (int i = 0; i < M; i++)
	{
		Enumeration_Of_Values(s, i, R, N);//������ � s ����� ������ �������
		if (TotalDistance(s, str, t, l) <= bestDistance)
		{
			bestDistance = TotalDistance(s, str, t, l);
			for (int j = 0; j < l; j++)
				bestWord[j] = s[j];
		}
	}

	delete[] R;
	delete[] s;

	return bestWord;
}

int main()
{
	setlocale(LC_ALL, ".1251");

	ifstream input("input.txt"); // ������� ���� ��� ������	
	string l1; //������ �������
	input >> l1; //������� ���-��	

	int l; //������ �������
	l = atoi(l1.c_str()); //������� � int	

	int count = 0; 
	string s; //������		
	while (input)
	{
		getline(input, s); //������� ������ �� �����		
		count++; //���-�� �����
	}
	input.close(); // ��������� ����

	input.open("input.txt"); // ������� ���� ��� ������	

	int n = count - 2; //���-�� ����� � �������	

	string* str = new string[n]; //������
	getline(input, str[0]); //������� ������ ������ �� ����� �� �����
	for (int i = 0; i < n; i++)
		getline(input, str[i]);	

	char* result=new char[l]; //���������
	result = SearchMotif(str, n, l);

	input.close(); // ��������� ����

	ofstream output; //������� ���� ��� ������
	output.open("output.txt"); //������� ���� ��� ������		
	for (int i = 0; i < l; i++)
		output << result[i];
	output.close(); // ��������� ����	

	delete[] str;
	delete[] result;
	return 0;
}

