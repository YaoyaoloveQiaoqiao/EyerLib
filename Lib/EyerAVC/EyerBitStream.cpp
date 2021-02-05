#include "EyerBitStream.hpp"

namespace Eyer
{
    EyerBitStream::EyerBitStream(EyerBuffer & buffer) : EyerBitStream(buffer.GetPtr(), buffer.GetLen())
    {

    }

    EyerBitStream::EyerBitStream(uint8_t * buf, size_t size)
    {
        start = buf;
        p = buf;
        end = buf + size;
        bits_left = 8;
    }
    EyerBitStream::~EyerBitStream()
    {

    }

    int EyerBitStream::PrintInfo(int level)
    {
        int byteOffset = p - start;
        EyerLogLevel(level, "bit offset: %d / %d\n", byteOffset * 8 + (8 - bits_left), (end - start) * 8);
        return 0;
    }

    uint32_t EyerBitStream::bs_read_u8()
    {
        return bs_read_u(8);
    }

    uint32_t EyerBitStream::bs_read_u(int n)
    {
        uint32_t r = 0;
        int i;
        for (i = 0; i < n; i++) {
            r |= ( bs_read_u1() << ( n - i - 1 ) );
        }
        return r;
    }

    uint32_t EyerBitStream::bs_peek_u(int n)
    {
        uint32_t r = 0;

        int temp_bits_left = bits_left;
        uint8_t * temp_p = p;

        for(int i=0; i<n; i++){

            uint32_t r_u = 0;
            temp_bits_left--;
            if (!bs_eof()) {
                r_u = ((*(temp_p)) >> temp_bits_left) & 0x01;
            }
            if (temp_bits_left == 0) {
                temp_p++;
                temp_bits_left = 8;
            }

            r |= ( r_u << ( n - i - 1 ) );
        }

        return r;
    }

    uint32_t EyerBitStream::bs_read_u1()
    {
        uint32_t r = 0;
        bits_left--;
        if (!bs_eof()) {
            r = ((*(p)) >> bits_left) & 0x01;
        }
        if (bits_left == 0) {
            p++;
            bits_left = 8;
        }
        return r;
    }

    void EyerBitStream::bs_skip_u(int n)
    {
        for (int i = 0; i < n; i++ )
        {
            bs_skip_u1();
        }
    }

    void EyerBitStream::bs_skip_u1()
    {
        bits_left--;
        if (bits_left == 0) {
            p++;
            bits_left = 8;
        }
    }

    uint32_t EyerBitStream::bs_read_ue()
    {
        int32_t r = 0;
        int i = 0;
        while((bs_read_u1() == 0) && (i < 32) && (!bs_eof()) ){
            i++;
        }
        r = bs_read_u(i);
        r += (1 << i) - 1;
        return r;
    }

    int32_t EyerBitStream::bs_read_se()
    {
        int32_t r = bs_read_ue();
        if (r & 0x01) {
            r = (r+1)/2;
        }
        else {
            r = -(r/2);
        }
        return r;
    }

    uint32_t EyerBitStream::bs_read_ae()
    {
        return 0;
    }

    int EyerBitStream::bs_eof()
    {
        if (p >= end) {
            return 1;
        }
        else {
            return 0;
        }
    }

    bool EyerBitStream::bs_byte_aligned()
    {
        return bits_left == 8;
    }

    bool EyerBitStream::more_data()
    {
        EyerBitStream tempBitstream(end - 1, 1);

        int lastByte[8];
        // int index_rbsp_stop_one_bit = 8;
        for(int i=0;i<8;i++){
            lastByte[i] = tempBitstream.bs_read_u1();
        }

        int traing_len = 0;
        for(int i=7;i>=0;i--){
            traing_len++;
            if(lastByte[i] == 1){
                break;
            }
        }

        EyerERROR("traing_len: %d\n", traing_len);

        int p_pos = p - start;
        if(p_pos < (end - start - 1)){
            return true;
        }

        if(p_pos = (end - start)){
            if(bits_left > traing_len){
                return true;
            }
            else{
                return false;
            }
        }

        return false;
    }

    int32_t EyerBitStream::bs_read_me(int ChromaArrayType, MB_PART_PRED_MODE predMode)
    {
        uint32_t ue_index = bs_read_ue();
        // EyerLog("UE index: %d\n", ue_index);
        uint32_t val = 0;
        // Table
        if(ChromaArrayType == 1 || ChromaArrayType == 2){
            if(predMode == MB_PART_PRED_MODE::Intra_4x4 || predMode == MB_PART_PRED_MODE::Intra_8x8){
                uint32_t codec_block_pattern[] = {
                        47, 31, 15, 0,
                        23, 27, 29, 30,
                        7, 11, 13, 14,
                        39, 43, 45, 46,
                        16, 3, 5, 10,
                        12, 19, 21, 26,
                        28, 35, 37, 42,
                        44, 1, 2, 4,
                        8, 17, 18, 20,
                        24, 6, 9, 22,
                        25, 32, 33, 34,
                        36, 40, 38, 41
                };
                val = codec_block_pattern[ue_index];
            }
            else if(predMode == MB_PART_PRED_MODE::Intra_16x16){
                uint32_t codec_block_pattern[] = {
                        0, 16, 1, 2,
                        4, 8, 32, 3,
                        5, 10, 12, 15,
                        47, 7, 11, 13,
                        14, 6, 9, 31,
                        35, 37, 42, 44,
                        33, 34, 36, 40,
                        39, 43, 45, 46,
                        17, 18, 20, 24,
                        19, 12, 26, 28,
                        23, 27, 29, 30,
                        22, 25, 38, 41
                };
                val = codec_block_pattern[ue_index];
            }
        }

        if(ChromaArrayType == 0 || ChromaArrayType == 3){
            if(predMode == MB_PART_PRED_MODE::Intra_4x4 || predMode == MB_PART_PRED_MODE::Intra_8x8){
                uint32_t codec_block_pattern[] = {
                        15, 0, 7, 11,
                        13, 14, 3, 5,
                        10, 12, 1, 2,
                        4, 8, 6, 9
                };
                val = codec_block_pattern[ue_index];
            }
            else if(predMode == MB_PART_PRED_MODE::Intra_16x16){
                uint32_t codec_block_pattern[] = {
                        0, 1, 2, 4,
                        8, 3, 5, 10,
                        12, 15, 7, 11,
                        13, 14, 6, 9
                };
                val = codec_block_pattern[ue_index];
            }
        }

        return val;
    }
}