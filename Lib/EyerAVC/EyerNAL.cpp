#include "EyerNAL.hpp"
#include "EyerCore/EyerCore.hpp"
#include "EyerField.hpp"
#include "EyerAVC_VLC.hpp"

namespace Eyer {
    EyerNAL::EyerNAL()
    {

    }

    EyerNAL::~EyerNAL()
    {

    }

    int EyerNAL::GetFieldSize()
    {
        return fieldList.size();
    }

    int EyerNAL::GetField(EyerField & field, int index)
    {
        EyerField * f = fieldList.at(index);
        field = *f;
        return 0;
    }

    int EyerNAL::PrintInfo()
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
            if(type == EyerFieldType::BOOL){
                EyerLog("%s%s = %d\n", levelStr.str, key.str, (int)field->GetBooleanVal());
            }
            else if(type == EyerFieldType::UNSIGNED_INT){
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

    /*
     * 0   1   2   3
     * 4   5   6   7
     * 8   9   10  11
     * 12  13  14  15
     */
    static const byte ZZ_SCAN[16]  =
    {
        0,  1,  4,  8,  5,  2,  3,  6,  9, 12, 13, 10,  7, 11, 14, 15
    };

    /*
     * 0   1   2   3   4   5   6   7
     * 8   9   10  11  12  13  14  15
     * 16  17  18  19  20  21  22  23
     * 24  25  26  27  28  29  30  31
     * 32  33  34  35  36  37  38  39
     * 40  41  42  43  44  45  46  47
     * 48  49  50  51  52  53  54  55
     * 56  57  58  59  60  61  62  63
     */
    static const byte ZZ_SCAN8[64] =
    {
        0,  1,  8, 16,  9,  2,  3, 10, 17, 24, 32, 25, 18, 11,  4,  5,
        12, 19, 26, 33, 40, 48, 41, 34, 27, 20, 13,  6,  7, 14, 21, 28,
        35, 42, 49, 56, 57, 50, 43, 36, 29, 22, 15, 23, 30, 37, 44, 51,
        58, 59, 52, 45, 38, 31, 39, 46, 53, 60, 61, 54, 47, 55, 62, 63
    };

    void EyerNAL::ScalingList(int * scalingList, int sizeOfScalingList, Boolean * useDefaultScalingMatrix, EyerBitStream * bitstream, int * used_bits)
    {
        int j, scanj;
        int delta_scale, lastScale, nextScale;

        lastScale      = 8;
        nextScale      = 8;

        for(j=0; j<sizeOfScalingList; j++) {
            scanj = (sizeOfScalingList==16) ? ZZ_SCAN[j]:ZZ_SCAN8[j];

            if(nextScale!=0) {
                delta_scale = EyerAVC_VLC::read_se_v ("   : delta_sl   "                           , bitstream, used_bits);
                nextScale = (lastScale + delta_scale + 256) % 256;
                *useDefaultScalingMatrix = (Boolean) (scanj==0 && nextScale==0);
            }

            scalingList[scanj] = (nextScale==0) ? lastScale:nextScale;
            lastScale = scalingList[scanj];
        }
    }
}