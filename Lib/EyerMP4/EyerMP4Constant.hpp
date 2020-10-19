#ifndef EYERLIB_EYERMP4CONSTANT_HPP
#define EYERLIB_EYERMP4CONSTANT_HPP

#define BOX_TYPE_FTYPE "ftyp"
#define BOX_TYPE_MOOV "moov"
#define BOX_TYPE_MVHD "mvhd"
#define BOX_TYPE_TRAK "trak"
#define BOX_TYPE_TKHD "tkhd"
#define BOX_TYPE_EDTS "edts"
#define BOX_TYPE_MDIA "mdia"
#define BOX_TYPE_MDHD "mdhd"
#define BOX_TYPE_HDLR "hdlr"
#define BOX_TYPE_MINF "minf"
#define BOX_TYPE_VMHD "vmhd"
#define BOX_TYPE_DINF "dinf"
#define BOX_TYPE_DREF "dref"
#define BOX_TYPE_STBL "stbl"
#define BOX_TYPE_STSD "stsd"
#define BOX_TYPE_STTS "stts"
#define BOX_TYPE_STSS "stss"
#define BOX_TYPE_STSC "stsc"
#define BOX_TYPE_STSZ "stsz"
#define BOX_TYPE_STCO "stco"
#define BOX_TYPE_UDTA "udta"

#define BOX_TYPE_MVEX "mvex"
#define BOX_TYPE_TREX "trex"
#define BOX_TYPE_MEHD "mehd"

#define MAX_BOX_SIZE_LEN 4
#define MAX_BOX_TYPE_LEN 4
#define MAX_HANDLER_TYPE_LEN 4
#define MAX_FTYP_BRABDS_LEN 4
#define MAX_FTYP_BRABDS_NUM 4
#define MAX_STTS_ENTRY_NUM 8
#define MAX_STSS_ENTRY_NUM 8
#define MAX_STSC_ENTRY_NUM 100
#define MAX_STSZ_ENTRY_NUM 100
#define MAX_STCO_ENTRY_NUM 100
#define MAX_MVHD_RESERVED_LEN 10
#define MAX_PRE_DEFINE_LEN 24
#define MAX_MATRIX_LEN 36
#define MAX_HDLR_NAME_LEN 100

namespace Eyer
{
    enum BoxType
    {
        UNKNOW = 0,
        FTYP = 1,
        MOOV = 2,
        MVHD = 3,
        TRAK = 4,
        TKHD = 5,
        EDTS = 6,
        MDHD = 7,
        HDLR = 8,
        MDIA = 9,
        MINF = 10,
        STBL = 11,
        MVEX = 12,
        TREX = 13,
        MEHD = 14
    };
}

#endif //EYERLIB_EYERMP4CONSTANT_HPP
