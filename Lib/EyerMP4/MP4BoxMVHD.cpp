#include "MP4BoxMVHD.hpp"
#include "EyerISOTypeReader.hpp"

namespace Eyer
{
    MP4BoxMVHD::MP4BoxMVHD() : MP4FullBox()
    {
        type = BoxType::MVHD;
    }

    MP4BoxMVHD::~MP4BoxMVHD()
    {

    }

    bool MP4BoxMVHD::operator == (const MP4BoxMVHD & mvhd) const
    {
        if(!MP4FullBox::operator==(mvhd)){
            return false;
        }

        if(creation_time != mvhd.creation_time){
            return false;
        }
        if(modification_time != mvhd.modification_time){
            return false;
        }
        if(timescale != mvhd.timescale){
            return false;
        }
        if(duration != mvhd.duration){
            return false;
        }

        return true;
    }

    EyerBuffer MP4BoxMVHD::SerializeParam()
    {
        EyerBuffer buffer = MP4FullBox::SerializeParam();

        if(version == 1){
            uint64_t creation_time_net          = htonll(creation_time);
            uint64_t modification_time_net      = htonll(modification_time);
            uint32_t timescale_net              = htonl (timescale);
            uint64_t duration_net               = htonll(duration);

            buffer.Append((unsigned char *)&creation_time_net,          sizeof(uint64_t));
            buffer.Append((unsigned char *)&modification_time_net,      sizeof(uint64_t));
            buffer.Append((unsigned char *)&timescale_net,              sizeof(uint32_t));
            buffer.Append((unsigned char *)&duration_net,               sizeof(uint64_t));
        }
        else{
            uint32_t creation_time_net          = htonl ((uint32_t)creation_time);
            uint32_t modification_time_net      = htonl ((uint32_t)modification_time);
            uint32_t timescale_net              = htonl ((uint32_t)timescale);
            uint32_t duration_net               = htonl ((uint32_t)duration);

            buffer.Append((unsigned char *)&creation_time_net,          sizeof(uint32_t));
            buffer.Append((unsigned char *)&modification_time_net,      sizeof(uint32_t));
            buffer.Append((unsigned char *)&timescale_net,              sizeof(uint32_t));
            buffer.Append((unsigned char *)&duration_net,               sizeof(uint32_t));
        }

        uint16_t rate_net[2] = {0};
        buffer.Append((unsigned char *)rate_net, 2 * sizeof(uint16_t));
        uint8_t volume_net[2] = {0};
        buffer.Append((unsigned char *)volume_net, 2 * sizeof(uint8_t));

        uint8_t reserved_net[10] = {0};
        buffer.Append(reserved_net, 10 * sizeof(uint8_t));

        for(int i=0;i<9;i++){
            uint32_t m = htonl(matrix[i]);
            buffer.Append((unsigned char *)&m, sizeof(uint32_t));
        }

        uint32_t pre_defined[6] = {0};
        buffer.Append((unsigned char *)pre_defined, 6 * sizeof(uint32_t));

        uint32_t next_track_ID_net = htonl(next_track_ID);
        buffer.Append((unsigned char *)&next_track_ID_net, sizeof(uint32_t));

        return buffer;
    }

    int MP4BoxMVHD::ParseParam(EyerBuffer & buffer, int offset)
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
            memcpy(&duration_net,               data + offset, 8); offset += 8;

            creation_time       = ntohll(creation_time_net);
            modification_time   = ntohll(modification_time_net);
            timescale           = ntohl (timescale_net);
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
            memcpy(&duration_net,                        data + offset, 4); offset += 4;

            creation_time       = ntohl(creation_time_net);
            modification_time   = ntohl(modification_time_net);
            timescale           = ntohl(timescale_net);
            duration            = ntohl(duration_net);
        }

        rate = EyerISOTypeReader::ReadFixedPoint1616(data); offset += 4;
        // rate        =  (data[offset + 0] << 8 | data[offset + 1]) + (data[offset + 2] << 8 | data[offset + 3]); offset += 4;
        volume      =  data[offset + 0] + data[offset + 1]; offset += 2;

        int MAX_MVHD_RESERVED_LEN = 2 * 4 + 2;
        offset += MAX_MVHD_RESERVED_LEN;

        for(int i=0;i<9;i++){
            uint32_t m;
            memcpy(&m, data + offset + i * 4, 4);
            matrix[i] = ntohl(m);
        }

        int MAX_MATRIX_LEN = 9 * 4;
        int MAX_PRE_DEFINE_LEN = 6 * 4;
        offset += MAX_PRE_DEFINE_LEN + MAX_MATRIX_LEN;

        uint32_t next_track_ID_net;
        memcpy(&next_track_ID_net,                   data + offset, 4); offset += 4;
        next_track_ID = ntohl(next_track_ID_net);

        free(data);

        return offset;
    }

    int MP4BoxMVHD::PrintInfo(int level)
    {
        MP4FullBox::PrintInfo(level);

        EyerString levelStr = "";
        for(int i=0;i<level;i++){
            levelStr = levelStr + "\t";
        }
        levelStr = levelStr + "\t";

        printf("%screation_time: %lld\n", levelStr.str, creation_time);
        printf("%smodification_time: %lld\n", levelStr.str, modification_time);
        printf("%stimescale: %d\n", levelStr.str, timescale);
        printf("%sduration: %lld\n", levelStr.str, duration);
        printf("%snext_track_ID: %d\n", levelStr.str, next_track_ID);

        return 0;
    }

    int MP4BoxMVHD::SetDefaultData()
    {
        version = 0;

        creation_time = 0;
        modification_time = 0;
        timescale = 1000;
        duration = 6666;

        rate = 1.4f;
        volume = 1.0f;

        next_track_ID = 5;

        type = BoxType::MVHD;
        if(version == 1){
            size = 8 + 8 + 8 + 4 + 8 + 4;
            size += 4 + 2 + 2 + 8 + 9 * 4 + 6 * 4 + 4;
            largesize = 0;
        }
        else{
            size = 8 + 4 + 4 + 4 + 4 + 4;
            size += 4 + 2 + 2 + 8 + 9 * 4 + 6 * 4 + 4;
            largesize = 0;
        }


        return 0;
    }
}