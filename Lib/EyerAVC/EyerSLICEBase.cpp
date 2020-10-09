#include "EyerSLICEBase.hpp"
#include "EyerAVC_VLC.hpp"

namespace Eyer
{
    EyerSLICEBase::EyerSLICEBase(EyerNALU & _nalu, EyerSPS & _sps, EyerPPS & _pps) : EyerNAL()
    {
        sps = _sps;
        pps = _pps;

        nalu = _nalu;

        nalu.ToSODB();

        idr_flag = (nalu.nal_unit_type == NALU_TYPE_IDR);
        nal_reference_idc = nalu.nal_reference_idc;

        EyerBitStream bitStream(nalu.buf + 1, nalu.len - 1);
        bitStream.code_len = nalu.len - 1;
        bitStream.bitstream_length = nalu.len - 1;
        bitStream.ei_flag = 0;
        bitStream.read_len = 0;
        bitStream.frame_bitoffset = 0;

        int usedBits = 0;

        first_mb_in_slice = EyerAVC_VLC::read_ue_v ("SH: first_mb_in_slice", &bitStream, &usedBits);
        fieldList.push_back(new EyerField("first_mb_in_slice", first_mb_in_slice));

        int tmp = EyerAVC_VLC::read_ue_v ("SH: slice_type", &bitStream, &usedBits);
        if (tmp > 4) {
            tmp -= 5;
        }

        slice_type = (SliceType) tmp;
        EyerString slice_type_str = EyerENUMUtil::GetSliceTypeStr((SliceType)slice_type);
        fieldList.push_back(new EyerField("slice_type", slice_type, slice_type_str));

        pic_parameter_set_id = EyerAVC_VLC::read_ue_v ("SH: pic_parameter_set_id", &bitStream, &usedBits);
        fieldList.push_back(new EyerField("pic_parameter_set_id", pic_parameter_set_id));

        int separate_colour_plane_flag = 0;
        if(separate_colour_plane_flag){
            colour_plane_id = EyerAVC_VLC::read_u_v (2, "SH: colour_plane_id", &bitStream, &usedBits);
        }
        else {
            colour_plane_id = PLANE_Y;
        }

        int log2_max_frame_num_minus4 = 0;
        frame_num = EyerAVC_VLC::read_u_v (log2_max_frame_num_minus4 + 4, "SH: frame_num", &bitStream, &usedBits);
        fieldList.push_back(new EyerField("frame_num", frame_num));


        int frame_mbs_only_flag = 1;
        if (frame_mbs_only_flag){

        }
        else{
            field_pic_flag = EyerAVC_VLC::read_u_1("SH: field_pic_flag", &bitStream, &usedBits);
            if (field_pic_flag){
                // bottom_field_flag  u(1)
                bottom_field_flag = (byte) EyerAVC_VLC::read_u_1("SH: bottom_field_flag", &bitStream, &usedBits);
            }
            else {
                bottom_field_flag = FALSE;
            }
        }

        if (idr_flag) {
            idr_pic_id = EyerAVC_VLC::read_ue_v("SH: idr_pic_id", &bitStream, &usedBits);
            fieldList.push_back(new EyerField("idr_pic_id", idr_pic_id));
        }

    }
    EyerSLICEBase::~EyerSLICEBase()
    {

    }
}