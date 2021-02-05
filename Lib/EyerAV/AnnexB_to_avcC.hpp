#ifndef EYERLIB_ANNEXB_TO_AVCC_HPP
#define EYERLIB_ANNEXB_TO_AVCC_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class AnnexB_to_avcC {
    public:
        AnnexB_to_avcC();
        ~AnnexB_to_avcC();

        int SendAnnexB(uint8_t * buf, int bufLen);
        int SendAnnexB(EyerBuffer & annexBBuffer);
        int RecvAvcC(EyerBuffer & avccBuffer, bool & isExtradata);

    private:
        bool CheckStartCode(int & startCodeLen, uint8_t * bufPtr, int bufLen);

        std::queue<EyerBuffer *> naluQueue;

        EyerBuffer spsBuf;
        int spsStartCodeLen = 0;

        EyerBuffer ppsBuf;
        int ppsStartCodeLen = 0;
    };
}


#endif //EYERLIB_ANNEXB_TO_AVCC_HPP
