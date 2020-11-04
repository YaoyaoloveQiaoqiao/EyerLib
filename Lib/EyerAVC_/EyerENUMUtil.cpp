#include "EyerAVCCommon.hpp"

namespace Eyer
{
    EyerString EyerENUMUtil::GetSliceTypeStr(const SliceType & sliceType)
    {
        if(sliceType == SliceType::P_SLICE){
            return "P_SLICE";
        }
        else if(sliceType == SliceType::B_SLICE){
            return "B_SLICE";
        }
        else if(sliceType == SliceType::I_SLICE){
            return "I_SLICE";
        }
        else if(sliceType == SliceType::SP_SLICE){
            return "SP_SLICE";
        }
        else if(sliceType == SliceType::SI_SLICE){
            return "SI_SLICE";
        }
        else if(sliceType == SliceType::NUM_SLICE_TYPES){
            return "NUM_SLICE_TYPES";
        }

        return nullptr;
    }
}