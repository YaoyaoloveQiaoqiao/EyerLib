#include "MP4Box.hpp"
#include "MP4BoxFTYP.hpp"

namespace Eyer
{
    MP4Box::MP4Box()
    {

    }

    MP4Box::~MP4Box()
    {
        for(int i=0;i<subBoxList.size();i++){
            delete subBoxList[i];
        }
        subBoxList.clear();
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
            ParseSubBox(buffer, 8);
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


            uint32_t net_type;
            memcpy(&net_type, data + alreadRead + 4, 4);
            BoxType boxtype = BoxType::GetType(net_type);
            boxtype.PrintInfo();


            alreadRead += boxSize;

            EyerBuffer boxBuffer;
            tempBuffer.CutOff(boxBuffer, boxSize);

            if(boxtype.HasSub()){
                MP4Box * box = new MP4Box();
                box->Parse(boxBuffer);
                subBoxList.push_back(box);
            }
            else{
                if(boxtype == BoxType::FTYP){
                    MP4BoxFTYP * ftyp = new MP4BoxFTYP();
                    ftyp->Parse(boxBuffer);
                    subBoxList.push_back(ftyp);
                }
            }
        }

        free(data);
        return 0;
    }

    int MP4Box::ParseParam(EyerBuffer & buffer, int offset)
    {
        printf("ParseParam\n");
        return 0;
    }

    uint64_t MP4Box::GetSize()
    {
        if(size == 1){
            return largesize;
        }
        return size;
    }
}