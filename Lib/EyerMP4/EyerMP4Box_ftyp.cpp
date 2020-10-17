#include "EyerMP4Box_ftyp.hpp"
#include <stdlib.h>

namespace Eyer
{
    EyerMP4Box_ftyp::EyerMP4Box_ftyp(int _boxSize, const EyerBuffer & _buffer) : EyerMP4Box(_boxSize)
    {
        buffer = _buffer;

        int bufferDataLen = buffer.GetBuffer();
        unsigned char * boxData = (unsigned char *)malloc(bufferDataLen);
        buffer.GetBuffer(boxData);

        //// <==========================================>

        memcpy(major_brand, boxData, 4);
        major_brand[MAX_FTYP_BRABDS_LEN] = '\0';

        minor_version = boxData[4] << 24 | boxData[5] << 16 | boxData[6] << 8 | boxData[7];

        int brandsNum = (boxSize - MAX_BOX_SIZE_LEN - MAX_BOX_TYPE_LEN - MAX_FTYP_BRABDS_LEN - 4) / 4;
        for (int i=0; i<brandsNum; i++) {
            memcpy(compatible_brands[i].brands, boxData + MAX_FTYP_BRABDS_LEN + 4 + 4 * i, 4);
            compatible_brands[i].brands[MAX_FTYP_BRABDS_LEN] = '\0';
        }

        //// <==========================================>



        printf("\tmajor_brand: %s, minor_version: %d, compatible_brands: ", major_brand, minor_version);

        for (int i=0; i<brandsNum; i++) {
            if (i==brandsNum-1) {
                printf("%s", compatible_brands[i].brands);
            }
            else {
                printf("%s,", compatible_brands[i].brands);
            }
        }

        printf("\n");

        free(boxData);
    }

    EyerMP4Box_ftyp::~EyerMP4Box_ftyp()
    {

    }
}