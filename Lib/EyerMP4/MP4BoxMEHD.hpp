#ifndef EYERLIB_MP4BOXMEHD_HPP
#define EYERLIB_MP4BOXMEHD_HPP

#include "MP4Box.hpp"
#include "MP4FullBox.hpp"

namespace Eyer
{
    class MP4BoxMEHD : public MP4FullBox {
    public:
        MP4BoxMEHD();
        ~MP4BoxMEHD();

        bool operator == (const MP4BoxMEHD & mehd) const;

        virtual EyerBuffer SerializeParam();
        virtual int ParseParam(EyerBuffer & buffer, int offset);

        virtual int PrintInfo(int level = 0);

        int SetDefaultData();

    private:
        uint64_t fragment_duration = 0;
    };
}

#endif //EYERLIB_MP4BOXMEHD_HPP
