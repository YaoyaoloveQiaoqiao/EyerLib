#ifndef EYERLIB_EYERAVCCOMMON_HPP
#define EYERLIB_EYERAVCCOMMON_HPP

namespace Eyer{

    typedef unsigned char byte;

    typedef enum {
        FALSE,
        TRUE
    } Boolean;

    class EyerAVCCommon {
    public:
        static const int ZEROBYTES_SHORTSTARTCODE = 2;
        static int EBSPtoRBSP(unsigned char * streamBuffer, int end_bytepos, int begin_bytepos);
        static int RBSPtoSODB(unsigned char * streamBuffer, int last_byte_pos);
    };
}

#endif //EYERLIB_EYERAVCCOMMON_HPP
