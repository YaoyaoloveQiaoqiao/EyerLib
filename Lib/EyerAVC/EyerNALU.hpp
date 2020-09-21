#ifndef EYERLIB_EYERNALU_HPP
#define EYERLIB_EYERNALU_HPP

#include <stdint.h>

namespace Eyer {
     enum NaluType {
        NALU_TYPE_SLICE    = 1,
        NALU_TYPE_DPA      = 2,
        NALU_TYPE_DPB      = 3,
        NALU_TYPE_DPC      = 4,
        NALU_TYPE_IDR      = 5,
        NALU_TYPE_SEI      = 6,
        NALU_TYPE_SPS      = 7,
        NALU_TYPE_PPS      = 8,
        NALU_TYPE_AUD      = 9,
        NALU_TYPE_EOSEQ    = 10,
        NALU_TYPE_EOSTREAM = 11,
        NALU_TYPE_FILL     = 12,
    };

    typedef enum {
        NALU_PRIORITY_HIGHEST     = 3,
        NALU_PRIORITY_HIGH        = 2,
        NALU_PRIORITY_LOW         = 1,
        NALU_PRIORITY_DISPOSABLE  = 0
    } NalRefIdc;

    class EyerNALU {
    public:
        EyerNALU(int buffersize = MAX_NALU_SIZE);
        ~EyerNALU();

        EyerNALU(const EyerNALU & _nalu);
        EyerNALU & operator = (const EyerNALU & _nalu);

        int ToRBSP();
        int ToSODB();

        const static int MAX_NALU_SIZE = 8 * 1024 * 1024;

    public:
        int       startcodeprefix_len;   //!< 4 for parameter sets and first slice in picture, 3 for everything else (suggested)
        unsigned  len;                   //!< Length of the NAL unit (Excluding the start code, which does not belong to the NALU)
        unsigned  max_size;              //!< NAL Unit Buffer size
        int       forbidden_bit;         //!< should be always FALSE
        NaluType  nal_unit_type;         //!< NALU_TYPE_xxxx
        NalRefIdc nal_reference_idc;     //!< NALU_PRIORITY_xxxx
        unsigned char * buf;                   //!< contains the first byte followed by the EBSP
        uint16_t  lost_packets;          //!< true, if packet loss is detected
    };
}

#endif //EYERLIB_EYERNALU_HPP
