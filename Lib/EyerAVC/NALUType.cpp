#include "NALUType.hpp"

namespace Eyer
{
    NALUType NALUType::NALU_TYPE_SLICE      (1, "NALU_TYPE_SLICE");
    NALUType NALUType::NALU_TYPE_DPA        (2, "NALU_TYPE_DPA");
    NALUType NALUType::NALU_TYPE_DPB        (3, "NALU_TYPE_DPB");
    NALUType NALUType::NALU_TYPE_DPC        (4, "NALU_TYPE_DPC");
    NALUType NALUType::NALU_TYPE_IDR        (5, "NALU_TYPE_IDR");
    NALUType NALUType::NALU_TYPE_SEI        (6, "NALU_TYPE_SEI");
    NALUType NALUType::NALU_TYPE_SPS        (7, "NALU_TYPE_SPS");
    NALUType NALUType::NALU_TYPE_PPS        (8, "NALU_TYPE_PPS");
    NALUType NALUType::NALU_TYPE_AUD        (9, "NALU_TYPE_AUD");
    NALUType NALUType::NALU_TYPE_EOSEQ      (10, "NALU_TYPE_EOSEQ");
    NALUType NALUType::NALU_TYPE_EOSTREAM   (11, "NALU_TYPE_EOSTREAM");
    NALUType NALUType::NALU_TYPE_FILL       (12, "NALU_TYPE_FILL");

    NALUType::NALUType(int _val, const EyerString & _name) : EyerEnum(_val, _name)
    {

    }

    NALUType::NALUType(const NALUType & naluType)
    {
        *this = naluType;
    }

    NALUType::NALUType(const int & naluType)
    {
        *this = naluType;
    }

    NALUType::~NALUType()
    {

    }

    NALUType & NALUType::operator = (const NALUType & naluType)
    {
        EyerEnum::operator=(naluType);
        return *this;
    }

    NALUType & NALUType::operator = (const int & naluType)
    {
        if(naluType == 1){
            *this = NALU_TYPE_SLICE;
        }
        else if(naluType == 2){
            *this = NALU_TYPE_DPA;
        }
        else if(naluType == 3){
            *this = NALU_TYPE_DPB;
        }
        else if(naluType == 4){
            *this = NALU_TYPE_DPC;
        }
        else if(naluType == 5){
            *this = NALU_TYPE_IDR;
        }
        else if(naluType == 6){
            *this = NALU_TYPE_SEI;
        }
        else if(naluType == 7){
            *this = NALU_TYPE_SPS;
        }
        else if(naluType == 8){
            *this = NALU_TYPE_PPS;
        }
        else if(naluType == 9){
            *this = NALU_TYPE_AUD;
        }
        else if(naluType == 10){
            *this = NALU_TYPE_EOSEQ;
        }
        else if(naluType == 11){
            *this = NALU_TYPE_EOSTREAM;
        }
        else if(naluType == 12){
            *this = NALU_TYPE_FILL;
        }
        return *this;
    }

    bool NALUType::operator == (const NALUType & naluType)
    {
        return EyerEnum::operator==(naluType);
    }
}