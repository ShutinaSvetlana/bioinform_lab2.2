// BioinfLab2.1.cpp: определяет точку входа для консольного приложения.
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
{ //Функция вычисляет произведение элементов вектора.
	int R_res = 1;
	for (int i = 0; i < n; i++)
		R_res *= V[i];
	return R_res;
}

void Enumeration_Of_Values(char* s, int I, int* count_elem, int n)
{
	//	Функция генерирует определенный вектор k-значной логики, где каждый элемент может
	//	принимать разное максимальное значение, в полном переборе вариантов.
	//	Генерируется I вектор в этом полном переборе.
	int* count_in_block = new int[n];
	int  count = Count(count_elem, n);
	count_in_block[0] = count / count_elem[0];
	int* s1 = new int[n]; //мотив
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
	int N = l;//сколько параметров будет у алгоритма
	char* bestWord = new char[l];
	int *R = new int[N];//вектор числа повторений у циклов
	for (int i = 0; i < N; i++)
		R[i] = 4;
	
	int M = Count(R, N);//сколько итераций вообще будет

	char* s=new char[l]; //вектор текущих значений индексов имитируемых вложенных циклов	
	int bestDistance = TotalDistance(s, str, t, l);

	//основной цикл
	for (int i = 0; i < M; i++)
	{
		Enumeration_Of_Values(s, i, R, N);//теперь в s лежат нужные индексы
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

	ifstream input("input.txt"); // открыли файл для чтения	
	string l1; //размер шаблона
	input >> l1; //считали кол-во	

	int l; //размер шаблона
	l = atoi(l1.c_str()); //перевод в int	

	int count = 0; 
	string s; //строка		
	while (input)
	{
		getline(input, s); //считали строки из файла		
		count++; //кол-во строк
	}
	input.close(); // закрываем файл

	input.open("input.txt"); // открыли файл для чтения	

	int n = count - 2; //кол-во строк с буквами	

	string* str = new string[n]; //строка
	getline(input, str[0]); //считали первую строку из файла до конца
	for (int i = 0; i < n; i++)
		getline(input, str[i]);	

	char* result=new char[l]; //результат
	result = SearchMotif(str, n, l);

	input.close(); // закрываем файл

	ofstream output; //создаем файл для записи
	output.open("output.txt"); //открыли файл для записи		
	for (int i = 0; i < l; i++)
		output << result[i];
	output.close(); // закрываем файл	

	delete[] str;
	delete[] result;
	return 0;
}

