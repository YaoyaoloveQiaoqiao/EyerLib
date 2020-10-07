#include "EyerSLICEBase.hpp"
#include "EyerAVC_VLC.hpp"

namespace Eyer
{
    EyerSLICEBase::EyerSLICEBase(EyerNALU & _nalu) : EyerNAL()
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

        start_mb_nr = EyerAVC_VLC::read_ue_v ("SH: first_mb_in_slice", &bitStream, &usedBits);
        fieldList.push_back(new EyerField("start_mb_nr", start_mb_nr));

        int tmp = EyerAVC_VLC::read_ue_v ("SH: slice_type", &bitStream, &usedBits);
        if (tmp > 4) {
            tmp -= 5;
        }

        slice_type = (SliceType) tmp;
        EyerString slice_type_str = EyerENUMUtil::GetSliceTypeStr((SliceType)slice_type);
        fieldList.push_back(new EyerField("slice_type", slice_type, slice_type_str));

        pic_parameter_set_id = EyerAVC_VLC::read_ue_v ("SH: pic_parameter_set_id", &bitStream, &usedBits);
        fieldList.push_back(new EyerField("pic_parameter_set_id", pic_parameter_set_id));
    }
    EyerSLICEBase::~EyerSLICEBase()
    {

    }
}