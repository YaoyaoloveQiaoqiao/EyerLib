#include "MBGPUDomino.hpp"

namespace MB {
    MBCommonParams::MBCommonParams() {

    }

    MBCommonParams::~MBCommonParams() {

    }

    MBCommonParams::MBCommonParams(const MBCommonParams &params) {
        *this = params;
    }

    MBCommonParams &MBCommonParams::operator=(const MBCommonParams &params) {
        return *this;
    }

    int MBCommonParams::PutFloat(MBString key, float val)
    {
        // param.insert(std::pair<MBString, float>(key, val));
        return 0;
    }
}