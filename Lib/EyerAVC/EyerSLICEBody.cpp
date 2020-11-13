#include "EyerSLICEBody.hpp"

namespace Eyer
{
    EyerSLICEBody::EyerSLICEBody()
    {

    }

    EyerSLICEBody::~EyerSLICEBody()
    {

    }

    int EyerSLICEBody::Parse(EyerBitStream & bs, EyerFieldList & fieldList, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader)
    {
        sps = _sps;
        pps = _pps;
        sliceHeader = _sliceHeader;

        if(!sps.isValid()){
            return -1;
        }
        if(!pps.isValid()){
            return -1;
        }

        if(pps.entropy_coding_mode_flag){
            // 进行对齐操作
            while(!bs.bs_byte_aligned()) {
                /* cabac_alignment_one_bit */
                bs.bs_read_u1();
            }
        }

        /*
        int MbaffFrameFlag = sps.mb_adaptive_frame_field_flag && !sliceHeader.sh.field_pic_flag;
        int CurrMbAddr = sliceHeader.sh.first_mb_in_slice * (1 + MbaffFrameFlag);
        int moreDataFlag = 1;
        int prevMbSkipped = 0;

        do {
            int mb_skip_flag;
            int mb_skip_run;

            if(sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_I && sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_SI) {
                if(!pps.entropy_coding_mode_flag) {
                    mb_skip_run = bs.bs_read_ue();
                    prevMbSkipped = mb_skip_run > 0;
                    for(int i = 0; i < mb_skip_run; i++){
                        // CurrMbAddr = NextMbAddress(CurrMbAddr);
                    }
                    // moreDataFlag = more_rbsp_data();
                }
                else {
                    mb_skip_flag = bs.bs_read_ae();
                    moreDataFlag = !mb_skip_flag;
                }
            }


        }
        while(moreDataFlag);
        */
        return 0;
    }
}