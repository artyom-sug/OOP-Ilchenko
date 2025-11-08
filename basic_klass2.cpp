#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

class Matrix {
private:
	int** data;
	int rows;
	int cols;

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

    void resize(int nRows, int nCols) {
        int** nData = new int* [nRows];
        for (int i = 0; i < nRows; i++) {
            nData[i] = new int[nCols];
            for (int j = 0; j < nCols; j++) {
                if (i < rows && j < cols) {
                    nData[i][j] = data[i][j];
                }
                else {
                    nData[i][j] = 0;
                }
            }
        }
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nData;
        rows = nRows;
        cols = nCols;
    }

    void display(int a = 0, int b = 0, int c = -1, int d = -1) const {
        c = c == -1 ? rows : c;
        d = d == -1 ? cols : d;
        a = a < 0 ? 0 : a;
        b = b < 0 ? 0 : b;
        if (a >= c or b >= d or c > rows or d > cols) {
            printf("Некорректный диапазон\n");
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
            printf("Некорректные индексы\n");
            return -1;
        }
        return data[i][j];
    }

    void set(int i, int j, int value) {
        if (i < 0 or i >= rows or j < 0 or j >= cols) {
            printf("Некорректные индексы\n");
            return;
        }
        data[i][j] = value;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

void printMenu() {
    printf("=== МЕНЮ РАБОТЫ С МАТРИЦЕЙ ===\n");
    printf("1. Создать новую матрицу\n");
    printf("2. Изменить размер матрицы\n");
    printf("3. Установить значение элемента\n");
    printf("4. Получить значение элемента\n");
    printf("5. Вывести всю матрицу\n");
    printf("6. Вывести подматрицу\n");
    printf("7. Показать размеры матрицы\n");
    printf("8. Создать копию матрицы\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    setlocale(LC_ALL, "Russian");

    Matrix* matrix = nullptr;
    Matrix* matrixCopy = nullptr;
    int choice;

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            if (matrix != nullptr) {
                delete matrix;
            }
            int rows, cols;
            printf("Введите количество строк: ");
            scanf("%d", &rows);
            printf("Введите количество столбцов: ");
            scanf("%d", &cols);

            if (rows > 0 && cols > 0) {
                matrix = new Matrix(rows, cols);
                printf("Матрица %dx%d создана успешно!\n", rows, cols);
            }
            else {
                printf("Некорректные размеры!\n");
                matrix = nullptr;
            }
            break;
        }

        case 2: {
            if (matrix == nullptr) {
                printf("Сначала создайте матрицу!\n");
                break;
            }
            int newRows, newCols;
            printf("Текущий размер: %dx%d\n", matrix->getRows(), matrix->getCols());
            printf("Введите новое количество строк: ");
            scanf("%d", &newRows);
            printf("Введите новое количество столбцов: ");
            scanf("%d", &newCols);

            if (newRows > 0 && newCols > 0) {
                matrix->resize(newRows, newCols);
                printf("Размер матрицы изменен на %dx%d\n", newRows, newCols);
            }
            else {
                printf("Некорректные размеры!\n");
            }
            break;
        }

        case 3: {
            if (matrix == nullptr) {
                printf("Сначала создайте матрицу!\n");
                break;
            }
            int i, j, value;
            printf("Введите индекс строки: ");
            scanf("%d", &i);
            printf("Введите индекс столбца: ");
            scanf("%d", &j);
            printf("Введите значение: ");
            scanf("%d", &value);

            matrix->set(i, j, value);
            printf("Значение установлено\n");
            break;
        }

        case 4: {
            if (matrix == nullptr) {
                printf("Сначала создайте матрицу!\n");
                break;
            }
            int i, j;
            printf("Введите индекс строки: ");
            scanf("%d", &i);
            printf("Введите индекс столбца: ");
            scanf("%d", &j);

            int value = matrix->get(i, j);
            if (value != -1) {
                printf("matrix[%d][%d] = %d\n", i, j, value);
            }
            break;
        }

        case 5: {
            if (matrix == nullptr) {
                printf("Сначала создайте матрицу!\n");
                break;
            }
            matrix->display();
            break;
        }

        case 6: {
            if (matrix == nullptr) {
                printf("Сначала создайте матрицу!\n");
                break;
            }
            int a, b, c, d;
            printf("Введите начальную строку: ");
            scanf("%d", &a);
            printf("Введите начальный столбец: ");
            scanf("%d", &b);
            printf("Введите конечную строку: ");
            scanf("%d", &c);
            printf("Введите конечный столбец: ");
            scanf("%d", &d);

            matrix->display(a, b, c, d);
            break;
        }

        case 7: {
            if (matrix == nullptr) {
                printf("Сначала создайте матрицу!\n");
                break;
            }
            printf("Размер матрицы: %d строк x %d столбцов\n",
                matrix->getRows(), matrix->getCols());
            break;
        }

        case 8: {
            if (matrix == nullptr) {
                printf("Сначала создайте матрицу!\n");
                break;
            }
            if (matrixCopy != nullptr) {
                delete matrixCopy;
            }
            matrixCopy = new Matrix(*matrix);
            printf("Копия матрицы создана успешно!\n");
            printf("Исходная матрица:\n");
            matrix->display();
            printf("Копия матрицы:\n");
            matrixCopy->display();
            break;
        }

        case 0:
            printf("Выход из программы...\n");
            break;

        default:
            printf("Неверный выбор! Попробуйте снова.\n");
        }

    } while (choice != 0);

    if (matrix != nullptr) {
        delete matrix;
    }
    if (matrixCopy != nullptr) {
        delete matrixCopy;
    }
}
