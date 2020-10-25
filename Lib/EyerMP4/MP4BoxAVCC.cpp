#include "MP4BoxAVCC.hpp"
#include "MP4Stream.hpp"


namespace Eyer
{
    MP4BoxAVCC::MP4BoxAVCC() : MP4Box()
    {
        type = BoxType::AVCC;
    }

    MP4BoxAVCC::~MP4BoxAVCC()
    {

    }

    bool MP4BoxAVCC::operator == (const MP4BoxAVCC & avcc) const
    {
        if(!MP4Box::operator==(avcc)){
            return false;
        }
        return true;
    }

    EyerBuffer MP4BoxAVCC::SerializeParam()
    {
        EyerBuffer buffer;
        MP4Stream stream(buffer);

        return stream.GetBuffer();
    }

    int MP4BoxAVCC::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4Box::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        configurationVersion    = stream.ReadBigEndian_uint8(offset);
        AVCProfileIndication    = stream.ReadBigEndian_uint8(offset);
        profile_compatibility   = stream.ReadBigEndian_uint8(offset);
        AVCLevelIndication      = stream.ReadBigEndian_uint8(offset);

        return offset;
    }

    int MP4BoxAVCC::PrintInfo(int level)
    {
        MP4Box::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%sconfigurationVersion: %d\n", levelStr.str, configurationVersion);
        printf("%sAVCProfileIndication: %d\n", levelStr.str, AVCProfileIndication);
        printf("%sprofile_compatibility: %d\n", levelStr.str, profile_compatibility);
        printf("%sAVCLevelIndication: %d\n", levelStr.str, AVCLevelIndication);
        
        return 0;
    }

    int MP4BoxAVCC::SetDefaultData()
    {
        return 0;
    }
}