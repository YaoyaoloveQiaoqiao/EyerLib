//
// Created by redknot on 2020/3/29.
//

#include "MBAVPacketQueue.hpp"

namespace MB
{
    MBAVPacketQueue::MBAVPacketQueue()
    {

    }

    MBAVPacketQueue::~MBAVPacketQueue()
    {
        packetQueueMut.lock();

        if(packetQueue.size() > 0) {
            MBAVPacket * pkt = packetQueue.front();
            delete pkt;
            packetQueue.pop();
        }

        packetQueueMut.unlock();
    }

    int MBAVPacketQueue::Push(MBAVPacket * pkt)
    {
        packetQueueMut.lock();

        packetQueue.push(pkt);

        packetQueueMut.unlock();
        return 0;
    }

    int MBAVPacketQueue::Front(MBAVPacket * * pkt)
    {
        packetQueueMut.lock();

        *pkt = packetQueue.front();

        packetQueueMut.unlock();
        return 0;
    }

    int MBAVPacketQueue::FrontPop(MBAVPacket * * pkt)
    {
        packetQueueMut.lock();

        *pkt = packetQueue.front();
        packetQueue.pop();

        packetQueueMut.unlock();
        return 0;
    }
}