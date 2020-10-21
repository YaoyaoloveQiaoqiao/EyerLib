#include "MP4Box.hpp"

namespace Eyer
{
    MP4Box::MP4Box()
    {

    }

    MP4Box::~MP4Box()
    {

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

        free(data);
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