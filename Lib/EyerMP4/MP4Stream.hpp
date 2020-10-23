#ifndef EYERLIB_MP4STREAM_HPP
#define EYERLIB_MP4STREAM_HPP

#include "EyerCore/EyerCore.hpp"
#include <stdint.h>

namespace Eyer
{
    class MP4Stream {
    public:
        MP4Stream(EyerBuffer & buffer);
        ~MP4Stream();

        uint64_t ReadBigEndian_uint64(int & offset);
        uint32_t ReadBigEndian_uint32(int & offset);
        uint16_t ReadBigEndian_uint16(int & offset);
        float ReadBigEndianFixedPoint(unsigned int integerLength, unsigned int fractionalLength, int & offset);
        int Skip(int len, int & offset);
        int Skip(int len);

        int WriteBigEndian(uint64_t val);
        int WriteBigEndian(uint32_t val);
        int WriteBigEndian(uint16_t val);
        int WriteBigEndian(uint8_t  val);
        int WriteZero(int len);

        int WriteBigEndianFixedPoint(float val, unsigned int integerLength, unsigned int fractionalLength);

        EyerBuffer & GetBuffer();
    private:
        EyerBuffer buffer;
    };
}



#endif //EYERLIB_MP4STREAM_HPP
