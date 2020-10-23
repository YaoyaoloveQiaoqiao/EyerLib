#include "MP4BoxTKHD.hpp"

namespace Eyer {
    MP4BoxTKHD::MP4BoxTKHD()
    {

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

        return true;
    }

    EyerBuffer MP4BoxTKHD::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();

        if(version == 1){
            uint64_t creation_time_net          = htonll(creation_time);
            uint64_t modification_time_net      = htonll(modification_time);
            uint32_t track_ID_net               = htonl (track_ID);
            uint64_t duration_net               = htonll(duration);

            uint32_t reserved = 0;

            buffer.Append((unsigned char *)&creation_time_net,          sizeof(uint64_t));
            buffer.Append((unsigned char *)&modification_time_net,      sizeof(uint64_t));
            buffer.Append((unsigned char *)&track_ID_net,               sizeof(uint32_t));
            buffer.Append((unsigned char *)&reserved,                   sizeof(uint32_t));
            buffer.Append((unsigned char *)&duration_net,               sizeof(uint64_t));
        }
        else{
            uint32_t creation_time_net          = htonl ((uint32_t)creation_time);
            uint32_t modification_time_net      = htonl ((uint32_t)modification_time);
            uint32_t track_ID_net               = htonl ((uint32_t)track_ID);
            uint32_t duration_net               = htonl ((uint32_t)duration);

            uint32_t reserved = 0;

            buffer.Append((unsigned char *)&creation_time_net,          sizeof(uint32_t));
            buffer.Append((unsigned char *)&modification_time_net,      sizeof(uint32_t));
            buffer.Append((unsigned char *)&track_ID_net,               sizeof(uint32_t));
            buffer.Append((unsigned char *)&reserved,                   sizeof(uint32_t));
            buffer.Append((unsigned char *)&duration_net,               sizeof(uint32_t));
        }

        uint32_t reserved[2] = {0};
        buffer.Append((unsigned char *)&reserved, 2 * sizeof(uint32_t));

        uint16_t layer_net = htons ((uint16_t)layer);
        buffer.Append((unsigned char *)&layer_net, sizeof(uint16_t));

        uint16_t alternate_group_net = htons ((uint16_t)alternate_group);
        buffer.Append((unsigned char *)&alternate_group_net, sizeof(uint16_t));



        return buffer;
    }

    int MP4BoxTKHD::ParseParam(EyerBuffer & buffer, int offset)
    {
        offset = MP4FullBox::ParseParam(buffer, offset);

        unsigned char * data = (unsigned char *)malloc(buffer.GetLen());
        buffer.GetBuffer(data);

        if(version == 1){
            uint64_t creation_time_net;
            uint64_t modification_time_net;
            uint32_t timescale_net;
            uint64_t duration_net;

            memcpy(&creation_time_net,          data + offset, 8); offset += 8;
            memcpy(&modification_time_net,      data + offset, 8); offset += 8;
            memcpy(&timescale_net,              data + offset, 4); offset += 4;
            offset += 4;
            memcpy(&duration_net,               data + offset, 8); offset += 8;

            creation_time       = ntohll(creation_time_net);
            modification_time   = ntohll(modification_time_net);
            track_ID            = ntohl (timescale_net);
            duration            = ntohll(duration_net);
        }
        else{
            uint32_t creation_time_net;
            uint32_t modification_time_net;
            uint32_t timescale_net;
            uint32_t duration_net;

            memcpy(&creation_time_net,                   data + offset, 4); offset += 4;
            memcpy(&modification_time_net,               data + offset, 4); offset += 4;
            memcpy(&timescale_net,                       data + offset, 4); offset += 4;
            offset += 4;
            memcpy(&duration_net,                        data + offset, 4); offset += 4;

            creation_time       = ntohl(creation_time_net);
            modification_time   = ntohl(modification_time_net);
            track_ID            = ntohl(timescale_net);
            duration            = ntohl(duration_net);
        }

        offset += 2 * sizeof(uint32_t);

        uint16_t layer_net;
        memcpy(&layer_net, data + offset, sizeof(uint16_t)); offset += sizeof(uint16_t);
        layer = ntohs(layer_net);




        uint16_t alternate_group_net;
        memcpy(&alternate_group_net, data + offset, sizeof(uint16_t)); offset += sizeof(uint16_t);
        alternate_group = ntohs(alternate_group_net);



        volume = data[offset + 0] + data[offset + 1]; offset += 2;
        offset += sizeof(uint16_t);


        for(int i=0;i<9;i++){
            uint32_t m;
            memcpy(&m, data + offset + i * 4, 4);
            matrix[i] = ntohl(m);
        }
        offset += sizeof(uint32_t) * 9;


        width = (data[offset] << 8 | data[offset + 1]) + (data[offset + 2] << 8 | data[offset + 3]);
        offset += sizeof(uint32_t);
        height = (data[offset] << 8 | data[offset + 1]) + (data[offset + 2] << 8 | data[offset + 3]);

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

        printf("%swidth: %f\n", levelStr.str, width);
        printf("%sheight: %f\n", levelStr.str, height);

        return 0;
    }

    int MP4BoxTKHD::SetDefaultData()
    {
        type = BoxType::TKHD;

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

        version = 0;

        creation_time = 0;
        modification_time = 0;
        track_ID = 2;
        duration = 6666;

        layer = 10;
        alternate_group = 11;
        volume = 1.0f;

        width = 1920.0f;
        height = 1080.0f;

        return 0;
    }
}