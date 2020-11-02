#include "EyerNALUData.hpp"

#include <stdio.h>

namespace Eyer
{
    EyerNALUData::EyerNALUData()
    {

    }

    EyerNALUData::~EyerNALUData()
    {

    }

    NALUType & EyerNALUData::GetNALUType()
    {
        return nal_unit_type;
    }

    EyerBuffer & EyerNALUData::GetNaluBuffer()
    {
        return naluBuffer;
    }

    EyerBuffer & EyerNALUData::GetRBSPBuffer()
    {
        return rbspBuffer;
    }

    EyerBuffer & EyerNALUData::GetSODBBuffer()
    {
        return sodbBuffer;
    }

    int EyerNALUData::SetData(EyerBuffer & _naluBuffer, int _startCodeLen)
    {
        naluBuffer = _naluBuffer;
        startCodeLen = _startCodeLen;

        unsigned char * bufPtr = naluBuffer.GetPtr();

        // Get Nalu Head
        forbidden_bit   = (*(bufPtr + startCodeLen) >> 7) & 1;
        nal_ref_idc     = (*(bufPtr + startCodeLen) >> 5) & 3;
        nal_unit_type   = (*(bufPtr + startCodeLen) >> 0) & 0x1f;

        // EBSPtoRBSP
        rbspBuffer = naluBuffer;
        EyerBuffer b;
        rbspBuffer.CutOff(b, startCodeLen + 1);
        int rbspLen = EBSPtoRBSP(rbspBuffer.GetPtr(), rbspBuffer.GetLen(),  0);
        rbspBuffer.SetLen(rbspLen);

        // RBSPtoSODB
        sodbBuffer = rbspBuffer;
        int sodbLen = RBSPtoSODB(sodbBuffer.GetPtr(), sodbBuffer.GetLen() - 1);
        sodbBuffer.SetLen(sodbLen);

        // Print Info
        printf("================================\n");
        printf("nale len: %d, %d %d %d %d %d\n", naluBuffer.GetLen(), bufPtr[0], bufPtr[1], bufPtr[2], bufPtr[3], bufPtr[4]);
        printf("nal_ref_idc: %s\n", nal_ref_idc.GetName().str);
        printf("nal_unit_type: %s\n", nal_unit_type.GetName().str);
        printf("rbsp len: %d\n", rbspLen);
        printf("sodb len: %d\n", sodbLen);

        return 0;
    }


    int EyerNALUData::EBSPtoRBSP(unsigned char * streamBuffer, int end_bytepos, int begin_bytepos)
    {
        const int ZEROBYTES_SHORTSTARTCODE = 2;

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

    int EyerNALUData::RBSPtoSODB(unsigned char * streamBuffer, int last_byte_pos)
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

        return last_byte_pos;
    }
}