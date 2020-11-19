#include "AnnexB_to_avcC.hpp"

namespace Eyer
{
    AnnexB_to_avcC::AnnexB_to_avcC()
    {

    }

    AnnexB_to_avcC::~AnnexB_to_avcC()
    {

    }

    int AnnexB_to_avcC::SendAnnexB(uint8_t * buf, int bufLen)
    {
        EyerBuffer buffer;
        buffer.Append(buf, bufLen);
        return SendAnnexB(buffer);
    }

    int AnnexB_to_avcC::SendAnnexB(EyerBuffer & _annexBBuffer)
    {
        EyerBuffer annexBBuffer = _annexBBuffer;
        // 按照 0001 切割 annexB
        std::vector<int> posList;
        int pos = 0;
        while(pos < annexBBuffer.GetLen()){
            int startCodeLen = 0;
            bool isStartCode = CheckStartCode(startCodeLen, annexBBuffer.GetPtr() + pos, annexBBuffer.GetLen() - pos);
            if(isStartCode){
                posList.push_back(pos);
                pos += startCodeLen;
            }
            else{
                pos++;
            }
        }

        int totleBufferLen = annexBBuffer.GetLen();
        for(int i=0;i<posList.size();i++){
            int startPos = posList[i];
            int endPos = 0;
            if(i+1 >= posList.size()){
                endPos = totleBufferLen;
            }else{
                endPos = posList[i + 1];
            }

            int naluLen = endPos - startPos;
            // printf("Nalu Len: %d\n", naluLen);

            EyerBuffer * naluBuffer = new EyerBuffer();
            annexBBuffer.CutOff(*naluBuffer, naluLen);

            // printf("%d, %d, %d, %d, %d\n", naluBuffer->GetPtr()[0], naluBuffer->GetPtr()[1], naluBuffer->GetPtr()[2], naluBuffer->GetPtr()[3], naluBuffer->GetPtr()[4]);

            naluQueue.push(naluBuffer);
        }

        return 0;
    }

    int AnnexB_to_avcC::RecvAvcC(EyerBuffer & avccBuffer, bool & isExtradata)
    {
        if(naluQueue.size() <= 0){
            return -1;
        }

        EyerBuffer * naluBuffer = naluQueue.front();
        naluQueue.pop();

        if(naluBuffer == nullptr){
            return -1;
        }

        // 获取到 nalu type
        int finalRet = 0;

        int startCodeLen = 0;
        bool isStartCode = CheckStartCode(startCodeLen, naluBuffer->GetPtr(), naluBuffer->GetLen());
        if(isStartCode){
            // printf("startCodeLen: %d\n", startCodeLen);
            int nalutype = naluBuffer->GetPtr()[startCodeLen] & 0x1f;
            printf("nalu type: %d\n", nalutype);

            if(nalutype == 7){
                // 进入暂存期
                spsBuf = *naluBuffer;
                spsStartCodeLen = startCodeLen;
                finalRet = -1;
            }
            else if(nalutype == 8){
                // 进行包装
                ppsBuf = *naluBuffer;
                ppsStartCodeLen = startCodeLen;

                EyerBuffer extradata;

                int8_t version = 0x01;
                extradata.Append((uint8_t *)&version, sizeof(int8_t));

                int8_t avc_profile = spsBuf.GetPtr()[startCodeLen + 1];
                extradata.Append((uint8_t *)&avc_profile, sizeof(int8_t));

                int8_t avc_compatibility = spsBuf.GetPtr()[startCodeLen + 2];
                extradata.Append((uint8_t *)&avc_compatibility, sizeof(int8_t));

                int8_t avc_level = spsBuf.GetPtr()[startCodeLen + 3];
                extradata.Append((uint8_t *)&avc_level, sizeof(int8_t));

                uint8_t lengthSizeMinusOne = 0xFF;
                extradata.Append((uint8_t *)&lengthSizeMinusOne, sizeof(int8_t));

                int8_t mask = 7 << 5;
                int8_t numSPS = 1;
                numSPS = mask | numSPS;
                extradata.Append((uint8_t *)&numSPS, sizeof(int8_t));

                {
                    int16_t spsLen = spsBuf.GetLen() - spsStartCodeLen;
                    spsLen = htons(spsLen);
                    extradata.Append((uint8_t *)&spsLen, sizeof(int16_t));

                    extradata.Append(spsBuf.GetPtr() + spsStartCodeLen, spsBuf.GetLen() - spsStartCodeLen);
                }

                int8_t numPPS = 1;
                extradata.Append((uint8_t *)&numPPS, sizeof(int8_t));
                {
                    int16_t ppsLen = ppsBuf.GetLen() - ppsStartCodeLen;
                    ppsLen = htons(ppsLen);
                    extradata.Append((uint8_t *)&ppsLen, sizeof(int16_t));

                    extradata.Append(ppsBuf.GetPtr() + ppsStartCodeLen, ppsBuf.GetLen() - ppsStartCodeLen);
                }

                for(int i=0;i<extradata.GetLen();i++){
                    printf(" %x ", extradata.GetPtr()[i]);
                }
                printf("\n");

                avccBuffer = extradata;

                finalRet = 0;
                isExtradata = true;
            }
            else if(nalutype == 5 || nalutype == 1){
                EyerBuffer buffer;

                int32_t bufferLen = naluBuffer->GetLen() - startCodeLen;
                bufferLen = htonl(bufferLen);
                buffer.Append((uint8_t *)&bufferLen, sizeof(int32_t));
                buffer.Append(naluBuffer->GetPtr() + startCodeLen, naluBuffer->GetLen() - startCodeLen);

                avccBuffer = buffer;

                finalRet = 0;
                isExtradata = false;
            }
            else{
                finalRet = -1;
            }
        }

        if(naluBuffer != nullptr){
            delete naluBuffer;
            naluBuffer = nullptr;
        }

        return finalRet;
    }

    bool AnnexB_to_avcC::CheckStartCode(int & startCodeLen, uint8_t * bufPtr, int bufLen)
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