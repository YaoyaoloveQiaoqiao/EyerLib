#include "MP4Box.hpp"
#include "MP4BoxFTYP.hpp"
#include "MP4BoxMVHD.hpp"
#include "MP4BoxTKHD.hpp"

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
        // TODO Len
        unsigned char * data = (unsigned char *)malloc(buffer.GetLen());
        buffer.GetBuffer(data);

        uint32_t net_size = 0;
        memcpy(&net_size, data, 4);
        size = ntohl(net_size);


        uint32_t net_type;
        memcpy(&net_type, data + 4, 4);
        type = BoxType::GetType(net_type);


        if(size == 1){
            uint64_t net_largesize = 0;
            memcpy(&net_largesize, data + 4 + 4, 8);
            largesize = ntohl(net_size);
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

        if(data != nullptr){
            free(data);
            data = nullptr;
        }

        return 0;
    }

    int MP4Box::ParseSubBox(EyerBuffer & buffer, int _offset)
    {
        EyerBuffer tempBuffer = buffer;

        int bufferLen = buffer.GetLen();
        unsigned char * data = (unsigned char *)malloc(bufferLen);
        buffer.GetBuffer(data);

        int alreadRead = 0;
        alreadRead += _offset;
        while(1){
            if(alreadRead >= bufferLen){
                break;
            }
            uint32_t net_size = 0;
            memcpy(&net_size, data + alreadRead, 4);
            int boxSize = ntohl(net_size);
            if(boxSize == 1){
                // TODO boxSize == 1
            }

            uint32_t net_type;
            memcpy(&net_type, data + alreadRead + 4, 4);
            BoxType boxtype = BoxType::GetType(net_type);


            alreadRead += boxSize;

            EyerBuffer boxBuffer;
            tempBuffer.CutOff(boxBuffer, boxSize);

            MP4Box * box = CreatBox(boxtype);
            if(box != nullptr){
                box->Parse(boxBuffer);
                // box->PrintInfo();
                subBoxList.push_back(box);
            }
        }

        free(data);
        return 0;
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

        printf("%s[%c%c%c%c]\n", levelStr.str, type.GetA(), type.GetB(), type.GetC(), type.GetD());
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