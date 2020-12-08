#include "EyerSLICEBody.hpp"
#include "I_MB_TYPE.hpp"
#include "MB_TYPE.hpp"
#include "EyerMacroblock.hpp"

namespace Eyer
{
    EyerSLICEBody::EyerSLICEBody()
    {

    }

    EyerSLICEBody::~EyerSLICEBody()
    {
        for(int i=0;i<macroblockList.size();i++){
            delete macroblockList[i];
        }
        macroblockList.clear();
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

        do{
            if(sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_I && sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_SI) {
                if (!pps.entropy_coding_mode_flag) {

                }
                else{

                }
            }

            if(moreDataFlag){
                if(MbaffFrameFlag && (CurrMbAddr % 2 == 0 || (CurrMbAddr % 2 == 1 && prevMbSkipped))){
                    uint32_t mb_field_decoding_flag = bs.bs_read_u1();
                }
                EyerMacroblock * block = new EyerMacroblock();
                block->Parse(bs, sps, pps, sliceHeader);
                macroblockList.push_back(block);
                // macroblock_layer(sliceHeader.GetSLICEType() ,bs);
            }
            if(!pps.entropy_coding_mode_flag){
                moreDataFlag = bs.more_data();
            }
            else {
                if(sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_I && sliceHeader.GetSLICEType() != SLICEType::SLICE_TYPE_SI){
                    //TODO prevMbSkipped = mb_skip_flag;
                }
                if(MbaffFrameFlag && CurrMbAddr % 2 == 0){
                    moreDataFlag = 1;
                }
                else {
                    uint32_t end_of_slice_flag = bs.bs_read_ae();
                    moreDataFlag = !end_of_slice_flag;
                }
            }

            //TODO CurrMbAddr = NextMbAddress(CurrMbAddr);

            //TODO DEBUG
            moreDataFlag = 0;
        }
        while (moreDataFlag);

        return 0;
    }
}