#include "EyerMP4Box_mehd.hpp"

namespace Eyer
{
    EyerMP4Box_mehd::EyerMP4Box_mehd() : EyerMP4Box()
    {
        int dataLen = buffer.GetBuffer();
        unsigned char * dataArr = (unsigned char *)malloc(dataLen);
        unsigned char * data = dataArr;
        buffer.GetBuffer(data);


        free(dataArr);
    }

    EyerMP4Box_mehd::EyerMP4Box_mehd(const EyerBuffer & _buffer) : EyerMP4Box(_buffer)
    {

    }

    EyerMP4Box_mehd::~EyerMP4Box_mehd()
    {

    }

    BoxType EyerMP4Box_mehd::GetType()
    {
        return BoxType::MEHD;
    }

    int EyerMP4Box_mehd::PrintInfo()
    {
        printf("========MEHD========\n");
        return 0;
    }

    bool EyerMP4Box_mehd::HasSub()
    {
        return false;
    }
}