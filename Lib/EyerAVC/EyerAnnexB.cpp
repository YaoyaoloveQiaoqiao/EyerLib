#include "EyerAnnexB.hpp"
#include <stdlib.h>
#include <stdio.h>

namespace Eyer {
    EyerAnnexB::EyerAnnexB(const EyerString & _path)
    {
        path = _path;
        file = fopen(path.str, "rb");
    }

    EyerAnnexB::~EyerAnnexB()
    {
        if(file != nullptr){
            fclose(file);
            file = nullptr;
        }
    }

    int EyerAnnexB::ReadNALU(EyerNALU & nalu)
    {
        while(1){
            if(buffer.GetLen() <= 0){
                int readedLen = ReadFromFile();
                if(readedLen <= 0){
                    isEnd = true;
                }
            }

            unsigned char * buf = buffer.GetPtr();
            // Find Start Code
            bool isStartCode = CheckStartCode(buf, buffer.GetLen());
            if(!isStartCode){
                break;
            }

            // Find End Code
            int endPos = -1;
            for(int i=2;i<buffer.GetLen();i++){
                bool isStartCode = CheckStartCode(buf + i, buffer.GetLen() - i);
                if(isStartCode){
                    endPos = i;
                    break;
                }
            }

            if(endPos > 0){
                EyerBuffer naluBuffer;
                buffer.CutOff(naluBuffer, endPos);
                nalu.SetData(naluBuffer);
                return 0;
            }
            else{
                if(isEnd == true){
                    EyerBuffer naluBuffer;
                    buffer.CutOff(naluBuffer, buffer.GetLen());
                    nalu.SetData(naluBuffer);
                    return 0;
                }
                int readedLen = ReadFromFile();
                if(readedLen <= 0){
                    isEnd = true;
                }
            }
        }

        return -1;
    }

    int EyerAnnexB::ReadFromFile()
    {
        int tempBufferLen = 1024;
        uint8_t * buf = (uint8_t *)malloc(tempBufferLen);

        int readedLen = fread(buf, 1, tempBufferLen, file);

        buffer.Append(buf, readedLen);

        free(buf);

        return readedLen;
    }

    bool EyerAnnexB::CheckStartCode(uint8_t * bufPtr, int bufLen)
    {
        if(bufLen <= 2){
            return false;
        }
        if(bufLen >= 4){
            if(bufPtr[0] == 0) {
                if (bufPtr[1] == 0) {
                    if (bufPtr[2] == 0) {
                        if (bufPtr[3] == 1) {
                            return true;
                        }
                    }
                    if(bufPtr[2] == 1){
                        return true;
                    }
                }
            }
        }
        if(bufLen <= 3){
            if(bufPtr[0] == 0) {
                if (bufPtr[1] == 0) {
                    if(bufPtr[2] == 1){
                        return true;
                    }
                }
            }
        }
        return false;
    }
}