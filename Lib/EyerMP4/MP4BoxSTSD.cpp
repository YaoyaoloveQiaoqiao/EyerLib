#include "MP4BoxSTSD.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxSTSD::MP4BoxSTSD() : MP4FullBox()
    {

    }

    MP4BoxSTSD::~MP4BoxSTSD()
    {

    }

    bool MP4BoxSTSD::operator == (const MP4BoxSTSD & stsd) const
    {
        if(!MP4FullBox::operator==(stsd)){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxSTSD::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        return stream.GetBuffer();
    }

    int MP4BoxSTSD::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        uint32_t entry_count = stream.ReadBigEndian_uint32(offset);
        for(int i=0;i<entry_count;i++){
            uint32_t size = stream.ReadBigEndian_uint32(offset);
            uint8_t a = stream.ReadBigEndian_uint8(offset);
            uint8_t b = stream.ReadBigEndian_uint8(offset);
            uint8_t c = stream.ReadBigEndian_uint8(offset);
            uint8_t d = stream.ReadBigEndian_uint8(offset);

            printf("%d  %c%c%c%c\n", size, a, b, c, d);

            for(int w=0;w<8 + 4 + 4 + 4;w++){
                uint8_t a = stream.ReadBigEndian_uint8(offset);
                printf("a:%d\n", a);
            }



        }

        return offset;
    }

    int MP4BoxSTSD::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        return 0;
    }

    int MP4BoxSTSD::SetDefaultData()
    {
        return 0;
    }
}