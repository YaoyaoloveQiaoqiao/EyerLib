#include "EyerAVCDecoder.hpp"

#include "EyerAnnexB.hpp"
#include "EyerSEI.hpp"
#include "EyerIDR.hpp"
#include "EyerSLICE.hpp"

namespace Eyer
{
    EyerAVCDecoder::EyerAVCDecoder(const EyerString & _path)
    {
        path = _path;
    }

    EyerAVCDecoder::~EyerAVCDecoder()
    {
        for(int i=0;i<nalList.size();i++){
            delete nalList[i];
        }
        nalList.clear();
    }

    int EyerAVCDecoder::DecodeAll()
    {
        Eyer::EyerAnnexB annexB;
        annexB.Open(path);

        while(1){
            Eyer::EyerNALU nalu;
            int ret = annexB.GetAnnexBNALU(nalu);
            if(ret <= 0){
                break;
            }

            int len = nalu.len;
            nalu.ToRBSP();

            if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_SPS){
                Eyer::EyerSPS * _sps = new Eyer::EyerSPS(nalu);
                nalList.push_back(_sps);
                sps = *_sps;
            }
            if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_PPS){
                Eyer::EyerPPS * _pps = new Eyer::EyerPPS(nalu);
                nalList.push_back(_pps);
                pps = *_pps;
            }
            if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_SEI){
                Eyer::EyerSEI * sei = new Eyer::EyerSEI(nalu);
                nalList.push_back(sei);
            }
            if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_IDR){
                Eyer::EyerIDR * idr = new Eyer::EyerIDR(nalu, sps, pps);
                nalList.push_back(idr);
            }
            if(nalu.nal_unit_type == Eyer::NaluType::NALU_TYPE_SLICE){
                Eyer::EyerSLICE * slice = new Eyer::EyerSLICE(nalu, sps, pps);
                nalList.push_back(slice);
            }
        }

        annexB.Close();




        for(int i=0;i<nalList.size();i++){
            Eyer::EyerNAL * nal = nalList[i];
            EyerLog("wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww\n");
            for(int j=0;j<nal->GetFieldSize();j++){
                Eyer::EyerField field;
                nal->GetField(field, j);

                if(field.GetType() == Eyer::EyerFieldType::UNSIGNED_INT){
                    EyerLog("%s = %u, %s\n", field.GetKey().str, field.GetUnsignedIntVal(), field.GetRemarks().str);
                }
                if(field.GetType() == Eyer::EyerFieldType::BOOL){
                    EyerLog("%s = %d, %s\n", field.GetKey().str, field.GetBooleanVal(), field.GetRemarks().str);
                }
                if(field.GetType() == Eyer::EyerFieldType::INT){
                    EyerLog("%s = %d, %s\n", field.GetKey().str, field.GetIntVal(), field.GetRemarks().str);
                }
            }
        }


        return 0;
    }
}