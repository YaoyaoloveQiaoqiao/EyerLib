#ifndef EYERLIB_EYERMP4BOX_TREX_HPP
#define EYERLIB_EYERMP4BOX_TREX_HPP

#include "EyerMP4Box.hpp"
#include "EyerCore/EyerCore.hpp"

#include "EyerMP4Constant.hpp"

namespace Eyer
{
    class EyerMP4Box_trex : public EyerMP4Box {
    public:
        EyerMP4Box_trex();
        EyerMP4Box_trex(const EyerBuffer & _buffer);
        ~EyerMP4Box_trex();

        virtual BoxType GetType();
        virtual int PrintInfo();
        virtual bool HasSub();

    private:
        int track_id;

        int default_sample_description_index;
        int default_sample_duration;
        int default_sample_size;
        int default_sample_flags;
    };
}



#endif //EYERLIB_EYERMP4BOX_TREX_HPP
