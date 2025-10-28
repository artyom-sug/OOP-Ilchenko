#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

class Tetragon {
private:
	struct point { double x, y; };
	point A, B, C, D;

	double distance(const point& p1, const point& p2) const {
		return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	}
	
public:
	Tetragon(double xa = 0, double xb = 0, double xc = 0, double xd = 0, double ya = 0, double yb = 0, double yc = 0, double yd = 0) :
		A{ xa,ya }, B{ xb, yb }, C{ xc, yc }, D{ xd, yd } { }

	Tetragon(Tetragon& other): A(other.A), B(other.B), C(other.C), D(other.D) { }

	~Tetragon() {}

	double getAx() const { return A.x; }
	double getAy() const { return A.y; }
	double getBx() const { return B.x; }
	double getBy() const { return B.y; }
	double getCx() const { return C.x; }
	double getCy() const { return C.y; }
	double getDx() const { return D.x; }
	double getDy() const { return D.y; }

	void setAx(double x) { A.x = x; }
	void setAy(double y) { A.y = y; }
	void setBx(double x) { B.x = x; }
	void setBy(double y) { B.y = y; }
	void setCx(double x) { C.x = x; }
	void setCy(double y) { C.y = y; }
	void setDx(double x) { D.x = x; }
	void setDy(double y) { D.y = y; }

	double getSideAB() const { return distance(A, B); }
	double getSideBC() const { return distance(B, C); }
	double getSideCD() const { return distance(C, D); }
	double getSideDA() const { return distance(D, A); }

	double getDiagonalAC() const { return distance(A, C); }
	double getDiagonalBD() const { return distance(B, D); }

	double getPerimeter() const {
		return getSideAB() + getSideBC() + getSideCD() + getSideDA();
	}

	double getArea() const {
		double sum1 = A.x * B.y + B.x * C.y + C.x * D.y + D.x * A.y;
		double sum2 = A.y * B.x + B.y * C.x + C.y * D.x + D.y * A.x;
		double dif = sum1 - sum2;
		return 0.5 * (dif > 0 ? dif : -dif);
	}
};

void printTetragonInfo(const Tetragon& t);

int main() {
	setlocale(LC_ALL, "");
	// 1. Создание объекта с помощью конструктора по умолчанию
	printf("Четырехугольник по умолчанию (квадрат 1x1):\n");
	Tetragon t1;
	printTetragonInfo(t1);
	// Создание объекта с параметрами (прямоугольник)
	printf("Прямоугольник со сторонами 3 и 4:\n");
	Tetragon t2(0, 3, 3, 0, 0, 0, 4, 4);
	printTetragonInfo(t2);
	// Создание произвольного четырехугольника
	printf("Произвольный четырехугольник:\n");
	Tetragon t3(0, 4, 6, 2, 0, 3, 3, 5);
	printTetragonInfo(t3);
	// Использование конструктора копирования
	printf("Копия произвольного четырехугольника (конструктор копирования):\n");
	Tetragon t4(t3);
	printTetragonInfo(t4);
	// Демонстрация работы методов set/get
	printf("Изменение координат через методы set:\n");
	Tetragon t5;
	printf("До изменения:\n");
	printf("A(%.2f, %.2f)\n", t5.getAx(), t5.getAy());
	t5.setAx(5); t5.setAy(5); t5.setBx(10); t5.setBy(5); t5.setCx(10); t5.setCy(10); t5.setDx(5); t5.setDy(10);
	printf("После изменения:\n");
	printTetragonInfo(t5);
	// Создание ромба
	printf("Ромб:\n");
	Tetragon rhombus(0, 3, 4, 1, 0, 4, 3, -1);
	printTetragonInfo(rhombus);
	// Демонстрация вычисления площади для разных фигур
	printf("Сравнение площадей:\n");
	// Квадрат 2x2
	Tetragon square(0, 2, 2, 0, 0, 0, 2, 2);
	printf("Квадрат 2x2 - площадь: %.2f\n", square.getArea());
	// Прямоугольник 3x4  
	Tetragon rectangle(0, 3, 3, 0, 0, 0, 4, 4);
	printf("Прямоугольник 3x4 - площадь: %.2f\n", rectangle.getArea());
	// Трапеция
	Tetragon trapezoid(0, 4, 3, 1, 0, 0, 3, 3);
	printf("Трапеция - площадь: %.2f\n", trapezoid.getArea());
}

void printTetragonInfo(const Tetragon& t) {
	printf("Координаты вершин:\n");
	printf("A(%.2f, %.2f)\n", t.getAx(), t.getAy());
	printf("B(%.2f, %.2f)\n", t.getBx(), t.getBy());
	printf("C(%.2f, %.2f)\n", t.getCx(), t.getCy());
	printf("D(%.2f, %.2f)\n", t.getDx(), t.getDy());
	printf("Длины сторон:\n");
	printf("AB = %.2f\n", t.getSideAB());
	printf("BC = %.2f\n", t.getSideBC());
	printf("CD = %.2f\n", t.getSideCD());
	printf("DA = %.2f\n", t.getSideDA());
	printf("Диагонали:\n");
	printf("AC = %.2f\n", t.getDiagonalAC());
	printf("BD = %.2f\n", t.getDiagonalBD());
	printf("Периметр: %.2f\n", t.getPerimeter());
	printf("Площадь: %.2f\n", t.getArea());
	printf("\n");
}
