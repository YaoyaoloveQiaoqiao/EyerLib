#include "EyerSLICE.hpp"

namespace Eyer
{
    EyerSLICE::EyerSLICE(EyerSPS & _sps, EyerPPS & _pps)
    {
        sps = _sps;
        pps = _pps;
    }

    EyerSLICE::~EyerSLICE()
    {

    }

    SLICEType EyerSLICE::GetSLICEType()
    {
        return sliceHeader.GetSLICEType();
    }

    int EyerSLICE::Parse()
    {
        if(!sps.isValid()){
            return -1;
        }
        if(!pps.isValid()){
            return -1;
        }

        EyerNALU::Parse();

        EyerBitStream bs(naluData.GetRBSPBuffer());
        int ret = sliceHeader.Parse(bs, fieldList, sps, pps, naluData);
        if(ret){
            return -1;
        }

        ret = sliceBody.Parse(bs, fieldList, sps, pps, sliceHeader);
        if(ret){
            return -1;
        }

        valid = true;

        return 0;
    }
}