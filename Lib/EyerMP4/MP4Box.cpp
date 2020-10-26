#include "MP4Box.hpp"
#include "MP4BoxFTYP.hpp"
#include "MP4BoxMVHD.hpp"
#include "MP4BoxTKHD.hpp"
#include "MP4BoxELST.hpp"
#include "MP4BoxHDLR.hpp"
#include "MP4BoxDREF.hpp"
#include "MP4BoxURL.hpp"
#include "MP4BoxURN.hpp"
#include "MP4BoxTREX.hpp"
#include "MP4BoxMEHD.hpp"
#include "MP4BoxSTSD.hpp"
#include "MP4BoxSTTS.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4Box::MP4Box()
    {
        type = BoxType::ROOT;
    }

    MP4Box::~MP4Box()
    {
        for(int i=0;i<subBoxList.size();i++){
            delete subBoxList[i];
        }
        subBoxList.clear();
    }

    bool MP4Box::operator == (const MP4Box & box) const
    {
        if(size != box.size) {
            return false;
        }
        if(type != box.type) {
            return false;
        }
        if(largesize != box.largesize) {
            return false;
        }

        return true;
    }

    EyerBuffer MP4Box::Serialize()
    {
        EyerBuffer buffer;

        EyerBuffer contentBuffer;
        if(type.HasSub()){
            contentBuffer = SerializeSubBox();
        }
        else{
            contentBuffer = SerializeParam();
        }

        uint8_t head[8];
        int len = contentBuffer.GetLen() + 8;
        head[0] = *((uint8_t *)(&len) + 3);
        head[1] = *((uint8_t *)(&len) + 2);
        head[2] = *((uint8_t *)(&len) + 1);
        head[3] = *((uint8_t *)(&len) + 0);

        head[4] = type.GetA();
        head[5] = type.GetB();
        head[6] = type.GetC();
        head[7] = type.GetD();

        buffer.Append(head, 8);
        buffer.Append(contentBuffer);

        return buffer;
    }

    EyerBuffer MP4Box::SerializeSubBox()
    {
        EyerBuffer buffer;
        return buffer;
    }

    EyerBuffer MP4Box::SerializeParam()
    {
        EyerBuffer buffer;
        return buffer;
    }

    int MP4Box::Parse(EyerBuffer & buffer)
    {
        int offset = 0;

        MP4Stream stream(buffer);
        size = stream.ReadBigEndian_int32(offset);

        type = BoxType::GetType(stream.Read_uint32(offset));

        if(size == 1){
            largesize = stream.ReadBigEndian_int64(offset);
        }

        // type.PrintInfo();
        if(type.HasSub()){
            EyerBuffer b = buffer;
            EyerBuffer tb;
            b.CutOff(tb, 8);
            ParseSubBox(b, 0);
        }
        else{
            ParseParam(buffer, 8);
        }

        return 0;
    }

    int MP4Box::ParseSubBox(EyerBuffer & buffer, int _offset)
    {
        EyerBuffer tempBuffer = buffer;

        MP4Stream stream(buffer);
        stream.Skip(_offset);

        while (tempBuffer.GetLen() > 0) {
            int offset = 0;
            uint64_t boxSize = stream.ReadBigEndian_uint32(offset);
            BoxType boxtype = BoxType::GetType(stream.Read_uint32(offset));
            if(boxSize == 1){
                boxSize = stream.ReadBigEndian_uint64(offset);
            }

            EyerBuffer boxBuffer;
            tempBuffer.CutOff(boxBuffer, (int)boxSize);

            stream.Skip(boxSize - offset);

            MP4Box * box = CreatBox(boxtype);
            if(box != nullptr){
                box->Parse(boxBuffer);
                subBoxList.push_back(box);
            }
        }
        return _offset;
    }

    int MP4Box::ParseParam(EyerBuffer & buffer, int offset)
    {
        return offset;
    }

    uint64_t MP4Box::GetSize()
    {
        if(size == 1){
            return largesize;
        }
        return size;
    }

    BoxType MP4Box::GetType()
    {
        return type;
    }

    MP4Box * MP4Box::GetSubBoxPtr(BoxType type)
    {
        MP4Box * subBox = nullptr;
        for(int i=0;i<subBoxList.size();i++){
            if(subBoxList[i]->type == type){
                subBox = CopyBox(subBoxList[i]);
            }
        }
        return subBox;
    }

    int MP4Box::PrintInfo(int level)
    {
        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }

        printf("%s[%c%c%c%c] (%d bytes)\n", levelStr.str, type.GetA(), type.GetB(), type.GetC(), type.GetD(), size);
        if(type.HasSub()){
            for(int i=0;i<subBoxList.size();i++){
                MP4Box * box = subBoxList[i];
                box->PrintInfo(level + 1);
            }
        }
        return 0;
    }

    MP4Box * MP4Box::CreatBox(BoxType type)
    {
        MP4Box * box = nullptr;
        if(type.HasSub()){
            box = new MP4Box();
        }
        else{
            if(type == BoxType::FTYP){
                box = new MP4BoxFTYP();
            }
            else if(type == BoxType::MVHD){
                box = new MP4BoxMVHD();
            }
            else if(type == BoxType::TKHD){
                box = new MP4BoxTKHD();
            }
            else if(type == BoxType::ELST){
                box = new MP4BoxELST();
            }
            else if(type == BoxType::HDLR){
                box = new MP4BoxHDLR();
            }
            else if(type == BoxType::DREF){
                box = new MP4BoxDREF();
            }
            else if(type == BoxType::URL){
                box = new MP4BoxURL();
            }
            else if(type == BoxType::URN){
                box = new MP4BoxURN();
            }
            else if(type == BoxType::TREX){
                box = new MP4BoxTREX();
            }
            else if(type == BoxType::MEHD){
                box = new MP4BoxMEHD();
            }
            else if(type == BoxType::STSD){
                box = new MP4BoxSTSD();
            }
            else if(type == BoxType::STTS){
                box = new MP4BoxSTTS();
            }
        }

        return box;
    }
    MP4Box * MP4Box::CopyBox(MP4Box * box)
    {
        MP4Box * dest = CreatBox(box->type);
        *dest = *box;
        return dest;
    }
}