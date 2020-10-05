#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, AnnexB){
    Eyer::EyerString url = "./demo_video.h264";

    std::vector<Eyer::EyerNAL *> nalList;

    Eyer::EyerAnnexB annexB;
    annexB.Open(url);

    while(1){
        Eyer::EyerNALU nalu(8 * 1024 * 1024);
        int ret = annexB.GetAnnexBNALU(nalu);
        // EyerLog("nalu len: %d, nalu type: %d, nalu startcodelen: %d\n", nalu.len, nalu.nal_unit_type, nalu.startcodeprefix_len);
        if(ret <= 0){
            break;
        }

        int len = nalu.len;
        nalu.ToRBSP();

        if(len != nalu.len){
            // EyerLog("nalu len: %d, nalu type: %d, nalu startcodelen: %d\n", nalu.len, nalu.nal_unit_type, nalu.startcodeprefix_len);
        }
        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_SPS){
            EyerLog("SPS\n");
            Eyer::EyerSPS * sps = new Eyer::EyerSPS(nalu);

            nalList.push_back(sps);
            // sps.PrintInfo();
        }
        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_PPS){
            EyerLog("PPS\n");
            Eyer::EyerPPS * pps = new Eyer::EyerPPS(nalu);

            nalList.push_back(pps);
            // pps.PrintInfo();
        }

        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_IDR){
            EyerLog("IDR\n");

            Eyer::EyerIDR * idr = new Eyer::EyerIDR(nalu);
            nalList.push_back(idr);
        }
    }

    annexB.Close();

    for(int i=0;i<nalList.size();i++){
        Eyer::EyerNAL * nal = nalList[i];
        for(int j=0;j<nal->GetFieldSize();j++){
            Eyer::EyerField field;
            // nal->GetField(field, j);
        }
    }

    for(int i=0;i<nalList.size();i++){
        delete nalList[i];
    }
    nalList.clear();
}

TEST(EyerAVC, EyerField){
    Eyer::EyerField fieldA("abc", 12);
    Eyer::EyerField fieldB = fieldA;
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
