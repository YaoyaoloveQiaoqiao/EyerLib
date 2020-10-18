#ifndef EYERLIB_EYERMP4BOX_FTYP_HPP
#define EYERLIB_EYERMP4BOX_FTYP_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"


/********************************************************************************************
**                            File Type Box (ftyp): file type, 表明文件类型
**
--------------------------------------------------------------------------------------------
**        字段名称            　　|    长度(bytes)   |        有关描述
--------------------------------------------------------------------------------------------
**        boxsize               |    4            |        box的长度
**        boxtype               |    4            |        box的类型
**        major_brand           |    4            |
**        minor_version         |    4            |        版本号
**        compatible_brands     |    4 * N        |        本文件遵从的多种协议(ismo, iso2, mp41)
********************************************************************************************/


namespace Eyer
{
    typedef struct t_box4ftyp_brand
    {
        unsigned char brands[MAX_FTYP_BRABDS_LEN+1];
    } T_BOX4FTYP_BRAN;

    class EyerMP4Box_ftyp : public EyerMP4Box {
    public:
        EyerMP4Box_ftyp(const EyerBuffer & _buffer);
        ~EyerMP4Box_ftyp();

        virtual bool HasSub();
        virtual BoxType GetType();
        virtual int PrintInfo();

    private:
        unsigned char major_brand[MAX_FTYP_BRABDS_LEN + 1];
        int minor_version;

        int brandsNum = 0;
        T_BOX4FTYP_BRAN compatible_brands[MAX_FTYP_BRABDS_NUM];
    };
}

#endif //EYERLIB_EYERMP4BOX_FTYP_HPP
