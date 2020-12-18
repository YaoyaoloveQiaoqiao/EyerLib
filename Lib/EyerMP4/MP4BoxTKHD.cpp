#include "MP4BoxTKHD.hpp"
#include "MP4Stream.hpp"

namespace Eyer {
    MP4BoxTKHD::MP4BoxTKHD() : MP4FullBox()
    {
        type = BoxType::TKHD;
    }

    MP4BoxTKHD::~MP4BoxTKHD()
    {

    }

    bool MP4BoxTKHD::operator==(const MP4BoxTKHD &tkhd) const
    {
        if(!MP4FullBox::operator==(tkhd)){
            return false;
        }

        if(creation_time != tkhd.creation_time){
            return false;
        }
        if(modification_time != tkhd.modification_time){
            return false;
        }
        if(track_ID != tkhd.track_ID){
            return false;
        }
        if(duration != tkhd.duration){
            return false;
        }
        if(layer != tkhd.layer){
            return false;
        }
        if(alternate_group != tkhd.alternate_group){
            return false;
        }
        if(volume != tkhd.volume){
            return false;
        }
        if(width != tkhd.width){
            return false;
        }
        if(height != tkhd.height){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxTKHD::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();

        MP4Stream stream(buffer);

        if(version == 1){
            stream.WriteBigEndian((uint64_t)creation_time);
            stream.WriteBigEndian((uint64_t)modification_time);
            stream.WriteBigEndian((uint32_t)track_ID);
            stream.WriteZero(sizeof(uint32_t));
            stream.WriteBigEndian((uint64_t)duration);
        }
        else{
            stream.WriteBigEndian((uint32_t)creation_time);
            stream.WriteBigEndian((uint32_t)modification_time);
            stream.WriteBigEndian((uint32_t)track_ID);
            stream.WriteZero(sizeof(uint32_t));
            stream.WriteBigEndian((uint32_t)duration);
        }
        stream.WriteZero(sizeof(uint32_t) * 2);
        stream.WriteBigEndian((uint16_t)layer);
        stream.WriteBigEndian((uint16_t)alternate_group);
        stream.WriteBigEndianFixedPoint(volume, 8, 8);
        stream.WriteZero(sizeof(uint16_t));

        for(int i=0;i<9;i++) {
            stream.WriteBigEndianFixedPoint(matrix[i], 16, 16);
        }

        stream.WriteBigEndianFixedPoint(width * 1.0, 16, 16);
        stream.WriteBigEndianFixedPoint(height * 1.0, 16, 16);

        return stream.GetBuffer();
    }

    int MP4BoxTKHD::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        MP4Stream stream(buffer);
        stream.Skip(offset);

        if(version == 1){
            creation_time       = stream.ReadBigEndian_uint64(offset);
            modification_time   = stream.ReadBigEndian_uint64(offset);
            track_ID            = stream.ReadBigEndian_uint32(offset);
            stream.Skip(4);
            duration            = stream.ReadBigEndian_uint64(offset);
        }
        else{
            creation_time       = stream.ReadBigEndian_uint32(offset);
            modification_time   = stream.ReadBigEndian_uint32(offset);
            track_ID            = stream.ReadBigEndian_uint32(offset);
            stream.Skip(4);
            duration            = stream.ReadBigEndian_uint32(offset);
        }

        stream.Skip(sizeof(uint32_t) * 2);

        layer           = stream.ReadBigEndian_uint16(offset);
        alternate_group = stream.ReadBigEndian_uint16(offset);
        volume          = stream.ReadBigEndianFixedPoint(8, 8, offset);

        stream.Skip(sizeof(uint16_t) * 1);

        for(int i=0;i<9;i++) {
            matrix[i] = stream.ReadBigEndianFixedPoint(16, 16, offset);
        }

        width       = stream.ReadBigEndianFixedPoint(16, 16, offset);
        height      = stream.ReadBigEndianFixedPoint(16, 16, offset);

        return offset;
    }

    int MP4BoxTKHD::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        EyerLog("%screation_time: %lld\n", levelStr.str, creation_time);
        EyerLog("%smodification_time: %lld\n", levelStr.str, modification_time);
        EyerLog("%strack_ID: %d\n", levelStr.str, track_ID);
        EyerLog("%sduration: %lld\n", levelStr.str, duration);

        EyerLog("%slayer: %d\n", levelStr.str, layer);
        EyerLog("%salternate_group: %d\n", levelStr.str, alternate_group);

        EyerLog("%svolume: %f\n", levelStr.str, volume);

        EyerLog("%s[ %f, %f, %f\n", levelStr.str,  matrix[0], matrix[1], matrix[2]);
        EyerLog("%s  %f, %f, %f\n", levelStr.str,  matrix[3], matrix[4], matrix[5]);
        EyerLog("%s  %f, %f, %f ]\n",levelStr.str, matrix[6], matrix[7], matrix[8]);

        EyerLog("%swidth: %d\n", levelStr.str, width);
        EyerLog("%sheight: %d\n", levelStr.str, height);

        return 0;
    }

    int MP4BoxTKHD::SetDefaultData()
    {
        type = BoxType::TKHD;

        version = 0;

        creation_time = 123456;
        modification_time = 654321;
        track_ID = 2;
        duration = 6666;

        layer = 10;
        alternate_group = 11;
        volume = 1.0f;

        matrix[0] = 0.0f; matrix[1] = 1.0f; matrix[2] = 2.0f;
        matrix[3] = 3.0f; matrix[4] = 4.0f; matrix[5] = 5.0f;
        matrix[6] = 6.0f; matrix[7] = 7.0f; matrix[8] = 8.0f;

        width = 1920.0f;
        height = 1080.0f;

        size = Serialize().GetLen();

        return 0;
    }
}