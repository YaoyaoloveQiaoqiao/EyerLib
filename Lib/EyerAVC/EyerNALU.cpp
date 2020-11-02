#include "EyerNALU.hpp"

namespace Eyer
{
    EyerNALU::EyerNALU()
    {

    }

    EyerNALU::~EyerNALU()
    {
        for(int i=0;i<fieldList.size();i++){
            delete fieldList[i];
        }
        fieldList.clear();
    }

    int EyerNALU::SetNALUData(EyerNALUData & _naluData)
    {
        naluData = _naluData;
        return 0;
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
            else{

            }
        }
        EyerLog("==============================================================\n");
        return 0;
    }
}