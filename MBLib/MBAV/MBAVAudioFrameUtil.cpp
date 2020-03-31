//
// Created by redknot on 2020/3/22.
//

#include "MBAV.hpp"

namespace MB
{
    MBAVAudioFrameUtil::MBAVAudioFrameUtil()
    {

    }

    MBAVAudioFrameUtil::~MBAVAudioFrameUtil()
    {
        for(int i=0;i<frameList.getLength();i++){
            MBAVFrameWeight * fw = nullptr;
            frameList.find(i, fw);
            if(fw != nullptr){
                delete fw;
            }
        }
        frameList.clear();
    }

    int MBAVAudioFrameUtil::AddAudioFrame(MBAVFrame & frame, float weight)
    {
        MBAVFrameWeight * fw = new MBAVFrameWeight(frame, weight);
        frameList.insertBack(fw);

        return 0;
    }

    int MBAVAudioFrameUtil::MergeAudioFrame(MBAVFrame & outFrame)
    {
        int maxChannel = outFrame.GetChannels();

        for(int channelIndex=0; channelIndex<maxChannel; channelIndex++){
            int channelDataLen = outFrame.GetPerSampleSize() * outFrame.GetNBSamples();
            for(int dataIndex=0; dataIndex < channelDataLen / 4; dataIndex++){
                // MBLog("Com Data Index : %d\n", dataIndex);
                float data = 0.0f;
                for(int i=0;i<frameList.getLength();i++){
                    MBAVFrameWeight * fw = nullptr;
                    frameList.find(i, fw);
                    if(fw != nullptr){
                        float a = fw->frame->GetAudioFloatData(channelIndex, dataIndex);
                        data += a * fw->weight;
                    }
                }

                outFrame.SetAudioFloatData(channelIndex, dataIndex, data);
            }
        }
        
        return 0;
    }
}