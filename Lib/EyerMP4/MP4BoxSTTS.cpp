#include "MP4BoxSTTS.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxSTTS::MP4BoxSTTS() : MP4FullBox()
    {
        type = BoxType::STTS;
    }

    MP4BoxSTTS::~MP4BoxSTTS()
    {

    }

    bool MP4BoxSTTS::operator == (const MP4BoxSTTS & stts) const
    {
        if(!MP4FullBox::operator==(stts)){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxSTTS::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();

        MP4Stream stream(buffer);
        return stream.GetBuffer();
    }

    int MP4BoxSTTS::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        uint32_t entry_count = stream.ReadBigEndian_uint32(offset);
        printf("entry_count: %d\n", entry_count);

        return offset;
    }

    int MP4BoxSTTS::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        return 0;
    }

    int MP4BoxSTTS::SetDefaultData()
    {
        return 0;
    }
}