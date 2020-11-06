#include "EyerNALU.hpp"

namespace Eyer
{
    EyerNALU::EyerNALU()
    {

    }

    EyerNALU::EyerNALU(const EyerNALU & nalu)
    {
        *this = nalu;
    }

    EyerNALU::~EyerNALU()
    {
        for(int i=0;i<fieldList.size();i++){
            delete fieldList[i];
        }
        fieldList.clear();
    }

    EyerNALU & EyerNALU::operator = (const EyerNALU & nalu)
    {
        naluData    = nalu.naluData;
        valid       = nalu.valid;

        for(int i=0;i<fieldList.size();i++){
            delete fieldList[i];
        }
        fieldList.clear();

        for( int i = 0; i < nalu.fieldList.size(); i++ ){
            EyerField * f = nalu.fieldList[i];
            EyerField * tempF = new EyerField(*f);
            fieldList.push_back(tempF);
        }

        return *this;
    }

    int EyerNALU::SetNALUData(EyerNALUData & _naluData)
    {
        naluData = _naluData;
        return 0;
    }

    NALUType & EyerNALU::GetNALUType()
    {
        return naluData.GetNALUType();
    }

    int EyerNALU::Parse()
    {
        for(int i=0;i<fieldList.size();i++){
            delete fieldList[i];
        }
        fieldList.clear();
        return 0;
    }

    bool EyerNALU::isValid()
    {
        return valid;
    }

    int EyerNALU::PrintInfo()
    {
        EyerLog("==============================================================\n");
        for(int i=0;i<fieldList.size();i++){
            EyerField * field = fieldList[i];
            EyerString key = field->GetKey();
            EyerFieldType type = field->GetType();

            EyerString levelStr = "";
            for(int i=0;i<field->GetLevel();i++){
                levelStr = levelStr + "\t";
            }
            if(type == EyerFieldType::UNSIGNED_INT){
                EyerLog("%s%s = %u\n", levelStr.str, key.str, field->GetUnsignedIntVal());
            }
            else if(type == EyerFieldType::INT){
                EyerLog("%s%s = %d\n", levelStr.str, key.str, field->GetIntVal());
            }
            else if(type == EyerFieldType::VOID){
                EyerLog("%s%s\n", levelStr.str, key.str);
            }
        }
        EyerLog("==============================================================\n");
        return 0;
    }

    int EyerNALU::intlog2(int x)
    {
        int log = 0;
        if (x < 0) { x = 0; }
        while ((x >> log) > 0)
        {
            log++;
        }
        if (log > 0 && x == 1<<(log-1)) { log--; }
        return log;
    }
}