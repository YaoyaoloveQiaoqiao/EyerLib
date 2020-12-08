#include "EyerRTPServerThread.hpp"

#include <jrtplib3/rtpsession.h>
#include <jrtplib3/rtppacket.h>
#include <jrtplib3/rtpudpv4transmitter.h>
#include <jrtplib3/rtpipv4address.h>
#include <jrtplib3/rtpsessionparams.h>
#include <jrtplib3/rtperrors.h>
#include <jrtplib3/rtpsourcedata.h>
#include <jrtplib3/rtpmemoryobject.h>

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerRTPServerThread::EyerRTPServerThread()
    {

    }

    EyerRTPServerThread::~EyerRTPServerThread()
    {

    }

    void EyerRTPServerThread::Run()
    {
        int rtpPort = 6000;

        jrtplib::RTPSession session;

        jrtplib::RTPSessionParams sessionParams;
        sessionParams.SetOwnTimestampUnit(1.0 / 9000.0);
        sessionParams.SetUsePollThread(true);
        sessionParams.SetAcceptOwnPackets(true);

        jrtplib::RTPUDPv4TransmissionParams transParams;
        transParams.SetRTPReceiveBuffer(1024 * 1024 * 5);
        transParams.SetPortbase(rtpPort);

        int status = session.Create(sessionParams, &transParams);

        if (status < 0) {
            EyerLog("Create Error: %s\n", jrtplib::RTPGetErrorString(status).c_str());
            return;
        }



        while(!stopFlag){
            session.BeginDataAccess();

            if (session.GotoFirstSourceWithData()){
                do {
                    jrtplib::RTPPacket * pack;
                    while ((pack = session.GetNextPacket()) != NULL)
                    {
                        jrtplib::RTPSourceData * mRTPSourceData = session.GetCurrentSourceInfo();
                        uint32_t ssrc = mRTPSourceData->GetSSRC();
                        int cameraId = ssrc - 100000000;

                        EyerLog("ssrc: %d\n", ssrc);

                        session.DeletePacket(pack);
                    }
                }
                while (session.GotoNextSourceWithData());
            }

            session.EndDataAccess();

            status = session.Poll();
            if (status < 0) {
                EyerLog("Poll Error: %s\n", jrtplib::RTPGetErrorString(status).c_str());
            }
        }

        session.BYEDestroy(jrtplib::RTPTime(10, 0), 0, 0);
    }
}