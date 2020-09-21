#include "EyerAVC_VLC.hpp"
#include "EyerSyntaxElement.hpp"

#define SE_HEADER           0

namespace Eyer
{
    int EyerAVC_VLC::read_u_v (int LenInBits, char * tracestring, EyerBitStream *bitstream, int *used_bits)
    {
        EyerSyntaxElement symbol;

        symbol.inf = 0;
        symbol.type = SE_HEADER;
        symbol.len = LenInBits;
        readSyntaxElement_FLC (&symbol, bitstream);
        *used_bits += symbol.len;

        return symbol.inf;
    }

    Boolean EyerAVC_VLC::read_u_1 (char *tracestring, EyerBitStream * bitstream, int *used_bits)
    {
        return (Boolean) read_u_v (1, tracestring, bitstream, used_bits);
    }


    int EyerAVC_VLC::readSyntaxElement_FLC(EyerSyntaxElement * sym, EyerBitStream * currStream)
    {
        int BitstreamLengthInBits  = (currStream->bitstream_length << 3) + 7;

        if ((GetBits(currStream->streamBuffer, currStream->frame_bitoffset, &(sym->inf), BitstreamLengthInBits, sym->len)) < 0){
            return -1;
        }

        sym->value1 = sym->inf;
        currStream->frame_bitoffset += sym->len; // move bitstream pointer

        return 1;
    }

    int EyerAVC_VLC::GetBits (unsigned char * buffer,int totbitoffset, int *info, int bitcount, int numbits)
    {
        if ((totbitoffset + numbits ) > bitcount) {
            return -1;
        }
        else {
            int bitoffset  = 7 - (totbitoffset & 0x07); // bit from start of byte
            int byteoffset = (totbitoffset >> 3); // byte from start of buffer
            int bitcounter = numbits;
            unsigned char * curbyte  = &(buffer[byteoffset]);
            int inf = 0;

            while (numbits--)
            {
                inf <<=1;
                inf |= ((*curbyte)>> (bitoffset--)) & 0x01;
                if (bitoffset == -1 )
                { //Move onto next byte to get all of numbits
                    curbyte++;
                    bitoffset = 7;
                }
                // Above conditional could also be avoided using the following:
                // curbyte   -= (bitoffset >> 3);
                // bitoffset &= 0x07;
            }
            *info = inf;

            return bitcounter;           // return absolute offset in bit from start of frame
        }
    }
}