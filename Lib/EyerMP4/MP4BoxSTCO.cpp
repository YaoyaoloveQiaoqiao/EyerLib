#include "MP4BoxSTCO.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxSTCO::MP4BoxSTCO() : MP4FullBox()
    {

    }

    MP4BoxSTCO::~MP4BoxSTCO()
    {

    }

    bool MP4BoxSTCO::operator == (const MP4BoxSTCO & stco) const
    {
        if(!MP4FullBox::operator==(stco)){
            return false;
        }
        return true;
    }

    EyerBuffer MP4BoxSTCO::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();
        MP4Stream stream(buffer);

        return stream.GetBuffer();
    }

    int MP4BoxSTCO::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        

        return offset;
    }

    int MP4BoxSTCO::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";



        return 0;
    }

    int MP4BoxSTCO::SetDefaultData()
    {
        return 0;
    }
}