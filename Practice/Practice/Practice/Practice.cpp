/*
1) Учебная практика 2019
2) Губайдуллин Гарри Станиславович БПИ 182
3) Visual Studio 2017
4) Сортировки (с подсчетом кол-ва операций) массивов 4-х видов по возрастанию методами
	1. пузырька
	2. пузырька с условием Айверсона 1
	3. пузырька с условием Айверсона 1+2
	4. простых вставок
	5. бинарных вставок
   и вывод результатов в файл output.csv
5) Сортировки массивов по возрастанию методами
	1. подсчетом (устойчивая)
	2. цифровая
*/
#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

/* Bubble sort */

int bubble(int* mas, int n)
{
	int k = 2;				//i = 1; i < n
	for (int i = 1; i < n; i++)
	{
		k += 3;				//i < n; i++
		k += 3;				//j = 0; j < n - i
		for (int j = 0; j < n - i; j++)
		{
			k += 4;			//j < n - i; j++
			k += 4;			//mas[j] > mas[j + 1]
			if (mas[j] > mas[j + 1])
			{
				k += 9;		//exchange
				int temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
			}
		}
	}
	return k;
}

/* Bubble sort with Iverson's condition 1 */

int bubble_1(int* mas, int n)
{
	int k = 5;				//t = false; i = 1; (i < n) && !t
	bool t = false;
	for (int i = 1; (i < n) && !t; i++)
	{
		k += 5;				//(i < n) && !t; i++
		k += 1;				//t = true;
		k += 3;				//j = 0; j < n - i
		t = true;
		for (int j = 0; j < n - i; j++)
		{
			k += 4;			//j < n - i; j++
			k += 4;			//mas[j] > mas[j + 1]
			if (mas[j] > mas[j + 1])
			{
				k += 10;	//excange; t = false;
				int temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
				t = false;
			}
		}
	}
	return k;
}

/* Bubble sort with Iverson's conditions 1 and 2 */

int bubble_1_2(int* mas, int n)
{
	int k = 2;				//t = 1; bound = n
	int t = 1, bound = n;
	while (t != 0)
	{
		t = 0;
		k += 5;				//t != 0; j = 0; j < bound - 1
		for (int j = 0; j < bound - 1; j++)
		{
			k += 4;			//j < bound - 1; j++
			k += 4;			//mas[j] > mas[j + 1]
			if (mas[j] > mas[j + 1])
			{
				int temp = mas[j];
				mas[j] = mas[j + 1];
				mas[j + 1] = temp;
				t = j;
				k += 10;	//exchange; t = j
			}
		}
		bound = t + 1;
		k += 2;				//bound = t + 1
	}
	return k;
}

/* Insertion sort */

int insertion(int* mas, int n)
{
	int j, b, k;
	k = 2;				//i = 0; i < n
	for (int i = 1; i < n; i++)
	{
		k += 7;			//i < n; i++; j = i - 1; b = mas[i];
		j = i - 1;
		b = mas[i];
		while (mas[j] > b && j >= 0)
		{
			k += 10;	//mas[j] > b && j >= 0; mas[j + 1] = mas[j]; j -= 1;
			mas[j + 1] = mas[j];
			j -= 1;
		}
		mas[j + 1] = b;
		k += 3;			//mas[j + 1] = b;
	}
	return k;
}

/* Binary insertion sort */

int binary_insertion(int* mas, int n)
{
	int num, a1, a2, middle;
	int k = 2;				//i = 1; i < n
	for (int i = 1; i < n; i++)
	{
		k += 8;				//i < n; i++; num = mas[i]; a1 = 0; a2 = i - 1;
		num = mas[i];
		a1 = 0;
		a2 = i - 1;
		while (a1 < a2)
		{
			k += 5;			//a1 < a2; middle = a1 + (a2 - a1) / 2
			middle = a1 + (a2 - a1) / 2;
			if (num < mas[middle])
			{
				a2 = middle;
				k+=3;		//num < mas[middle]; a2 = middle
			}
			else
			{
				a1 = middle + 1;
				k += 2;		//a1 = middle + 1
			}
		}
		k += 3;				//j = i; j > a1 + 1
		for (int j = i; j > a1 + 1; j--)
		{
			mas[j] = mas[j - 1];
			k += 8;			//j > a1 + 1; j--; mas[j] = mas[j - 1]
		}
		mas[a1] = num;
		k += 2;				//mas[a1] = num;
	}
	return k;
}

int main()
{
	srand(time(0));
	int *mas1, *mas2, *working_arr, *reverse;
	int n = 1000, temp;
	ofstream ofs("output.csv");
	ofs << "Размер массива" << ";" << "Пузырек (1)" << ";" << "Пузырек (2)" << ";" << "Пузырек (3)" << ";" << "Пузырек (4)" << ";" << "Пузырек с условием Айверсона 1 (1)" << ";" << "Пузырек с условием Айверсона 1 (2)" << ";" << "Пузырек с условием Айверсона 1 (3)" << ";" << "Пузырек с условием Айверсона 1 (4)" << ";" << "Пузырек  с условием Айверсона 1+2 (1)" << ";" << "Пузырек с условием Айверсона 1+2 (2)" << ";" << "Пузырек с условием Айверсона 1+2 (3)" << ";" << "Пузырек с условием Айверсона 1+2 (4)" <<";"<< "Простые вставки (1)" << ";" << "Простые вставки (2)" << ";" << "Простые вставки (3)" << ";" << "Простые вставки (4)" << ";" << "Бинарные вставки (1)" << ";" << "Бинарные вставки (2)" << ";" << "Бинарные вставки (3)" << ";" << "Бинарные вставки (4)" << endl;
	do
	{
		/* Filling the array with random numbers */

		mas1 = new int[n];
		for (int i = 0; i < n; i++)
		{
			mas1[i] = rand() % 10;
		}
		mas2 = new int[n];
		for (int i = 0; i < n; i++)
		{
			mas2[i] = rand() % 10001;
		}
		working_arr = new int[n];

		/* Bubble sort */

		//0-9
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas1[i];
		}
		ofs << n << ";";
		ofs << bubble(working_arr, n) << ";";

		//0-10000
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas2[i];
		}
		ofs << bubble(working_arr, n) << ";";

		//Partly sorted 0-10000
		temp = working_arr[135]; working_arr[135] = working_arr[246]; working_arr[246] = temp;
		temp = working_arr[357]; working_arr[357] = working_arr[468]; working_arr[468] = temp;
		temp = working_arr[579]; working_arr[579] = working_arr[680]; working_arr[680] = temp;
		temp = working_arr[975]; working_arr[975] = working_arr[864]; working_arr[864] = temp;
		temp = working_arr[753]; working_arr[753] = working_arr[642]; working_arr[642] = temp;
		temp = working_arr[123]; working_arr[123] = working_arr[456]; working_arr[456] = temp;
		temp = working_arr[789]; working_arr[798] = working_arr[12]; working_arr[12] = temp;
		temp = working_arr[234]; working_arr[234] = working_arr[567]; working_arr[567] = temp;
		temp = working_arr[890]; working_arr[890] = working_arr[321]; working_arr[321] = temp;
		ofs << bubble(working_arr, n) << ";";

		//Reversed sorted array 10000-0
		reverse = new int[n];
		for (int i = 0; i < n; i++)
			reverse[i] = working_arr[n - 1 - i];
		ofs << bubble(working_arr, n) << ";";

		/* Bubble sort with Iverson's condition 1 */

		//0-9
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas1[i];
		}
		ofs << bubble_1(working_arr, n) << ";";

		//0-10000
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas2[i];
		}
		ofs << bubble_1(working_arr, n) << ";";

		//Partly sorted 0-10000
		temp = working_arr[135]; working_arr[135] = working_arr[246]; working_arr[246] = temp;
		temp = working_arr[357]; working_arr[357] = working_arr[468]; working_arr[468] = temp;
		temp = working_arr[579]; working_arr[579] = working_arr[680]; working_arr[680] = temp;
		temp = working_arr[975]; working_arr[975] = working_arr[864]; working_arr[864] = temp;
		temp = working_arr[753]; working_arr[753] = working_arr[642]; working_arr[642] = temp;
		temp = working_arr[123]; working_arr[123] = working_arr[456]; working_arr[456] = temp;
		temp = working_arr[789]; working_arr[798] = working_arr[12]; working_arr[12] = temp;
		temp = working_arr[234]; working_arr[234] = working_arr[567]; working_arr[567] = temp;
		temp = working_arr[890]; working_arr[890] = working_arr[321]; working_arr[321] = temp;
		ofs << bubble_1(working_arr, n) << ";";

		//Reversed sorted array 10000-0
		reverse = new int[n];
		for (int i = 0; i < n; i++)
			reverse[i] = working_arr[n - 1 - i];
		ofs << bubble_1(working_arr, n) << ";";

		/* Bubble sort with Iverson's conditions 1 and 2 */

		//0-9
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas1[i];
		}
		ofs << bubble_1_2(working_arr, n) << ";";
		//0-10000
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas2[i];
		}
		ofs << bubble_1_2(working_arr, n) << ";";

		//Partly sorted 0-10000
		temp = working_arr[135]; working_arr[135] = working_arr[246]; working_arr[246] = temp;
		temp = working_arr[357]; working_arr[357] = working_arr[468]; working_arr[468] = temp;
		temp = working_arr[579]; working_arr[579] = working_arr[680]; working_arr[680] = temp;
		temp = working_arr[975]; working_arr[975] = working_arr[864]; working_arr[864] = temp;
		temp = working_arr[753]; working_arr[753] = working_arr[642]; working_arr[642] = temp;
		temp = working_arr[123]; working_arr[123] = working_arr[456]; working_arr[456] = temp;
		temp = working_arr[789]; working_arr[798] = working_arr[12]; working_arr[12] = temp;
		temp = working_arr[234]; working_arr[234] = working_arr[567]; working_arr[567] = temp;
		temp = working_arr[890]; working_arr[890] = working_arr[321]; working_arr[321] = temp;
		ofs << bubble_1_2(working_arr, n) << ";";

		//Reversed sorted array 10000-0
		reverse = new int[n];
		for (int i = 0; i < n; i++)
			reverse[i] = working_arr[n - 1 - i];
		ofs << bubble_1_2(working_arr, n) << ";";

		/* Insertion sort */

		//0-9
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas1[i];
		}
		ofs << insertion(working_arr, n) << ";";

		//0-10000
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas2[i];
		}
		ofs << insertion(working_arr, n) << ";";

		//Partly sorted 0-10000
		temp = working_arr[135]; working_arr[135] = working_arr[246]; working_arr[246] = temp;
		temp = working_arr[357]; working_arr[357] = working_arr[468]; working_arr[468] = temp;
		temp = working_arr[579]; working_arr[579] = working_arr[680]; working_arr[680] = temp;
		temp = working_arr[975]; working_arr[975] = working_arr[864]; working_arr[864] = temp;
		temp = working_arr[753]; working_arr[753] = working_arr[642]; working_arr[642] = temp;
		temp = working_arr[123]; working_arr[123] = working_arr[456]; working_arr[456] = temp;
		temp = working_arr[789]; working_arr[798] = working_arr[12]; working_arr[12] = temp;
		temp = working_arr[234]; working_arr[234] = working_arr[567]; working_arr[567] = temp;
		temp = working_arr[890]; working_arr[890] = working_arr[321]; working_arr[321] = temp;
		ofs << insertion(working_arr, n) << ";";

		//Reversed sorted array 10000-0
		reverse = new int[n];
		for (int i = 0; i < n; i++)
			reverse[i] = working_arr[n - 1 - i];
		ofs << insertion(working_arr, n) << ";";

		/* Binary insertion sort */

		//0-9
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas1[i];
		}
		ofs << binary_insertion(working_arr, n) << ";";

		//0-10000
		for (int i = 0; i < n; i++)
		{
			working_arr[i] = mas2[i];
		}
		ofs << binary_insertion(working_arr, n) << ";";

		//Partly sorted 0-10000
		temp = working_arr[135]; working_arr[135] = working_arr[246]; working_arr[246] = temp;
		temp = working_arr[357]; working_arr[357] = working_arr[468]; working_arr[468] = temp;
		temp = working_arr[579]; working_arr[579] = working_arr[680]; working_arr[680] = temp;
		temp = working_arr[975]; working_arr[975] = working_arr[864]; working_arr[864] = temp;
		temp = working_arr[753]; working_arr[753] = working_arr[642]; working_arr[642] = temp;
		temp = working_arr[123]; working_arr[123] = working_arr[456]; working_arr[456] = temp;
		temp = working_arr[789]; working_arr[798] = working_arr[12]; working_arr[12] = temp;
		temp = working_arr[234]; working_arr[234] = working_arr[567]; working_arr[567] = temp;
		temp = working_arr[890]; working_arr[890] = working_arr[321]; working_arr[321] = temp;
		ofs << binary_insertion(working_arr, n) << ";";

		//Reversed sorted array 10000-0
		reverse = new int[n];
		for (int i = 0; i < n; i++)
			reverse[i] = working_arr[n - 1 - i];
		ofs << binary_insertion(working_arr, n) << endl;

		n += 1000;
	} while (n < 8001);
	ofs.close();
	delete[] mas1;
	delete[] mas2;
	delete[] working_arr;
	delete[] reverse;
	return 0;
}