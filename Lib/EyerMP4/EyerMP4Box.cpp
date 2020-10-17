#include "EyerMP4Box.hpp"
#include "EyerMP4Constant.hpp"
#include "EyerMP4Box_ftyp.hpp"
#include "EyerMP4Box_moov.hpp"
#include "EyerMP4Box_mvhd.hpp"
#include "EyerMP4Box_trak.hpp"
#include "EyerMP4Box_tkhd.hpp"

namespace Eyer
{
    EyerMP4Box::EyerMP4Box(const EyerBuffer & _buffer)
    {
        buffer = _buffer;
    }

    EyerMP4Box::~EyerMP4Box()
    {

    }

    int EyerMP4Box::Get(EyerMP4Box * * box)
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

        return 0;
    }


    BoxType EyerMP4Box::GetType()
    {
        return BoxType::UNKNOW;
    }

    int EyerMP4Box::PrintInfo()
    {

        return 0;
    }
}