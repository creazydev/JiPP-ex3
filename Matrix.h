//
// Created by Kamil Nowak on 24/11/2020.
//

#ifndef EX1_MATRIX_H
#define EX1_MATRIX_H
#include <string>
#include <list>
#include <iostream>
using namespace std;

class Matrix {
public:
    Matrix(int n, int m);
    Matrix(int squareMatrixSize);
    Matrix(int n, int m, double ** &matrixArray);
    Matrix(string path);
    Matrix(const Matrix &matrix2);
    ~Matrix();

    //podstawowe funkcjonalnosci
    void set(int n, int m, double val);
    double get(int n, int m);
    Matrix add(Matrix &matrix2);
    Matrix subtract(Matrix &matrix2);
    Matrix multiply(Matrix &matrix2);
    int getCols();
    int getRows();
    void print();
    void store(string filename, string path);

    //przeciazone operatory
    Matrix operator +(Matrix &matrix2);
    Matrix operator -(Matrix &matrix2);
    Matrix operator *(Matrix &matrix2);
    friend ostream& operator <<(ostream &os, const Matrix &matrix);
    bool operator ==(const Matrix &matrix2);
    list<double> operator [](int rowIndex);

private:
    int rows, columns;
    double** matrixArray;
    double** allocateMemoryToMatrixArray(int n, int m, double ** &matrixArray);
    void readFromFile(string path);
    bool isElementPresent(int n, int m);
};
#endif //EX1_MATRIX_H
