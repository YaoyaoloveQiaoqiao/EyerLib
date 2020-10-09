#include <gtest/gtest.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerAVC/EyerAVC.hpp"

TEST(EyerAVC, AnnexB){
    // Eyer::EyerString url = "C:/Video/video.h264";
    // Eyer::EyerString url = "/Users/lichi/annie/xinxiaomen.h264";
    // Eyer::EyerString url = "/Users/lichi/annie/xinxiaomen.h264";
    Eyer::EyerString url = "./demo_video.h264";

    std::vector<Eyer::EyerNAL *> nalList;

    Eyer::EyerAnnexB annexB;
    annexB.Open(url);

    while(1){
        Eyer::EyerNALU nalu(8 * 1024 * 1024);
        int ret = annexB.GetAnnexBNALU(nalu);
        if(ret <= 0){
            break;
        }

        int len = nalu.len;
        nalu.ToRBSP();

        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_SPS){
            Eyer::EyerSPS * sps = new Eyer::EyerSPS(nalu);
            nalList.push_back(sps);
        }
        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_PPS){
            Eyer::EyerPPS * pps = new Eyer::EyerPPS(nalu);
            nalList.push_back(pps);
        }
        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_SEI){
            Eyer::EyerSEI * sei = new Eyer::EyerSEI(nalu);
            nalList.push_back(sei);
        }
        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_IDR){
            Eyer::EyerIDR * idr = new Eyer::EyerIDR(nalu);
            nalList.push_back(idr);
        }
        if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_SLICE){
            Eyer::EyerSLICE * slice = new Eyer::EyerSLICE(nalu);
            nalList.push_back(slice);
        }
    }

    annexB.Close();

    // EyerLog("Nal List: %d\n", nalList.size());

    for(int i=0;i<nalList.size();i++){
        Eyer::EyerNAL * nal = nalList[i];
        // EyerLog("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
        for(int j=0;j<nal->GetFieldSize();j++){
            Eyer::EyerField field;
            nal->GetField(field, j);

            if(field.GetType() == Eyer::EyerFieldType::UNSIGNED_INT){
                // EyerLog("%s = %u, %s\n", field.GetKey().str, field.GetUnsignedIntVal(), field.GetRemarks().str);
            }
            if(field.GetType() == Eyer::EyerFieldType::BOOL){
                // EyerLog("%s = %d, %s\n", field.GetKey().str, field.GetBooleanVal(), field.GetRemarks().str);
            }
            if(field.GetType() == Eyer::EyerFieldType::INT){
                // EyerLog("%s = %d, %s\n", field.GetKey().str, field.GetIntVal(), field.GetRemarks().str);
            }
        }
    }

    for(int i=0;i<nalList.size();i++){
        delete nalList[i];
    }
    nalList.clear();
}

TEST(EyerAVC, Decoder)
{
    Eyer::EyerAVCDecoder avcDeocder("./demo_video.h264");
    avcDeocder.DecodeAll();
}

TEST(EyerAVC, EyerField){
    Eyer::EyerField fieldA("abc", 12);
    Eyer::EyerField fieldB = fieldA;
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
