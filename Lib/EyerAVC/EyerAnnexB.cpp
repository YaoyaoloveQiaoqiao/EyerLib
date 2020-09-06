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

    int EyerAnnexB::GetAnnexBNALU()
    {
        int i;
        int info2 = 0, info3 = 0, pos = 0;
        int StartCodeFound = 0;
        int LeadingZero8BitsCount = 0;

        unsigned char * pBuf = buf;

        if (nextstartcodebytes != 0) {
            for (i = 0; i<nextstartcodebytes - 1; i++){
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
            nalu->startcodeprefix_len = 3;
        }
        else {
            LeadingZero8BitsCount = pos - 4;
            nalu->startcodeprefix_len = 4;
        }

        return 0;
    }

    int EyerAnnexB::getChunk()
    {
        int readbytes = fread(iobuffer, ioBufferSize, 1, bitStreamFile);
        if (0 == readbytes){
            is_eof = true;
            return 0;
        }

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
}