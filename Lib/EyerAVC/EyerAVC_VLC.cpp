#include "EyerCore/EyerCore.hpp"
#include "EyerAVC_VLC.hpp"
#include "EyerSyntaxElement.hpp"

#define SE_HEADER           0

namespace Eyer
{
    int EyerAVC_VLC::read_se_v (const char * tracestring, EyerBitStream * bitstream, int * used_bits)
    {
        EyerLog("%s\n", tracestring);

        EyerSyntaxElement symbol;
        symbol.type = SE_HEADER;
        symbol.SetMappingType(SyntaxElementMappingType::linfo_se);
        readSyntaxElement_VLC (&symbol, bitstream);
        *used_bits += symbol.len;
        return symbol.value1;
    }

    int EyerAVC_VLC::read_ue_v (const char * tracestring, EyerBitStream * bitstream, int * used_bits)
    {
        EyerLog("%s\n", tracestring);

        EyerSyntaxElement symbol;
        symbol.type = SE_HEADER;
        symbol.SetMappingType(SyntaxElementMappingType::linfo_ue);
        readSyntaxElement_VLC (&symbol, bitstream);
        *used_bits += symbol.len;

        return symbol.value1;
    }

    int EyerAVC_VLC::read_u_v (int LenInBits, const char * tracestring, EyerBitStream * bitstream, int * used_bits)
    {
        EyerLog("%s\n", tracestring);

        EyerSyntaxElement symbol;
        symbol.inf = 0;
        symbol.type = SE_HEADER;
        symbol.len = LenInBits;
        readSyntaxElement_FLC (&symbol, bitstream);
        *used_bits += symbol.len;
        return symbol.inf;
    }

    Boolean EyerAVC_VLC::read_u_1 (const char * tracestring, EyerBitStream * bitstream, int * used_bits)
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

    int EyerAVC_VLC::readSyntaxElement_VLC(EyerSyntaxElement *sym, EyerBitStream * currStream)
    {
        sym->len = GetVLCSymbol (currStream->streamBuffer, currStream->frame_bitoffset, &(sym->inf), currStream->bitstream_length);
        if (sym->len == -1)
            return -1;

        currStream->frame_bitoffset += sym->len;
        sym->mapping(sym->len, sym->inf, &(sym->value1), &(sym->value2));

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

            while (numbits--) {
                inf <<=1;
                inf |= ((*curbyte)>> (bitoffset--)) & 0x01;
                if (bitoffset == -1 ) { //Move onto next byte to get all of numbits
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

    int EyerAVC_VLC::GetVLCSymbol (byte buffer[],int totbitoffset,int *info, int bytecount)
    {
        long byteoffset = (totbitoffset >> 3);         // byte from start of buffer
        int  bitoffset  = (7 - (totbitoffset & 0x07)); // bit from start of byte
        int  bitcounter = 1;
        int  len        = 0;
        byte *cur_byte  = &(buffer[byteoffset]);
        int  ctr_bit    = ((*cur_byte) >> (bitoffset)) & 0x01;  // control bit for current bit posision

        while (ctr_bit == 0) {                 // find leading 1 bit
            len++;
            bitcounter++;
            bitoffset--;
            bitoffset &= 0x07;
            cur_byte  += (bitoffset == 7);
            byteoffset+= (bitoffset == 7);
            ctr_bit    = ((*cur_byte) >> (bitoffset)) & 0x01;
        }

        if (byteoffset + ((len + 7) >> 3) > bytecount){
            return -1;
        }
        else {
            // make infoword
            int inf = 0;                          // shortest possible code is 1, then info is always 0

            while (len--) {
                bitoffset --;
                bitoffset &= 0x07;
                cur_byte  += (bitoffset == 7);
                bitcounter++;
                inf <<= 1;
                inf |= ((*cur_byte) >> (bitoffset)) & 0x01;
            }

            *info = inf;
            return bitcounter;           // return absolute offset in bit from start of frame
        }
    }
}