#ifndef EYERLIB_EYERSLICEBASE_H
#define EYERLIB_EYERSLICEBASE_H

#include "EyerNALU.hpp"
#include "EyerAVCCommon.hpp"
#include "EyerBitStream.hpp"
#include "EyerVUI.hpp"
#include "EyerField.hpp"
#include "EyerNAL.hpp"

namespace Eyer{
    class EyerSLICEBase : public EyerNAL {
    public:
        EyerSLICEBase(EyerNALU & _nalu);
        ~EyerSLICEBase();

        virtual NaluType GetNalType() = 0;

    public:
        int                 start_mb_nr;   //!< MUST be set by NAL even in case of ei_flag == 1
        int                 slice_type;    //!< slice type
        int                 pic_parameter_set_id;   //!<the ID of the picture parameter set the
    };
}



#endif //EYERLIB_EYERSLICEBASE_H
