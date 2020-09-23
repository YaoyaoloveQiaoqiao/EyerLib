#include "EyerSyntaxElement.hpp"

namespace Eyer
{
    int EyerSyntaxElement::SetMappingType(SyntaxElementMappingType type)
    {
        mappingType = type;
        return 0;
    }
    void EyerSyntaxElement::mapping(int len, int info, int * value1, int * dummy)
    {
        if(mappingType = SyntaxElementMappingType::linfo_se){
            linfo_se(len, info, value1, dummy);
        }
        if(mappingType = SyntaxElementMappingType::linfo_ue){
            linfo_ue(len, info, value1, dummy);
        }
    }

    void EyerSyntaxElement::linfo_ue(int len, int info, int *value1, int *dummy)
    {
        *value1 = (int) (((unsigned int) 1 << (len >> 1)) + (unsigned int) (info) - 1);
    }

    void EyerSyntaxElement::linfo_se(int len, int info, int * value1, int * dummy)
    {
        unsigned int n = ((unsigned int) 1 << (len >> 1)) + (unsigned int) info - 1;
        *value1 = (n + 1) >> 1;
        if((n & 0x01) == 0) {
            *value1 = -*value1;
        }
    }
}