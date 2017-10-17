#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <stdio.h>
using namespace std;

//Proxy-class for [][] operation
class Matrix_Row
{
private:
    double *row;
    size_t m;
public:

    Matrix_Row(double * a, int cnt) {
        row = a;
        m = cnt;
    }

    double& operator[](size_t i) {
        if (i >= m || i < 0) {
              assert(!"index out of range");
              exit(1);
        }
        return row[i];
    }
};

class  Matrix
{
private:

    size_t n; //rows count
    size_t m; //columns count
    double **arr;

public:

    Matrix (int row, int col)
    {
        arr = (double **)malloc(row * sizeof(double*) + row * col * sizeof(double));
        double *buf;
        buf = (double*)(arr + row);
        for (int i = 0; i < row; ++i) {
            arr[i] = buf + i * col;
        }
        n = row;
        m = col;
    }

    int columns()
    {
        return m;
    }

    int rows()
    {
        return n;
    }

    Matrix& operator=(Matrix mt)
    {
        int row = mt.n, col = mt.m;
        free(arr);
        arr = (double **)malloc(row * sizeof(double*) + row * col * sizeof(double));
        double *buf;
        buf = (double*)(arr + row);
        for (int i = 0; i < row; ++i) {
            arr[i] = buf + i * col;
        }
        n = row;
        m = col;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                arr[i][j] = mt.arr[i][j];
            }
        }
        return *this;
    }


    Matrix_Row operator[](size_t i)
    {
        if (i >= n || i < 0) {
              assert(!"index out of range");
              exit(1);
        }
        return Matrix_Row(arr[i], m); //m for check if column index our of range
    }

    Matrix& operator*=(vector <double> &v)
    {
        if (m != v.size()) {
            assert(!"the vector has an unsuitable length"); //during matrix multiplication on vector from right, vector size must be equal to matrix colimn count
            exit(1);
        }
        Matrix res = Matrix(n, 1);
        for (size_t i = 0; i < n; ++i) {
            res[i][0] = 0;
            for (size_t j = 0; j < m; ++j){
                res[i][0] += arr[i][j] * v[j];
            }
        }
        *this = res;
        return *this;
    }

    Matrix& operator*=(double k)
    {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                arr[i][j] *= k;
            }
        }
        return *this;
    }

    int operator==(Matrix mt)
    {
        if (n != mt.n || m != mt.m)
            return 0;
        int flag = 1;
        for (size_t i = 0; i < n && flag; ++i) {
            for (size_t j = 0; j < m && flag; ++j) {
                flag = arr[i][j] == mt.arr[i][j];
            }
        }
        return flag;
    }

    int operator!=(Matrix mt)
    {
        return !(*this == mt);
    }

    //with_size - flag of outputing matrix sizes
    //format - format string for 1 element of matrix
    void print(int with_size, char *format)
    {
        if (with_size) {
            printf("%u %u\n", n, m);
        }
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                printf(format, arr[i][j]);
            }
            printf("\n");
        }
    }

    //print version with standart format of each element outputing
    void print(int with_size)
    {
        print(with_size, "%lf ");
    }

    ~Matrix() {
        free(arr);
    }


};
