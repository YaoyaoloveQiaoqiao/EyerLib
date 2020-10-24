#include "MP4BoxFTYP.hpp"
#include "MP4Stream.hpp"

namespace Eyer
{
    MP4BoxFTYP::MP4BoxFTYP() : MP4Box()
    {
        type = BoxType::FTYP;
    }

    MP4BoxFTYP::~MP4BoxFTYP()
    {

    }

    bool MP4BoxFTYP::operator == (const MP4BoxFTYP & ftyp) const
    {
        if(!MP4Box::operator==(ftyp)){
            return false;
        }

        for(int i=0;i<4;i++){
            if(major_brand[i] != ftyp.major_brand[i]) {
                return false;
            }
        }

        if(minor_version != ftyp.minor_version) {
            return false;
        }

        if(compatible_brands_len != ftyp.compatible_brands_len) {
            return false;
        }

        for(int i=0;i<compatible_brands_len;i++){
            if(compatible_brands[i][0] != ftyp.compatible_brands[i][0]){
                return false;
            }
            if(compatible_brands[i][1] != ftyp.compatible_brands[i][1]){
                return false;
            }
            if(compatible_brands[i][2] != ftyp.compatible_brands[i][2]){
                return false;
            }
            if(compatible_brands[i][3] != ftyp.compatible_brands[i][3]){
                return false;
            }
        }

        return true;
    }

    EyerBuffer MP4BoxFTYP::SerializeParam()
    {
        EyerBuffer buffer;

        buffer.Append(major_brand, 4);

        uint32_t net_minor_version = htonl(minor_version);
        buffer.Append((unsigned char *)(&net_minor_version), 4);

        for(int i=0;i<compatible_brands_len;i++){
            buffer.Append(compatible_brands[i], 4);
        }

        return buffer;
    }

    int MP4BoxFTYP::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4Box::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        major_brand[0] = stream.ReadBigEndian_uint8(offset);
        major_brand[1] = stream.ReadBigEndian_uint8(offset);
        major_brand[2] = stream.ReadBigEndian_uint8(offset);
        major_brand[3] = stream.ReadBigEndian_uint8(offset);

        minor_version = stream.ReadBigEndian_int32(offset);

        compatible_brands_len = stream.GetBuffer().GetLen();

        for(int i=0;i<compatible_brands_len;i++){
            compatible_brands[i][0] = stream.ReadBigEndian_uint8(offset);
            compatible_brands[i][1] = stream.ReadBigEndian_uint8(offset);
            compatible_brands[i][2] = stream.ReadBigEndian_uint8(offset);
            compatible_brands[i][3] = stream.ReadBigEndian_uint8(offset);
        }

        return offset;
    }

    int MP4BoxFTYP::PrintInfo(int level)
    {
        MP4Box::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%smajor_brand: %c%c%c%c\n", levelStr.str, major_brand[0], major_brand[1], major_brand[2], major_brand[3]);
        printf("%sminor_version: %d\n", levelStr.str, minor_version);

        for(int i=0;i<compatible_brands_len;i++){
            printf("%s%c%c%c%c\n", levelStr.str, compatible_brands[i][0], compatible_brands[i][1], compatible_brands[i][2],compatible_brands[i][3]);
        }

        return 0;
    }

    int MP4BoxFTYP::SetDefaultData()
    {
        uint8_t net_major_brand[5] = "isom";
        memcpy(major_brand, net_major_brand, 4);

        minor_version = 512;

        compatible_brands_len = 4;
        memcpy(compatible_brands[0], "isom", 4);
        memcpy(compatible_brands[1], "iso2", 4);
        memcpy(compatible_brands[2], "avc1", 4);
        memcpy(compatible_brands[3], "mp41", 4);

        type = BoxType::FTYP;
        size = 8 + 4 + 4 + 4 * 4;
        largesize = 0;

        return 0;
    }
}