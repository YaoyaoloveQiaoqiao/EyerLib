#include "EyerMP4Box.hpp"
#include "EyerMP4Constant.hpp"
#include "EyerMP4Box_ftyp.hpp"
#include "EyerMP4Box_moov.hpp"
#include "EyerMP4Box_mvhd.hpp"
#include "EyerMP4Box_trak.hpp"
#include "EyerMP4Box_tkhd.hpp"
#include "EyerMP4Box_edts.hpp"
#include "EyerMP4Box_mdia.hpp"
#include "EyerMP4Box_mdhd.hpp"
#include "EyerMP4Box_hdlr.hpp"
#include "EyerMP4Box_minf.hpp"
#include "EyerMP4Box_stbl.hpp"
#include "EyerMP4Box_mvex.hpp"
#include "EyerMP4Box_trex.hpp"
#include "EyerMP4Box_mehd.hpp"
#include <string.h>

namespace Eyer
{
    EyerMP4Box::EyerMP4Box()
    {

    }

    EyerMP4Box::EyerMP4Box(const EyerBuffer & _buffer)
    {
        buffer = _buffer;
        totalBuffer = _buffer;
    }

    EyerMP4Box::~EyerMP4Box()
    {

    }

    EyerMP4Box::EyerMP4Box(const EyerMP4Box & _box) : EyerMP4Box()
    {
        *this = _box;
    }

    EyerMP4Box & EyerMP4Box::operator = (const EyerMP4Box & _box)
    {
        buffer = _box.buffer;
        totalBuffer = _box.totalBuffer;

        printf("EyerMP4Box & EyerMP4Box::operator = (const EyerMP4Box & _box)\n");

        return *this;
    }

    int EyerMP4Box::Get(EyerMP4Box * * box)
    {
        return Get(box, buffer);
    }

    int EyerMP4Box::Get(EyerMP4Box * * box, EyerBuffer & buffer)
    {
        if(buffer.GetBuffer() < 4){
            return -1;
        }

        EyerBuffer boxSizeBuffer;
        buffer.CutOff(boxSizeBuffer, 4);

        int boxSizeBufferLen = boxSizeBuffer.GetBuffer();
        unsigned char * boxSizeBufferB = (unsigned char *)malloc(boxSizeBufferLen);
        boxSizeBuffer.GetBuffer(boxSizeBufferB);

        int boxSize = boxSizeBufferB[0] << 24 | boxSizeBufferB[1] << 16 | boxSizeBufferB[2] << 8 | boxSizeBufferB[3];

        free(boxSizeBufferB);







        EyerBuffer boxTypeBuffer;
        buffer.CutOff(boxTypeBuffer, 4);

        unsigned char boxType[MAX_BOX_TYPE_LEN + 1];
        boxTypeBuffer.GetBuffer(boxType);

        boxType[MAX_BOX_TYPE_LEN] = '\0';







        int boxDataLen = boxSize - MAX_BOX_SIZE_LEN - MAX_BOX_TYPE_LEN;
        EyerBuffer boxDataBuffer;
        buffer.CutOff(boxDataBuffer, boxDataLen);





        printf("boxType: %s\n", boxType);
        if (0 == strcmp((char *)boxType, BOX_TYPE_FTYPE)) {
            *box = new EyerMP4Box_ftyp(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_MOOV)){
            *box = new EyerMP4Box_moov(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_MVHD)){
            *box = new EyerMP4Box_mvhd(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_TRAK)){
            *box = new EyerMP4Box_trak(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_TKHD)){
            *box = new EyerMP4Box_tkhd(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_EDTS)){
            *box = new EyerMP4Box_edts(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_MDIA)){
            *box = new EyerMP4Box_mdia(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_MDHD)){
            *box = new EyerMP4Box_mdhd(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_HDLR)){
            *box = new EyerMP4Box_hdlr(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_MINF)){
            *box = new EyerMP4Box_minf(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_STBL)){
            *box = new EyerMP4Box_stbl(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_MVEX)){
            *box = new EyerMP4Box_mvex(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_TREX)){
            *box = new EyerMP4Box_trex(boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_MEHD)){
            *box = new EyerMP4Box_mehd(boxDataBuffer);
        }

        return 0;
    }


    BoxType EyerMP4Box::GetType()
    {
        return BoxType::UNKNOW;
    }

    bool EyerMP4Box::HasSub()
    {
        return true;
    }

    int EyerMP4Box::PrintInfo()
    {
        return 0;
    }

    int EyerMP4Box::GetTotalBufferData(unsigned char * data)
    {
        return totalBuffer.GetBuffer(data);
    }

    EyerBuffer & EyerMP4Box::GetTotalBuffer()
    {
        return totalBuffer;
    }

    EyerBuffer EyerMP4Box::GetTotalBufferWithHead()
    {
        int totalBufferLen = totalBuffer.GetLen();
        int len = 8 + totalBufferLen;
        char head[8];

        head[0] = *((char *)&len + 3);
        head[1] = *((char *)&len + 2);
        head[2] = *((char *)&len + 1);
        head[3] = *((char *)&len + 0);

        BoxType type = GetType();

        head[4] = type.GetA();
        head[5] = type.GetB();
        head[6] = type.GetC();
        head[7] = type.GetD();

        EyerBuffer buffer;

        buffer.Append((unsigned char *)head, 8);
        buffer.Append(totalBuffer);

        return buffer;
    }

    int EyerMP4Box::AddSubBox(EyerMP4Box & subBox)
    {
        if(!HasSub()) {
            return -1;
        }

        EyerBuffer subBuffer = subBox.GetTotalBuffer();

        int len = 8 + subBuffer.GetLen();
        char head[8];

        head[0] = *((char *)&len + 3);
        head[1] = *((char *)&len + 2);
        head[2] = *((char *)&len + 1);
        head[3] = *((char *)&len + 0);

        BoxType type = subBox.GetType();

        head[4] = type.GetA();
        head[5] = type.GetB();
        head[6] = type.GetC();
        head[7] = type.GetD();

        totalBuffer.Append((unsigned char *)head, 8);
        totalBuffer.Append(subBuffer);

        buffer = totalBuffer;

        return 0;
    }

    int EyerMP4Box::GetMOOV(EyerMP4Box_moov & moov)
    {
        if(!HasSub()){
            return -1;
        }

        EyerBuffer buf = buffer;

        int finalRet = -1;
        while (1){
            EyerMP4Box * box = nullptr;
            int ret = Get(&box, buf);
            if(ret){
                break;
            }
            if(box == nullptr){
                continue;
            }

            if(box->GetType() == BoxType::MOOV){
                moov = *((EyerMP4Box_moov *)box);
                finalRet = 0;
            }

            if(box != nullptr){
                delete box;
                box = nullptr;
            }
        }
        return finalRet;
    }

    int EyerMP4Box::GetTRAK(EyerMP4Box_trak & trak)
    {
        if(!HasSub()){
            return -1;
        }

        EyerBuffer buf = buffer;

        int finalRet = -1;
        while (1){
            EyerMP4Box * box = nullptr;
            int ret = Get(&box, buf);
            if(ret){
                break;
            }
            if(box == nullptr){
                continue;
            }

            if(box->GetType() == BoxType::TRAK){
                trak = *((EyerMP4Box_trak *)box);
                finalRet = 0;
            }

            if(box != nullptr){
                delete box;
                box = nullptr;
            }
        }
        return finalRet;
    }

    int EyerMP4Box::GetFTYP(EyerMP4Box_ftyp & ftyp)
    {
        if(!HasSub()){
            return -1;
        }

        EyerBuffer buf = buffer;

        int finalRet = -1;
        while (1){
            EyerMP4Box * box = nullptr;
            int ret = Get(&box, buf);
            if(ret){
                break;
            }
            if(box == nullptr){
                continue;
            }

            if(box->GetType() == BoxType::FTYP){
                ftyp = *((EyerMP4Box_ftyp *)box);
                finalRet = 0;
            }

            if(box != nullptr){
                delete box;
                box = nullptr;
            }
        }
        return finalRet;
    }

    int EyerMP4Box::GetMVHD(EyerMP4Box_mvhd & mvhd)
    {
        if(!HasSub()){
            return -1;
        }

        EyerBuffer buf = buffer;

        int finalRet = -1;
        while (1){
            EyerMP4Box * box = nullptr;
            int ret = Get(&box, buf);
            if(ret){
                break;
            }
            if(box == nullptr){
                continue;
            }

            if(box->GetType() == BoxType::MVHD){
                mvhd = *((EyerMP4Box_mvhd *)box);
                finalRet = 0;
            }

            if(box != nullptr){
                delete box;
                box = nullptr;
            }
        }
        return finalRet;
    }

    int EyerMP4Box::GetMVEX(EyerMP4Box_mvex & mvex)
    {
        if(!HasSub()){
            return -1;
        }

        EyerBuffer buf = buffer;

        int finalRet = -1;
        while (1){
            EyerMP4Box * box = nullptr;
            int ret = Get(&box, buf);
            if(ret){
                break;
            }
            if(box == nullptr){
                continue;
            }

            if(box->GetType() == BoxType::MVEX){
                mvex = *((EyerMP4Box_mvex *)box);
                finalRet = 0;
            }

            if(box != nullptr){
                delete box;
                box = nullptr;
            }
        }
        return finalRet;
    }

    int EyerMP4Box::GetMEHD(EyerMP4Box_mehd & mehd)
    {
        if(!HasSub()){
            return -1;
        }

        EyerBuffer buf = buffer;

        int finalRet = -1;
        while (1){
            EyerMP4Box * box = nullptr;
            int ret = Get(&box, buf);
            if(ret){
                break;
            }
            if(box == nullptr){
                continue;
            }

            if(box->GetType() == BoxType::MEHD){
                mehd = *((EyerMP4Box_mehd *)box);
                finalRet = 0;
            }

            if(box != nullptr){
                delete box;
                box = nullptr;
            }
        }
        return finalRet;
    }

    int EyerMP4Box::GetTREX(EyerMP4Box_trex & trex)
    {
        if(!HasSub()){
            return -1;
        }

        EyerBuffer buf = buffer;

        int finalRet = -1;
        while (1){
            EyerMP4Box * box = nullptr;
            int ret = Get(&box, buf);
            if(ret){
                break;
            }
            if(box == nullptr){
                continue;
            }

            if(box->GetType() == BoxType::TREX){
                trex = *((EyerMP4Box_trex *)box);
                finalRet = 0;
            }

            if(box != nullptr){
                delete box;
                box = nullptr;
            }
        }
        return finalRet;
    }

    int EyerMP4Box::PrintAll()
    {
        PrintBox(*this, 0);
        return 0;
    }

    int EyerMP4Box::PrintBox(EyerMP4Box & box, int depth)
    {
        for(int i=0;i<depth;i++){
            printf("\t");
        }
        box.PrintInfo();

        if(!box.HasSub()){
            return 0;
        }

        EyerBuffer b = box.GetTotalBuffer();

        while(1) {
            Eyer::EyerMP4Box *subBox = nullptr;

            int ret = box.Get(&subBox, b);
            if (ret) {
                break;
            }
            if(subBox == nullptr){
                continue;
            }
            int d = depth + 1;

            PrintBox(*subBox, d);

            if(subBox != nullptr){
                delete subBox;
                subBox = nullptr;
            }
        }

        return 0;
    }
}