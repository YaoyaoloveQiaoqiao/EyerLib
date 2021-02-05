#ifndef EYERLIB_RESIDUAL_TYPE_HPP
#define EYERLIB_RESIDUAL_TYPE_HPP

#include "EyerEnum.hpp"
namespace Eyer
{
    class RESIDUAL_TYPE : public EyerEnum{
    public:
        RESIDUAL_TYPE(int _val, const EyerString & _name);
        RESIDUAL_TYPE(const RESIDUAL_TYPE & residualType);
        RESIDUAL_TYPE(const int & residualType);
        ~RESIDUAL_TYPE();

        RESIDUAL_TYPE & operator = (const RESIDUAL_TYPE & residualType);
        bool operator == (const RESIDUAL_TYPE & residualType);
        bool operator != (const RESIDUAL_TYPE & residualType);

    public:
        static RESIDUAL_TYPE LUMA;
        static RESIDUAL_TYPE CHROMA_CR;
        static RESIDUAL_TYPE CHROMA_CB;
    };
}

#endif //EYERLIB_RESIDUAL_TYPE_HPP
