#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

class Figure {
public:
    Figure() { }

    virtual ~Figure() { }

    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual double getVolume() const = 0; 
    virtual void printInfo() const = 0;
};

class EquilateralTriangle : public Figure {
protected:
    double side; 

public:
    EquilateralTriangle(double s = 1.0) : side(s > 0 ? s : 1.0) {}

    double getArea() const override {
        return (sqrt(3) / 4) * side * side;
    }

    double getPerimeter() const override {
        return 3 * side;
    }

    double getVolume() const override {
        return 0;
    }
            
    double getSide() const {
        return side;
    }
    
    void printInfo() const override {
        printf("Равносторонний треугольник:\n");
        printf("  Сторона: %.2f\n", side);
        printf("  Периметр: %.2f\n", getPerimeter());
        printf("  Площадь: %.2f\n", getArea());
        printf("  Объем: %.2f\n", getVolume());
    }
};

class TriangularPrism : public EquilateralTriangle {
private:
    double height;

public:
    TriangularPrism(double s = 1.0, double h = 1.0)
        : EquilateralTriangle(s), height(h > 0 ? h : 1.0) {
    }

    double getArea() const override {
        double baseArea = (sqrt(3) / 4) * side * side;
        double lateralArea = 3 * side * height;
        return 2 * baseArea + lateralArea;
    }

    double getVolume() const override {
        double baseArea = (sqrt(3) / 4) * side * side;
        return baseArea * height;
    }

    void printInfo() const override {
        printf("Правильная треугольная призма:\n");
        printf("  Сторона основания: %.2f\n", side);
        printf("  Высота призмы: %.2f\n", height);
        printf("  Площадь поверхности: %.2f\n", getArea());
        printf("  Объем: %.2f\n", getVolume());
        printf("  Периметр основания: %.2f\n", getPerimeter());
    }

    double getHeight() const {
        return height;
    }

    double getBaseArea() const {
        return EquilateralTriangle::getArea();
    }
};

int main() {
    setlocale(LC_ALL, "");
    int n, m;
    printf("Введите количество треугольников: ");
    scanf("%d", &n);
    printf("Введите количество призм: ");
    scanf("%d", &m);
    EquilateralTriangle** triangles = new EquilateralTriangle * [n];
    TriangularPrism** prisms = new TriangularPrism * [m];
    for (int i = 0; i < n; i++) {
        printf("Введите сторону треугольника %d: ", i + 1);
        double side;
        scanf("%lf", &side);
        triangles[i] = new EquilateralTriangle(side);
    }
    for (int i = 0; i < m; i++) {
        printf("Введите сторону основания и высоту для призмы %d: ", i + 1);
        double side, height;
        scanf("%lf %lf", &side, &height);
        prisms[i] = new TriangularPrism(side, height);
    }
    double totalArea = 0.0;
    for (int i = 0; i < n; i++) {
        totalArea += triangles[i]->getArea();
    }
    double averageArea = (n > 0) ? totalArea / n : 0.0;
    printf("Средняя площадь треугольников: %.2f\n", averageArea);
    int countLessThanAverage = 0;
    printf("Треугольники с площадью меньше средней (%.2f):\n", averageArea);
    for (int i = 0; i < n; i++) {
        double area = triangles[i]->getArea();
        if (area < averageArea) {
            countLessThanAverage++;
            printf("  %d. Площадь: %.2f\n", i + 1, area);
        }
    }
    printf("Количество таких треугольников: %d\n", countLessThanAverage);
    if (m > 0) {
        TriangularPrism* maxVolumePrism = prisms[0];
        double maxVolume = prisms[0]->getVolume();
        for (int i = 1; i < m; i++) {
            double volume = prisms[i]->getVolume();
            if (volume > maxVolume) {
                maxVolume = volume;
                maxVolumePrism = prisms[i];
            }
        }
        printf("\nПризма с наибольшим объемом:\n");
        printf("  Сторона основания: %.2f\n", maxVolumePrism->getSide());
        printf("  Высота: %.2f\n", maxVolumePrism->getHeight());
        printf("  Объем: %.2f\n", maxVolume);
        printf("  Площадь поверхности: %.2f\n", maxVolumePrism->getArea());
    }
    else {
        printf("\nПризмы не введены\n");
    }
}
