#include "EyerSliceData.hpp"
#include "EyerAVC_VLC.hpp"

namespace Eyer
{
    EyerSliceData::EyerSliceData()
    {

    }

    EyerSliceData::~EyerSliceData()
    {

    }

    int EyerSliceData::Parse(EyerSPS & _sps, EyerPPS & _pps, EyerSliceHeader & sliceHeader, EyerBitStream * bitStream, int * usedBits)
    {
        sps = _sps;
        pps = _pps;

        EyerLog("=======================\n");

        if(pps.entropy_coding_mode_flag){
            EyerLog("CABAC\n");
            while(*usedBits % 8 != 0){
                EyerAVC_VLC::read_u_1("", bitStream, usedBits);
            }
        }

        int curr_mb_addr = sliceHeader.first_mb_in_slice * (sliceHeader.mb_aff_frame_flag + 1);
        EyerLog("curr_mb_addr: %d\n", curr_mb_addr);
        int more_data_flag = 1;
        int pre_mb_skipped = 0;

        do
        {
            if(sliceHeader.slice_type != SliceType::I_SLICE && sliceHeader.slice_type != SliceType::SI_SLICE){
                if(!pps.entropy_coding_mode_flag){
                    int mb_skip_run = EyerAVC_VLC::read_ue_v("mb_skip_run", bitStream, usedBits);
                    EyerLog("mb_skip_run: %d\n", mb_skip_run);
                }
                else{
                    //TODO CABAC
                }
            }
            if(more_data_flag){
                if(sliceHeader.mb_aff_frame_flag && (curr_mb_addr % 2 == 0 || (curr_mb_addr % 2 == 1 && pre_mb_skipped))){
                    int mb_field_decoding_flag = EyerAVC_VLC::read_ue_v("mb_field_decoding_flag", bitStream, usedBits);
                    EyerLog("mb_field_decoding_flag: %d\n", mb_field_decoding_flag);
                }
                //TODO macroblock_layer();

                int mb_type = EyerAVC_VLC::read_ue_v("mb_type", bitStream, usedBits);
                EyerLog("mb_type: %d\n", mb_type);

                more_data_flag = 0;
            }

            if(!pps.entropy_coding_mode_flag){
                //TODO more_rbspdata();
            }
            else{
                //TODO CABAC
            }
        }
        while(more_data_flag);

        return 0;
    }
}