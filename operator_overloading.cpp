#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <cmath>
#include <iostream>
using namespace std;

class Matrix {
private:
	int** data;
	int rows;
	int cols;

    Matrix getMinor(int eRow, int eCol) const {
        Matrix minor(rows - 1, cols - 1);
        int minorRow = 0;
        for (int i = 0; i < rows; i++) {
            if (i == eRow) continue;
            int minorCol = 0;
            for (int j = 0; j < cols; j++) {
                if (j == eCol) continue;
                minorCol++;
                minor.data[minorRow][minorCol] = data[i][j];
            }
            minorRow++;
        }
        return minor;
    }

public:
	Matrix(int nRows, int nCols) : rows(nRows), cols(nCols) {
		data = new int* [rows];
		for (int i = 0; i < rows; i++) {
			data[i] = new int[cols];
			for (int j = 0; j < cols; j++) {
				data[i][j] = 0;
			}
		}
	}

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new int* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

	~Matrix() {
		for (int i = 0; i < rows; i++) {
			delete[] data[i];
		}
		delete[] data;
	}

    void display(int a = 0, int b = 0, int c = -1, int d = -1) const {
        c = c == -1 ? rows : c;
        d = d == -1 ? cols : d;
        a = a < 0 ? 0 : a;
        b = b < 0 ? 0 : b;
        if (a >= c or b >= d or c > rows or d > cols) {
            throw "Некорректный диапазон\n";
            return;
        }
        printf("Матрица %dх%d\n", rows, cols);
        for (int i = a; i < c; i++) {
            for (int j = b; j < d; j++) {
                printf("%d ", data[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    int get(int i, int j) const {
        if (i < 0 or i >= rows or j < 0 or j >= cols) {
            throw "Некорректные индексы\n";
        }
        return data[i][j];
    }

    void set(int i, int j, int value) {
        if (i < 0 or i >= rows or j < 0 or j >= cols) {
            throw "Некорректные индексы\n";
        }
        data[i][j] = value;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    bool isSquare() const {
        return rows == cols;
    }

    int determinant() const {
        if (!isSquare) {
            throw "Определитель можно вычислить только для квадратной матрицы\n";
        }
        if (rows == 1) {
            return data[0][0];
        }
        else if (rows == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
        else if (rows == 3) {
            return data[0][0] * data[1][1] * data[2][2] +
                data[0][1] * data[1][2] * data[2][0] +
                data[0][2] * data[1][0] * data[2][1] -
                data[0][2] * data[1][1] * data[2][0] -
                data[0][1] * data[1][0] * data[2][2] -
                data[0][0] * data[1][2] * data[2][1];
        }
        int det = 0;
        for (int j = 0; j < cols; j++) {
            Matrix minor = getMinor(0, j);
            int cofactor = (j % 2 == 0 ? 1 : -1) * data[0][j] * minor.determinant();
            det += cofactor;
        }
        return;
    }

    void fill(int value) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = value;
            }
        }
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows and cols != other.cols) {
            throw "Несовпадающие размеры матриц";
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator+(int scalar) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + scalar;
            }
        }
        return result;
    }

    Matrix& operator+=(int scalar) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] += scalar;
            }
        }
        return *this;
    }
    
    Matrix operator-(const Matrix& other) {
        if (rows != other.rows and cols != other.cols) {
            throw "Несовпадающие размеры матриц";
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(int scalar) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - scalar;
            }
        }
        return result;
    }

    Matrix& operator-=(int scalar) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] -= scalar;
            }
        }
        return *this;
    }

    Matrix& operator*=(int scalar) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] *= scalar;
            }
        }
        return *this;
    }

    Matrix operator*(const Matrix& other) {
        if (cols != other.rows) {
            throw "Несовместимые размеры матриц для умножения\n";
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        rows = other.rows;
        cols = other.cols;
        data = new int* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
        return *this;
    }
};
