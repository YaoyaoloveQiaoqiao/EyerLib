#include "MP4BoxFTYP.hpp"

namespace Eyer
{
    MP4BoxFTYP::MP4BoxFTYP() : MP4Box()
    {

    }

    MP4BoxFTYP::~MP4BoxFTYP()
    {

    }

    int MP4BoxFTYP::ParseParam(EyerBuffer & buffer, int offset)
    {
        unsigned char * data = (unsigned char *)malloc(buffer.GetLen());
        buffer.GetBuffer(data);

        memcpy(major_brand, data + offset, 4);

        printf("MP4BoxFTYP major_brand: %c%c%c%c\n", major_brand[0], major_brand[1], major_brand[2], major_brand[3]);

        uint32_t net_minor_version = 0;
        memcpy(&net_minor_version, data + offset + 4, 4);
        minor_version = ntohl(net_minor_version);

        printf("MP4BoxFTYP minor_version: %d\n", minor_version);


        compatible_brands_len = (buffer.GetLen() - offset - 4 - 4) / 4;

        printf("MP4BoxFTYP compatible_brands_len: %d\n", compatible_brands_len);
        for(int i=0;i<compatible_brands_len;i++){
            memcpy(compatible_brands[i], data + offset + 4 + 4 + i * 4, 4);
            printf("MP4BoxFTYP %c%c%c%c\n", compatible_brands[i][0], compatible_brands[i][1], compatible_brands[i][2],compatible_brands[i][3]);
        }

        free(data);

        return 0;
    }
}