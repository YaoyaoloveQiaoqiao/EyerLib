#include "EyerAnnexB.hpp"
#include <stdio.h>
#include <stdlib.h>

namespace Eyer{
    EyerAnnexB::EyerAnnexB()
    {
        int nalu_max_size = 8 * 1024 * 1024;
        buf = (unsigned char *)malloc(nalu_max_size);
        if(buf == nullptr){
            EyerLog("malloc_annex_b: Buf\n");
        }

        bitStreamFile = nullptr;
        iobuffer = nullptr;
        iobufferread = nullptr;
        bytesinbuffer = 0;
        is_eof = false;
        isFirstByteStreamNALU = 1;
        nextstartcodebytes = 0;
    }

    EyerAnnexB::~EyerAnnexB()
    {
        Close();

        if(buf != nullptr){
            free(buf);
            buf = nullptr;
        }
    }

    int EyerAnnexB::Open(EyerString & path)
    {
        if (nullptr != iobuffer) {
            EyerLog ("open_annex_b: tried to open Annex B file twice\n");
            return -1;
        }

        bitStreamFile = fopen(path.str, "rb");
        if(nullptr == bitStreamFile){
            EyerLog ("Cannot open Annex B ByteStream file '%s'\n", path.str);
            return -1;
        }

        int IOBUFFERSIZE = 512 * 1024;

        ioBufferSize = IOBUFFERSIZE * sizeof (unsigned char);
        iobuffer = (unsigned char *)malloc (ioBufferSize);
        if (nullptr == iobuffer) {
            EyerLog ("open_annex_b: cannot allocate IO buffer\n");
        }

        is_eof = false;
        getChunk();
        return 0;
    }

    int EyerAnnexB::Close()
    {
        if (bitStreamFile != nullptr) {
            fclose(bitStreamFile);
            bitStreamFile = nullptr;
        }
        if(iobuffer != nullptr){
            free(iobuffer);
            iobuffer = nullptr;
        }
        return 0;
    }

    int EyerAnnexB::Reset()
    {
        is_eof = false;
        bytesinbuffer = 0;
        iobufferread = iobuffer;
        return 0;
    }

    int EyerAnnexB::GetAnnexBNALU(EyerNALU & nalu)
    {
        int i;
        int info2 = 0, info3 = 0, pos = 0;
        int StartCodeFound = 0;
        int LeadingZero8BitsCount = 0;

        unsigned char * pBuf = buf;

        if (nextstartcodebytes != 0) {
            for (i = 0; i<nextstartcodebytes - 1; i++) {
                (*pBuf++) = 0;
                pos++;
            }
            (*pBuf++) = 1;
            pos++;
        }
        else {
            while(!is_eof) {
                pos++;
                if ((*(pBuf++) = getfbyte())!= 0){
                    break;
                }
            }
        }



        if(is_eof == true) {
            if(pos==0) {
                return 0;
            }
            else {
                EyerLog( "get_annex_b_NALU can't read start code\n");
                return -1;
            }
        }


        if(*(pBuf - 1) != 1 || pos < 3) {
            EyerLog ("get_annex_b_NALU: no Start Code at the beginning of the NALU, return -1\n");
            return -1;
        }

        if (pos == 3) {
            nalu.startcodeprefix_len = 3;
        }
        else {
            LeadingZero8BitsCount = pos - 4;
            nalu.startcodeprefix_len = 4;
        }

        // EyerLog("startcodeprefix_len: %d\n", nalu.startcodeprefix_len);

        if(!isFirstByteStreamNALU && LeadingZero8BitsCount > 0) {
            EyerLog ("get_annex_b_NALU: The leading_zero_8bits syntax can only be present in the first byte stream NAL unit, return -1\n");
            return -1;
        }

        LeadingZero8BitsCount = pos;
        isFirstByteStreamNALU = 0;


        while (!StartCodeFound) {
            if (is_eof == true) {
                pBuf -= 2;
                while(*(pBuf--)==0) {
                    pos--;
                }

                nalu.len = (pos - 1) - LeadingZero8BitsCount;
                memcpy (nalu.buf, buf + LeadingZero8BitsCount, nalu.len);
                nalu.forbidden_bit     = (*(nalu.buf) >> 7) & 1;
                nalu.nal_reference_idc = (NalRefIdc) ((*(nalu.buf) >> 5) & 3);
                nalu.nal_unit_type     = (NaluType) ((*(nalu.buf)) & 0x1f);
                nextstartcodebytes = 0;

                // printf ("get_annex_b_NALU, eof case: pos %d nalu->len %d, nalu->reference_idc %d, nal_unit_type %d \n", pos, nalu->len, nalu->nal_reference_idc, nalu->nal_unit_type);
                return (pos - 1);
            }

            pos++;
            *(pBuf ++) = getfbyte();
            info3 = FindStartCode(pBuf - 4, 3);
            if(info3 != 1) {
                info2 = FindStartCode(pBuf - 3, 2);
                StartCodeFound = info2 & 0x01;
            }
            else {
                StartCodeFound = 1;
            }
        }


        // Here, we have found another start code (and read length of startcode bytes more than we should
        // have.  Hence, go back in the file
        if(info3 == 1)  //if the detected start code is 00 00 01, trailing_zero_8bits is sure not to be present
        {
            pBuf -= 5;
            while(*(pBuf--) == 0) {
                pos--;
            }

            nextstartcodebytes = 4;
        }
        else if (info2 == 1) {
            nextstartcodebytes = 3;
        }
        else{
            printf(" Panic: Error in next start code search \n");
            return -1;
        }

        pos -= nextstartcodebytes;



        // Here the leading zeros(if any), Start code, the complete NALU, trailing zeros(if any)
        // and the next start code is in the Buf.
        // The size of Buf is pos - rewind, pos are the number of bytes excluding the next
        // start code, and (pos) - LeadingZero8BitsCount
        // is the size of the NALU.

        nalu.len = pos - LeadingZero8BitsCount;
        memcpy (nalu.buf, buf + LeadingZero8BitsCount, nalu.len);
        nalu.forbidden_bit     = (*(nalu.buf) >> 7) & 1;
        nalu.nal_reference_idc = (NalRefIdc) ((*(nalu.buf) >> 5) & 3);
        nalu.nal_unit_type     = (NaluType) ((*(nalu.buf)) & 0x1f);
        nalu.lost_packets = 0;


        //printf ("get_annex_b_NALU, regular case: pos %d nalu->len %d, nalu->reference_idc %d, nal_unit_type %d \n", pos, nalu->len, nalu->nal_reference_idc, nalu->nal_unit_type);

        return (pos);
    }

    int EyerAnnexB::getChunk()
    {
        int readbytes = fread(iobuffer, 1, ioBufferSize, bitStreamFile);
        // EyerLog("readbytes: %d\n", readbytes);
        if (0 == readbytes){
            is_eof = true;
            return 0;
        }

        /*
        for(int i=0;i<100;i++){
            printf(" %d ", iobuffer[i]);
        }
        printf("\n\n");
        */

        bytesinbuffer = readbytes;
        iobufferread = iobuffer;

        return readbytes;
    }

    unsigned char EyerAnnexB::getfbyte(){
        if (0 == bytesinbuffer) {
            if (0 == getChunk()) {
                return 0;
            }
        }
        bytesinbuffer--;
        return (*iobufferread++);
    }

    int EyerAnnexB::FindStartCode (unsigned char * Buf, int zeros_in_startcode)
    {
        int i;

        for (i = 0; i < zeros_in_startcode; i++) {
            if(*(Buf++) != 0) {
                return 0;
            }
        }

        if(*Buf != 1){
            return 0;
        }

        return 1;
    }
}