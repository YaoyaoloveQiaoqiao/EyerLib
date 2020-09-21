#ifndef EYERLIB_EYERBITSTREAM_HPP
#define EYERLIB_EYERBITSTREAM_HPP

#include "EyerAVCCommon.hpp"

namespace Eyer{
    class EyerBitStream {
        /*
        int           read_len;           //!< actual position in the codebuffer, CABAC only
        int           code_len;           //!< overall codebuffer length, CABAC only
        // CAVLC Decoding
        int           frame_bitoffset;    //!< actual position in the codebuffer, bit-oriented, CAVLC only
        int           bitstream_length;   //!< over codebuffer lnegth, byte oriented, CAVLC only
        // ErrorConcealment
        unsigned char * streamBuffer;      //!< actual codebuffer for read bytes
        int           ei_flag;            //!< error indication, 0: no error, else unspecified error
        */

    public:
        int           read_len;           //!< actual position in the codebuffer, CABAC only
        int           code_len;           //!< overall codebuffer length, CABAC only

        int           frame_bitoffset;    //!< actual position in the codebuffer, bit-oriented, CAVLC only
        int           bitstream_length;   //!< over codebuffer lnegth, byte oriented, CAVLC only

        byte *        streamBuffer = nullptr;      //!< actual codebuffer for read bytes
        int           ei_flag;            //!< error indication, 0: no error, else unspecified error

    public:
        EyerBitStream(byte * stream, int len);
        ~EyerBitStream();
    };
}

#endif //EYERLIB_EYERBITSTREAM_HPP
