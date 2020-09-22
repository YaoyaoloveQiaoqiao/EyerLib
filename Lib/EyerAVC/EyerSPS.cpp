#include "EyerSPS.hpp"
#include "EyerBitStream.hpp"
#include "EyerAVC_VLC.hpp"
#include "EyerCore/EyerLog.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace Eyer{
    EyerSPS::EyerSPS(EyerNALU & _nalu)
    {
        nalu = _nalu;

        nalu.ToSODB();

        EyerBitStream bitStream(nalu.buf + 1, nalu.len - 1);
        bitStream.code_len = nalu.len - 1;
        bitStream.bitstream_length = nalu.len - 1;
        bitStream.ei_flag = 0;
        bitStream.read_len = 0;
        bitStream.frame_bitoffset = 0;

        int usedBits = 0;
        profile_idc = EyerAVC_VLC::read_u_v(8, "SPS: profile_idc", &bitStream, &usedBits);

        if ((profile_idc != BASELINE       ) &&
            (profile_idc != MAIN           ) &&
            (profile_idc != EXTENDED       ) &&
            (profile_idc != FREXT_HP       ) &&
            (profile_idc != FREXT_Hi10P    ) &&
            (profile_idc != FREXT_Hi422    ) &&
            (profile_idc != FREXT_Hi444    ) &&
            (profile_idc != FREXT_CAVLC444 ))
        {
            EyerLog("Invalid Profile IDC (%d) encountered. \n", profile_idc);
            return;
        }

        int reserved_zero;

        constrained_set0_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set0_flag"                 , &bitStream, &usedBits);
        constrained_set1_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set1_flag"                 , &bitStream, &usedBits);
        constrained_set2_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set2_flag"                 , &bitStream, &usedBits);
        constrained_set3_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set3_flag"                 , &bitStream, &usedBits);
        constrained_set4_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set4_flag"                 , &bitStream, &usedBits);
        constrained_set5_flag                  = EyerAVC_VLC::read_u_1  (   "SPS: constrained_set5_flag"                 , &bitStream, &usedBits);

        reserved_zero                          = EyerAVC_VLC::read_u_v  (2, "SPS: reserved_zero_2bits"          , &bitStream, &usedBits);

        level_idc                              = EyerAVC_VLC::read_u_v  (8, "SPS: level_idc"                    , &bitStream, &usedBits);

        seq_parameter_set_id                   = EyerAVC_VLC::read_ue_v ("SPS: seq_parameter_set_id"                     , &bitStream, &usedBits);


        // Fidelity Range Extensions stuff
        chroma_format_idc = 1;

        if((profile_idc == FREXT_HP   ) ||
           (profile_idc == FREXT_Hi10P) ||
           (profile_idc == FREXT_Hi422) ||
           (profile_idc == FREXT_Hi444) ||
           (profile_idc == FREXT_CAVLC444))
        {
            chroma_format_idc                       = EyerAVC_VLC::read_ue_v ("SPS: chroma_format_idc"                       , &bitStream, &usedBits);
            if(chroma_format_idc == YUV444){

            }
        }

    }

    EyerSPS::~EyerSPS()
    {

    }

    int EyerSPS::PrintInfo()
    {
        char profile_idc_str[128];
        GetProfileIDC(profile_idc_str, profile_idc);
        EyerLog("profile_idc: %s\n", profile_idc_str);

        EyerLog("constrained_set0_flag: %d\n", constrained_set0_flag);
        EyerLog("constrained_set1_flag: %d\n", constrained_set1_flag);
        EyerLog("constrained_set2_flag: %d\n", constrained_set2_flag);
        EyerLog("constrained_set3_flag: %d\n", constrained_set3_flag);
        EyerLog("constrained_set4_flag: %d\n", constrained_set4_flag);
        EyerLog("constrained_set5_flag: %d\n", constrained_set5_flag);

        EyerLog("level_idc: %d\n", level_idc);

        EyerLog("seq_parameter_set_id: %d\n", seq_parameter_set_id);

        EyerLog("chroma_format_idc: %d\n", chroma_format_idc);

        return 0;
    }



    int EyerSPS::GetProfileIDC(char * str, unsigned int & profileIdc)
    {
        if(profileIdc == ProfileIDC::NO_PROFILE){
            memcpy(str, "NO_PROFILE", strlen("NO_PROFILE") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_CAVLC444){
            memcpy(str, "FREXT_CAVLC444", strlen("FREXT_CAVLC444") + 1);
        }
        if(profileIdc == ProfileIDC::BASELINE){
            memcpy(str, "BASELINE", strlen("BASELINE") + 1);
        }
        if(profileIdc == ProfileIDC::MAIN){
            memcpy(str, "MAIN", strlen("MAIN") + 1);
        }
        if(profileIdc == ProfileIDC::EXTENDED){
            memcpy(str, "EXTENDED", strlen("EXTENDED") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_HP){
            memcpy(str, "FREXT_HP", strlen("FREXT_HP") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_Hi10P){
            memcpy(str, "FREXT_Hi10P", strlen("FREXT_Hi10P") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_Hi422){
            memcpy(str, "FREXT_Hi422", strlen("FREXT_Hi422") + 1);
        }
        if(profileIdc == ProfileIDC::FREXT_Hi444){
            memcpy(str, "FREXT_Hi444", strlen("FREXT_Hi444") + 1);
        }
        return 0;
    }
}
