#ifndef EYERLIB_EYERMP4BOX_MDHD_HPP
#define EYERLIB_EYERMP4BOX_MDHD_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"


/************************************************************************************************************
**                                        mdhd: 包含了了该track的总体信息, mdhd和tkhd 内容大致都是一样的.
**
-------------------------------------------------------------------------------------------------------------
**        字段名称            　　|　　    长度(bytes)　　　|        有关描述
-------------------------------------------------------------------------------------------------------------
**        boxsize               |    4            　　  |        box的长度
**        boxtype               |    4            　　  |        box的类型
**        version               |    1　　　　　　　　　|        box版本0或1 一般为0 (以下字节数均按version=0)
**        flags                 |    3            　　  |
**        creation_time         |    4            　　  |        创建时间（相对于UTC时间1904 - 01 - 01零点的秒数）
**        modification_time     |    4            　　  |        修改时间
**        time_scale            |    4            　　  |
**        duration              |    4            　　　|        track的时间长度
**        language              |    2            　　　|        媒体语言码,最高位为0 后面15位为3个字符[见ISO 639-2/T标准中定义]
**        pre-defined           |    2            　　  |        保留位

** tkhd通常是对指定的track设定相关属性和内容, 而mdhd是针对于独立的media来设置的, 一般情况下二者相同.
************************************************************************************************************/

namespace Eyer
{
    class EyerMP4Box_mdhd : public EyerMP4Box {
    public:
        EyerMP4Box_mdhd(const EyerBuffer & _buffer);
        ~EyerMP4Box_mdhd();

        virtual BoxType GetType();
        virtual int PrintInfo();

        virtual bool HasSub();

    private:
        int creation_time;
        int modification_time;
        int timescale;
        int duration;
        short language;
    };
}

#endif //EYERLIB_EYERMP4BOX_MDHD_HPP
