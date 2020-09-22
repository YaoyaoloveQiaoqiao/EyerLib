#ifndef EYERLIB_EYERAVC_VLC_HPP
#define EYERLIB_EYERAVC_VLC_HPP

#include "EyerBitStream.hpp"
#include "EyerSyntaxElement.hpp"

namespace Eyer{
    class EyerAVC_VLC {
    public:
        static int read_ue_v                (char * tracestring, EyerBitStream * bitstream, int * used_bits);
        static int read_u_v                 (int LenInBits, char * tracestring, EyerBitStream * bitstream, int * used_bits);
        static Boolean read_u_1             (char * tracestring, EyerBitStream * bitstream, int * used_bits);

        static int readSyntaxElement_VLC(EyerSyntaxElement * sym, EyerBitStream * currStream);
        static int readSyntaxElement_FLC(EyerSyntaxElement * sym, EyerBitStream * currStream);
        static int GetBits (byte * buffer, int totbitoffset, int * info, int bitcount, int numbits);
        static int GetVLCSymbol (byte buffer[], int totbitoffset, int * info, int bytecount);
    };
}

#endif //EYERLIB_EYERAVC_VLC_HPP
