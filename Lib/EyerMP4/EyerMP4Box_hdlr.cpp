#include "EyerMP4Box_hdlr.hpp"
#include <stdio.h>

namespace Eyer {
    EyerMP4Box_hdlr::EyerMP4Box_hdlr(const EyerBuffer &_buffer) : EyerMP4Box(_buffer)
    {
        int dataLen = buffer.GetBuffer();
        unsigned char * dataArr = (unsigned char *)malloc(dataLen);
        unsigned char * data = dataArr;
        buffer.GetBuffer(data);

        int i = 0;

        data += 4;
        data += 4;

        memcpy(handler_type, data, 4);

        handler_type[MAX_HANDLER_TYPE_LEN] = '\0';

        data += 4;

        data += 12;

        while ('\0' != data[i]) {
            i++;
        }

        memcpy(name, data, i);
        name[i] = '\0';
        name[MAX_HDLR_NAME_LEN] = '\0';


        free(dataArr);
    }

    EyerMP4Box_hdlr::~EyerMP4Box_hdlr()
    {

    }

    BoxType EyerMP4Box_hdlr::GetType()
    {
        return BoxType::HDLR;
    }

    int EyerMP4Box_hdlr::PrintInfo()
    {
        printf("========HDLR========\n");
        printf("thandler_type: %s, name: %s\n", handler_type, name);
        return 0;
    }

    bool EyerMP4Box_hdlr::HasSub()
    {
        return false;
    }
}