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
            stream.WriteBigEndian(creation_time);
            stream.WriteBigEndian(modification_time);
            stream.WriteBigEndian(track_ID);
            stream.WriteZero(4);
            stream.WriteBigEndian(duration);
        }
        else{
            stream.WriteBigEndian((uint32_t)creation_time);
            stream.WriteBigEndian((uint32_t)modification_time);
            stream.WriteBigEndian((uint32_t)track_ID);
            stream.WriteZero(4);
            stream.WriteBigEndian((uint32_t)duration);
        }
        stream.WriteZero(4);
        stream.WriteBigEndian(layer);
        stream.WriteBigEndian(alternate_group);
        stream.WriteBigEndianFixedPoint(volume, 8, 8);

        for(int i=0;i<9;i++) {
            stream.WriteBigEndianFixedPoint(matrix[i], 16, 16);
        }

        stream.WriteBigEndian(width);
        stream.WriteBigEndian(height);

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

        stream.Skip(4);

        layer           = stream.ReadBigEndian_uint16(offset);
        alternate_group = stream.ReadBigEndian_uint16(offset);
        volume          = stream.ReadBigEndianFixedPoint(8, 8, offset);

        for(int i=0;i<9;i++) {
            matrix[i] = stream.ReadBigEndianFixedPoint(16, 16, offset);
        }

        width = stream.ReadBigEndian_uint32(offset);
        height = stream.ReadBigEndian_uint32(offset);

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

        printf("%screation_time: %lld\n", levelStr.str, creation_time);
        printf("%smodification_time: %lld\n", levelStr.str, modification_time);
        printf("%strack_ID: %d\n", levelStr.str, track_ID);
        printf("%sduration: %lld\n", levelStr.str, duration);

        printf("%slayer: %d\n", levelStr.str, layer);
        printf("%salternate_group: %d\n", levelStr.str, alternate_group);

        printf("%svolume: %f\n", levelStr.str, volume);

        printf("%s[ %f, %f, %f\n", levelStr.str,  matrix[0], matrix[1], matrix[2]);
        printf("%s  %f, %f, %f\n", levelStr.str,  matrix[3], matrix[4], matrix[5]);
        printf("%s  %f, %f, %f ]\n",levelStr.str, matrix[6], matrix[7], matrix[8]);

        printf("%swidth: %d\n", levelStr.str, width);
        printf("%sheight: %d\n", levelStr.str, height);

        return 0;
    }

    int MP4BoxTKHD::SetDefaultData()
    {
        type = BoxType::TKHD;

        version = 0;

        if(version == 1){
            size = 8 + 4;
            size += 8 + 8 + 4 + 4 + 8;
            size += 4 * 2 + 2 * 4 + 4 * 9 + 4 + 4;
        }
        else{
            size = 8 + 4;
            size += 4 + 4 + 4 + 4 + 4;
            size += 4 * 2 + 2 * 4 + 4 * 9 + 4 + 4;
        }

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

        return 0;
    }
}