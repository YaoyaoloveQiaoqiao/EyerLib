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

    int EyerAnnexB::ReadNALU(EyerNALUData & nalu)
    {
        while(1){
            if(buffer.GetLen() <= 0){
                int readedLen = ReadFromFile();
                if(readedLen <= 0){
                    isEnd = true;
                }
            }

            unsigned char * buf = buffer.GetPtr();

            int startCodeLen = 0;
            // Find Start Code
            bool isStartCode = CheckStartCode(startCodeLen, buf, buffer.GetLen());
            if(!isStartCode){
                break;
            }

            // Find End Code
            int endPos = -1;
            for(int i=2;i<buffer.GetLen();i++){
                int startCodeLen = 0;
                bool isStartCode = CheckStartCode(startCodeLen, buf + i, buffer.GetLen() - i);
                if(isStartCode){
                    endPos = i;
                    break;
                }
            }

            if(endPos > 0){
                EyerBuffer naluBuffer;
                buffer.CutOff(naluBuffer, endPos);
                nalu.SetData(naluBuffer, startCodeLen);
                return 0;
            }
            else{
                if(isEnd == true){
                    EyerBuffer naluBuffer;
                    buffer.CutOff(naluBuffer, buffer.GetLen());
                    nalu.SetData(naluBuffer, startCodeLen);
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

    bool EyerAnnexB::CheckStartCode(int & startCodeLen, uint8_t * bufPtr, int bufLen)
    {
        if(bufLen <= 2){
            startCodeLen = 0;
            return false;
        }
        if(bufLen >= 4){
            if(bufPtr[0] == 0) {
                if (bufPtr[1] == 0) {
                    if (bufPtr[2] == 0) {
                        if (bufPtr[3] == 1) {
                            startCodeLen = 4;
                            return true;
                        }
                    }
                    if(bufPtr[2] == 1){
                        startCodeLen = 3;
                        return true;
                    }
                }
            }
        }
        if(bufLen <= 3){
            if(bufPtr[0] == 0) {
                if (bufPtr[1] == 0) {
                    if(bufPtr[2] == 1){
                        startCodeLen = 4;
                        return true;
                    }
                }
            }
        }

        startCodeLen = 0;
        return false;
    }
}