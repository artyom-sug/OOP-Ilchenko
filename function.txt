#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

int N;

int count_pos(int* X, int sz) { //ф-ция для подсчёта положительных чисел
	int cnt = 0;
	for (int i = 0; i < sz; i++) {
		if (X[i] > 0) cnt++;
	}
	return cnt;
}

int* insert(int* X, int& sz) { //ф-ция для вставки 0 после положительных чисел
	int n_sz = sz + count_pos(X, sz);
	printf("Новый размер массива: %i\n", n_sz);
	int* Y = new int[n_sz];
	for (int i = 0, j = 0; i < sz; i++) {
		Y[j++] = X[i];
		if (X[i] > 0) Y[j++] = 0;
	}
	sz = n_sz;
	return Y;
}

double arithmetic_mean(int* X, int sz) { //ф-ция для поиска среднего арифметического
	double sum = 0;
	for (int i = 0; i < sz; i++) {
		sum += X[i];
	}
	return sum / sz;
}

void print_array(int* A, int sz) { //ф-ция для вывода массива 
	for (int i = 0; i < sz; i++) {
		printf("%i ", A[i]); 
	}
	printf("\n");
}

int search_max(int* A, int sz) { //ф-ция для поиска максимального числа
	int mx = 0;
	for (int i = 0; i < sz; i++) {
		mx = (A[i] > mx ? A[i] : mx);
	}
	return mx;
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "");
	printf("Укажите размер массива: ");
	scanf("%i", &N);
	int* X = new int[N];
	int size = N;
	for (int i = 0; i < N; i++) {
		X[i] = rand() % 201 - 100;
	}
	printf("Массив X: ");
	print_array(X, size);
	printf("Среднее арифметическое значение массива X: %.5f\n", arithmetic_mean(X, size));
	printf("Максимальное значение массива X: %i\n", search_max(X, size));
	int* Y = insert(X, size);
	printf("Массив Y: ");
	print_array(Y, size);
	printf("Среднее арифметическое значение массива Y: %.5f\n", arithmetic_mean(Y, size));
	printf("Максимальное значение массива Y: %i\n", search_max(Y, size));
	delete[] X;
	delete[] Y;
}
