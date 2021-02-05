#ifndef EYERLIB_DCT_HPP
#define EYERLIB_DCT_HPP

#include <math.h>
#include <stdio.h>
#include "EyerMath/EyerMath.hpp"

namespace Eyer
{
    template<typename T>
    class DCT {
    public:
        DCT()
        {

        }

        ~DCT()
        {

        }

        int DCT2D(Eatrix<T> & input, Eatrix<T> & out)
        {
            for(int y=0;y<out.row;y++) {
                for (int x = 0; x < out.col; x++) {
                    double r = DCT2DA(input, out, x, y);
                    printf(" %f ", r);
                    out.Set(y, x, (T)(r / 255.0));
                }
                printf("\n");
            }

            printf("\n");
            printf("\n");
            printf("\n");

            return 0;
        }

        double DCT2DA(Eatrix<T> & input, Eatrix<T> & out, int u, int v)
        {
            double sum = 0;
            for(int y=0;y<input.row;y++){
                for(int x=0;x<input.col;x++){
                    T Fij = input.Get(y, x);
                    double a = cos( (x + 0.5) * M_PI / input.col * u);
                    double b = cos( (y + 0.5) * M_PI / input.row * v);

                    sum += Fij * a * b;
                }
            }

            return sum;
        }

        int DCT1D(T * inputArray, int inputArrayLen, T * uArray, int uLen)
        {
            for(int u=0;u<uLen;u++){
                long long sum = 0;
                for(int i=0;i<inputArrayLen;i++){
                    sum += inputArray[i] * cos((i + 0.5) * M_PI / inputArrayLen * u);
                }

                uArray[u] = c(u, inputArrayLen) * sum;
            }

            return 0;
        }

        double c(int u, int n){
            if(u == 0){
                return sqrt(1.0 / n);
            }
            return sqrt(2.0 / n);
        }
    };
}

#endif //EYERLIB_DCT_HPP
