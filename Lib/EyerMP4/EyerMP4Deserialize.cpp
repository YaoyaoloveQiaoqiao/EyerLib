#include "EyerMP4Deserialize.hpp"
#include "EyerMP4Box_ftyp.hpp"
#include "EyerMP4Box_moov.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    EyerMP4Deserialize::EyerMP4Deserialize(EyerBuffer & _buffer)
    {
        buffer = _buffer;
    }

    EyerMP4Deserialize::~EyerMP4Deserialize()
    {

    }

    int EyerMP4Deserialize::Get(EyerMP4Box & box)
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
            EyerMP4Box_ftyp ftypBox(boxSize, boxDataBuffer);
        }
        else if (0 == strcmp((char *)boxType, BOX_TYPE_MOOV)){
            EyerMP4Box_moov moovBox(boxSize, boxDataBuffer);
        }

        return 0;
    }
}