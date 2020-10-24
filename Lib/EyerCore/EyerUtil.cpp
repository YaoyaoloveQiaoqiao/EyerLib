#include "EyerUtil.hpp"

namespace Eyer
{
    uint64_t EyerUtil::EndianNtohll(uint64_t val)
    {
        uint64_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = a[0] << 56 | a[1] << 48 | a[2] << 40 | a[3] << 32 | a[4] << 24 | a[5] << 16 | a[6] << 8 | a[7];
        }
        else{
            res = val;
        }
        return res;
    }

    uint32_t EyerUtil::EndianNtohl(uint32_t val)
    {
        uint32_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = a[0] << 24 | a[1] << 16 | a[2] << 8 | a[3];
        }
        else{
            res = val;
        }
        return res;
    }

    uint16_t EyerUtil::EndianNtohs         (uint16_t val)
    {
        uint16_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = a[0] << 8 | a[1];
        }
        else{
            res = val;
        }
        return res;
    }




    uint64_t EyerUtil::EndianHtonll(uint64_t val)
    {
        uint64_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = a[0] << 56 | a[1] << 48 | a[2] << 40 | a[3] << 32 | a[4] << 24 | a[5] << 16 | a[6] << 8 | a[7];
        }
        else{
            res = val;
        }
        return res;
    }

    uint32_t EyerUtil::EndianHtonl         (uint32_t val)
    {
        uint32_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = a[0] << 24 | a[1] << 16 | a[2] << 8 | a[3];
        }
        else{
            res = val;
        }
        return res;
    }

    uint16_t EyerUtil::EndianHtons         (uint16_t val)
    {
        uint16_t res;
        if(CheckCPU()){
            // 小端
            uint8_t * a = (uint8_t *)&val;
            res = a[0] << 8 | a[1];
        }
        else{
            res = val;
        }
        return res;
    }

    bool EyerUtil::CheckCPU()
    {
        union w
        {
            int a;
            char b;
        }c;

        c.a = 1;
        return (c.b == 1);
    }
}