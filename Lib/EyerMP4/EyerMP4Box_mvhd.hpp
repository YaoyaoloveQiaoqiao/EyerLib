#ifndef EYERLIB_EYERMP4BOX_MVHD_HPP
#define EYERLIB_EYERMP4BOX_MVHD_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"


/************************************************************************************************************
**                                            mvhd: movie header, 文件的总体信息: 时长, 创建时间等
**
--------------------------------------------------------------------------------------------
**        字段名称            　　|    长度(bytes)   |        有关描述
--------------------------------------------------------------------------------------------
**        boxsize               |    4            |        box的长度
**        boxtype               |    4            |        box的类型
**        version               |    1            |        box版本，0或1，一般为0（以下字节数均按version = 0）
**        flags                 |    3            |
**        creation time         |    4            |        创建时间（相对于UTC时间1904 - 01 - 01零点的秒数）
**        modification time     |    4            |        修改时间
**        time scale            |    4            |        文件媒体在1秒时间内的刻度值，可以理解为1秒长度的时间单元数
**        duration              |    4            |        该track的时间长度，用duration和time scale值可以计算track时长
**        rate                  |    4            |        推荐播放速率，高16位和低16位分别为小数点整数部分和小数部分，即[16.16] 格式.该值为1.0 (0x00010000)
**        volume                |    2            |        与rate类似，[8.8] 格式，1.0（0x0100）表示最大音量
**        reserved              |    10           |        保留位
**        matrix                |    36           |        视频变换矩阵
**        pre-defined           |    24           |
**        next track id         |    4            |        下一个track使用的id号
**
if (version==1)
{
    unsigned int(64) creation_time;
    unsigned int(64) modification_time;
    unsigned int(32) timescale;
    unsigned int(64) duration;
}
else
{
    unsigned int(32) creation_time;
    unsigned int(32) modification_time;
    unsigned int(32) timescale;
    unsigned int(32) duration;
}
************************************************************************************************************/

namespace Eyer
{
    class EyerMP4Box_mvhd : public EyerMP4Box {
    public:
        EyerMP4Box_mvhd(const EyerBuffer & _buffer);
        ~EyerMP4Box_mvhd();

        virtual BoxType GetType();
        virtual int PrintInfo();
        virtual bool HasSub();

    private:
        int creation_time;
        int modification_time;
        int timescale;
        int duration;
        float rate;
        float volume;
        int next_track_id;
    };
}

#endif //EYERLIB_EYERMP4BOX_MVHD_HPP
