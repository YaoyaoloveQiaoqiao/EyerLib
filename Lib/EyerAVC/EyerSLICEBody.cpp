#include "EyerSLICEBody.hpp"
#include "I_MB_TYPE.hpp"
#include "MB_TYPE.hpp"
#include "EyerMacroblock.hpp"

namespace Eyer
{
    EyerSLICEBody::EyerSLICEBody() : mbTable(0, 0)
    {

    }

    EyerSLICEBody::~EyerSLICEBody()
    {
        /*
        for(int i=0;i<macroblockList.size();i++){
            delete macroblockList[i];
        }
        macroblockList.clear();
         */
    }

    int EyerSLICEBody::Parse(EyerBitStream & bs, EyerSyntax & syntax, EyerSPS & _sps, EyerPPS & _pps, EyerSLICEHeader & _sliceHeader)
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

        // 初始化 宏块 Table
        // 将宏块列表更新
        int w_mbs_nums = sps.pic_width_in_mbs_minus1 + 1;
        int h_mbs_nums = sps.pic_height_in_map_units_minus1 + 1;
        mbTable.Resize(w_mbs_nums, h_mbs_nums);
        for(int y=0; y<h_mbs_nums; y++){
            for(int x=0; x<w_mbs_nums; x++){
                EyerMacroblock * n = nullptr;
                mbTable.Set(x, y, n);
            }
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

            EyerERROR("sps.pic_width_in_mbs_minus1 + 1 : %d\n", sps.pic_width_in_mbs_minus1 + 1);
            EyerERROR("sps.pic_height_in_map_units_minus1 + 1 : %d\n", sps.pic_height_in_map_units_minus1 + 1);

            if(moreDataFlag){
                if(MbaffFrameFlag && (CurrMbAddr % 2 == 0 || (CurrMbAddr % 2 == 1 && prevMbSkipped))){
                    uint32_t mb_field_decoding_flag = bs.bs_read_u1();
                }

                int x = CurrMbAddr % (sps.pic_width_in_mbs_minus1 + 1);
                int y = CurrMbAddr / (sps.pic_width_in_mbs_minus1 + 1);

                int mbAddrA_X = x - 1;
                int mbAddrA_Y = y;
                EyerMacroblock * mbAddrA = nullptr;
                mbTable.Get(mbAddrA, mbAddrA_X, mbAddrA_Y);

                int mbAddrB_X = x;
                int mbAddrB_Y = y - 1;
                EyerMacroblock * mbAddrB = nullptr;
                mbTable.Get(mbAddrB, mbAddrB_X, mbAddrB_Y);

                int mbAddrC_X = x + 1;
                int mbAddrC_Y = y - 1;
                EyerMacroblock * mbAddrC = nullptr;
                mbTable.Get(mbAddrC, mbAddrC_X, mbAddrC_Y);

                int mbAddrD_X = x - 1;
                int mbAddrD_Y = y - 1;
                EyerMacroblock * mbAddrD = nullptr;
                mbTable.Get(mbAddrD, mbAddrD_X, mbAddrD_Y);

                EyerMacroblock * block = new EyerMacroblock(CurrMbAddr, mbAddrA, mbAddrB, mbAddrC, mbAddrD);
                block->Parse(bs, sps, pps, sliceHeader);
                mbTable.Set(x, y, block);
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
            CurrMbAddr++;

            //TODO DEBUG

            if(CurrMbAddr >= 30){
                moreDataFlag = 0;
            }

            EyerERROR("moreDataFlag: %d\n", moreDataFlag);
            EyerERROR("CurrMbAddr: %d\n", CurrMbAddr);
        }
        while (moreDataFlag);

        return 0;
    }
}