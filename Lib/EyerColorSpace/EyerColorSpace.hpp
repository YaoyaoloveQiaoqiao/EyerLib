//
// Created by chuchun on 2021/2/7.
//

#ifndef EYERLIB_EYERCOLORSPACE_H
#define EYERLIB_EYERCOLORSPACE_H

#include <iostream>
#include <cstdio>

namespace Eyer
{
    class EyerColorSpace
    {
    public:
        EyerColorSpace();
        ~EyerColorSpace();
        int Convert();
    };


    class Matrix{
    public:
        Matrix();
        ~Matrix();
        int get_size() const;
        void inverse();
        void show() const;
        void initialize();
        void lupDecomposition(int (*p)[100], double (*left)[100], double (*up)[100]);

    private:
        double data[100][100];
        int rowsize, colsize;
        double* lupSolve(double (*left)[100], double (*up)[100], int *position, double *b);
    };
}
#endif //EYERLIB_EYERCOLORSPACE_H
