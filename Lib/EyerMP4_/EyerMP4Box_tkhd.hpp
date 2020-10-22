#ifndef EYERLIB_EYERMP4BOX_TKHD_HPP
#define EYERLIB_EYERMP4BOX_TKHD_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"


/************************************************************************************************************
**                                        tkhd: track header, track的总体信息, 如时长, 宽高等
**
-------------------------------------------------------------------------------------------------------------
**        字段名称            　　 |    长度(bytes)   |        有关描述
-------------------------------------------------------------------------------------------------------------
**        boxsize                |    4            |        box的长度
**        boxtype                |    4            |        box的类型
**        version                |    1            |        box版本，0或1，一般为0。（以下字节数均按version = 0）
**        flags                  |    3            |        按位或操作结果值，预定义如下;
                                                    　　　　 0x000001 track_enabled，否则该track不被播放；
                                                    　　　　 0x000002 track_in_movie，表示该track在播放中被引用；
                                                    　　　　 0x000004 track_in_preview，表示该track在预览时被引用。
                                                    　　　　 一般该值为7，如果一个媒体所有track均未设置track_in_movie和track_in_preview,将被理解为所有track均设置了这两项;
                                                    　　　　 对于hint track，该值为0;
**        creation_time          |    4            |        创建时间（相对于UTC时间1904 - 01 - 01零点的秒数）
**        modification_time      |    4            |        修改时间
**        track_id               |    4            |        id号 不能重复且不能为0
**        reserved               |    4            |        保留位
**        duration               |    4            |        track的时间长度
**        reserved               |    8            |        保留位
**        layer                  |    2            |        视频层，默认为0，值小的在上层
**        alternate_group        |    2            |        track分组信息，默认为0表示该track未与其他track有群组关系
**        volume                 |    2            |        [8.8] 格式，如果为音频track，1.0（0x0100）表示最大音量；否则为0
**        reserved               |    2            |        保留位
**        matrix                 |    36           |        视频变换矩阵
**        width                  |    4            |        宽
**        height                 |    4            |        高，均为[16.16] 格式值 与sample描述中的实际画面大小比值，用于播放时的展示宽高
if (version==1)
{
    unsigned int(64) creation_time;
    unsigned int(64) modification_time;
    unsigned int(32) track_ID;
    const unsigned int(32) reserved = 0;
    unsigned int(64) duration;
}
else
{
    unsigned int(32) creation_time;
    unsigned int(32) modification_time;
    unsigned int(32) track_ID;
    const unsigned int(32) reserved = 0;
    unsigned int(32) duration;
}
************************************************************************************************************/

namespace Eyer
{
    class EyerMP4Box_tkhd : public EyerMP4Box {
    public:
        EyerMP4Box_tkhd(const EyerBuffer & _buffer);
        ~EyerMP4Box_tkhd();

        virtual BoxType GetType();
        virtual int PrintInfo();
        virtual bool HasSub();

    private:
        int flags;
        int creation_time;
        int modification_time;
        int track_id;
        int duration;
        int layer;
        int alternate_group;
        float volume;
        float width;
        float height;
    };
}



#endif //EYERLIB_EYERMP4BOX_TKHD_HPP
