#include "EyerSLICEBody.hpp"
#include "I_MB_TYPE.hpp"

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


        int MbaffFrameFlag = sps.mb_adaptive_frame_field_flag && !sliceHeader.sh.field_pic_flag;
        int CurrMbAddr = sliceHeader.sh.first_mb_in_slice * (1 + MbaffFrameFlag);
        int moreDataFlag = 1;
        int prevMbSkipped = 0;

        do {
            int mb_skip_flag;
            int mb_skip_run;

            if(sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_I && sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_SI) {
                if(!pps.entropy_coding_mode_flag){

                }
                else{

                }
            }
            if(moreDataFlag) {
                if(MbaffFrameFlag && (CurrMbAddr % 2 == 0 || (CurrMbAddr % 2 == 1 && prevMbSkipped))) {
                    int cabac = 0;
                    if (cabac) {
                        mb_field_decoding_flag = bs.bs_read_ae();
                    }
                    else {
                        mb_field_decoding_flag = bs.bs_read_u(1);
                    }
                }
                read_macroblock_layer(bs);
            }
            if(!pps.entropy_coding_mode_flag) {
                // moreDataFlag = more_rbsp_data( );
            }
            else {
                if(sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_I && sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_SI) {
                    prevMbSkipped = mb_skip_flag;
                }
                if(MbaffFrameFlag && CurrMbAddr % 2 == 0) {
                    moreDataFlag = 1;
                }
                else
                {
                    /*
                    int end_of_slice_flag;
                    end_of_slice_flag = bs.bs_read_ae();
                    moreDataFlag = !end_of_slice_flag;
                    */
                }
            }
            // CurrMbAddr = NextMbAddress( CurrMbAddr );
        }
        while(moreDataFlag);

        return 0;
    }

    int EyerSLICEBody::read_macroblock_layer(EyerBitStream & bs)
    {
        int mb_type = 0;
        if(!pps.entropy_coding_mode_flag){
            mb_type = bs.bs_read_ue();
        }
        else{
            mb_type = bs.bs_read_ae();
        }

        I_MB_TYPE mbType = mb_type;
        if(mbType == I_MB_TYPE::I_PCM){
            // I_PCM
        }
        else{
            
        }

        return 0;
    }
}