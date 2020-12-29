#include "RESIDUAL_TYPE.hpp"

namespace Eyer {

    RESIDUAL_TYPE RESIDUAL_TYPE::LUMA           (1, "LUMA");
    RESIDUAL_TYPE RESIDUAL_TYPE::CHROMA_CR      (2, "CHROMA_CR");
    RESIDUAL_TYPE RESIDUAL_TYPE::CHROMA_CB      (3, "CHROMA_CB");

    RESIDUAL_TYPE::RESIDUAL_TYPE(int _val, const EyerString &_name) : EyerEnum(_val, _name)
    {

    }

    RESIDUAL_TYPE::RESIDUAL_TYPE(const RESIDUAL_TYPE &residualType)
    {
        *this = residualType;
    }

    RESIDUAL_TYPE::RESIDUAL_TYPE(const int &residualType)
    {
        *this = residualType;
    }

    RESIDUAL_TYPE::~RESIDUAL_TYPE()
    {

    }

    RESIDUAL_TYPE &RESIDUAL_TYPE::operator=(const RESIDUAL_TYPE &residualType)
    {
        EyerEnum::operator=(residualType);
        return *this;
    }

    bool RESIDUAL_TYPE::operator == (const RESIDUAL_TYPE & residualType)
    {
        return EyerEnum::operator==(residualType);
    }

    bool RESIDUAL_TYPE::operator != (const RESIDUAL_TYPE & residualType)
    {
        return !(*this == residualType);
    }
}