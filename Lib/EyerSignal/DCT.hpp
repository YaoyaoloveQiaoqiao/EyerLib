#ifndef EYERLIB_DCT_HPP
#define EYERLIB_DCT_HPP

#include <math.h>

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

        int DCT1D(T * inputArray, int inputArrayLen, T * uArray, int uLen)
        {
            for(int u=0;u<uLen;u++){
                T sum = 0;
                for(int i=0;i<inputArrayLen;i++){
                    sum += inputArray[i] * cos((i + 0.5) * M_PI / inputArrayLen * u);
                }

                uArray[u] = cu(u, inputArrayLen) * sum;
            }

            return 0;
        }

        T cu(int u, int n){
            if(u == 0){
                return sqrt(1.0 / n);
            }
            return sqrt(2.0 / n);
        }
    };
}

#endif //EYERLIB_DCT_HPP
