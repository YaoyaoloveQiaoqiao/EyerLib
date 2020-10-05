#ifndef EYERLIB_EYERIDR_HPP
#define EYERLIB_EYERIDR_HPP

#include "EyerNAL.hpp"

namespace Eyer
{
    class EyerIDR : public EyerNAL
    {
    public:
        EyerIDR(EyerNALU & _nalu);
        ~EyerIDR();

        virtual NaluType GetNalType();

    private:
        int                 start_mb_nr;   //!< MUST be set by NAL even in case of ei_flag == 1
        int                 slice_type;    //!< slice type
        int                 pic_parameter_set_id;   //!<the ID of the picture parameter set the
    };
}

#endif //EYERLIB_EYERIDR_HPP
