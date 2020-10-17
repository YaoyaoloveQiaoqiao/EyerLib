#include "EyerMP4Box_moov.hpp"

namespace Eyer
{
    EyerMP4Box_moov::EyerMP4Box_moov(int _boxSize, const EyerBuffer & _buffer) : EyerMP4Box(_boxSize)
    {
        buffer = _buffer;

        int bufferDataLen = buffer.GetBuffer();
        unsigned char * boxData = (unsigned char *)malloc(bufferDataLen);
        buffer.GetBuffer(boxData);

        //// <==========================================>

        unsigned char * moovData = boxData;
        int moovDataSize = _boxSize;

        

        //// <==========================================>
        free(boxData);
    }

    EyerMP4Box_moov::~EyerMP4Box_moov()
    {

    }
}
