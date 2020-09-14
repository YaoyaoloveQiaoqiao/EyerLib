#include "EyerAVCCommon.hpp"
#include "EyerCore/EyerCore.hpp"

namespace Eyer{
    int EyerAVCCommon::EBSPtoRBSP(unsigned char * streamBuffer, int end_bytepos, int begin_bytepos)
    {
        int i, j, count;
        count = 0;

        if(end_bytepos < begin_bytepos){
            return end_bytepos;
        }

        j = begin_bytepos;

        for(i = begin_bytepos; i < end_bytepos; ++i){
            //starting from begin_bytepos to avoid header information
            //in NAL unit, 0x000000, 0x000001 or 0x000002 shall not occur at any byte-aligned position
            if(count == ZEROBYTES_SHORTSTARTCODE && streamBuffer[i] < 0x03){
                return -1;
            }
            if(count == ZEROBYTES_SHORTSTARTCODE && streamBuffer[i] == 0x03) {
                //check the 4th byte after 0x000003, except when cabac_zero_word is used, in which case the last three bytes of this NAL unit must be 0x000003
                if((i < end_bytepos-1) && (streamBuffer[i+1] > 0x03)){
                    return -1;
                }

                //if cabac_zero_word is used, the final byte of this NAL unit(0x03) is discarded, and the last two bytes of RBSP must be 0x0000
                if(i == end_bytepos-1){
                    return j;
                }

                ++i;
                count = 0;
            }
            streamBuffer[j] = streamBuffer[i];
            if(streamBuffer[i] == 0x00) {
                ++count;
            }
            else{
                count = 0;
            }

            ++j;
        }

        return j;
    }


    int EyerAVCCommon::RBSPtoSODB(unsigned char * streamBuffer, int last_byte_pos)
    {
        int ctr_bit, bitoffset;

        bitoffset = 0;
        //find trailing 1
        ctr_bit = (streamBuffer[last_byte_pos-1] & (0x01<<bitoffset));   // set up control bit

        while (ctr_bit==0)
        {                 // find trailing 1 bit
            ++bitoffset;
            if(bitoffset == 8)
            {
                if(last_byte_pos == 0){
                    EyerLog(" Panic: All zero data sequence in RBSP \n");
                }

                --last_byte_pos;
                bitoffset = 0;
            }
            ctr_bit= streamBuffer[last_byte_pos - 1] & (0x01<<(bitoffset));
        }

        return(last_byte_pos);

        return 0;
    }
}