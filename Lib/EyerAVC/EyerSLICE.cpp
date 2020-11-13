#include "EyerSLICE.hpp"

namespace Eyer
{
    EyerSLICE::EyerSLICE(EyerSPS & _sps, EyerPPS & _pps) : sliceHeader(_sps, _pps, naluData)
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
        int ret = sliceHeader.Parse(bs, fieldList);
        if(ret){
            return -1;
        }

        ParseBody(bs);

        valid = true;

        return 0;
    }

    int EyerSLICE::ParseBody(EyerBitStream & bs)
    {
        if(pps.entropy_coding_mode_flag){
            // 进行对齐操作
        }


        return 0;
    }
}