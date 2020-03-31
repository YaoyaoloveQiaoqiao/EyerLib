//
// Created by redknot on 2020/3/29.
//

#ifndef EYE_LIB_EYERAVPACKETQUEUE_HPP
#define EYE_LIB_EYERAVPACKETQUEUE_HPP

#include <queue>
#include <mutex>
#include "MBAV.hpp"

namespace MB
{
    class MBAVPacketQueue {
    public:
        MBAVPacketQueue();
        ~MBAVPacketQueue();

        int Push(MBAVPacket * pkt);
        int Front(MBAVPacket * * pkt);
        int FrontPop(MBAVPacket * * pkt);
    private:
        std::queue<MBAVPacket *> packetQueue;
        std::mutex packetQueueMut;
    };
}

#endif //EYE_LIB_EYERAVPACKETQUEUE_HPP
