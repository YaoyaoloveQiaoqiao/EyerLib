#ifndef EYE_LIB_EYERMPD_HPP
#define EYE_LIB_EYERMPD_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAdaptationSet.hpp"

namespace Eyer{
    class EyerMPD {
    public:
        EyerMPD();
        ~EyerMPD();

        int LoadMPD(EyerBuffer & buffer);


        int PrintInfo();
    private:
        EyerString baseUrl;
        std::vector<EyerAdaptationSet *> adaptationSetList;
    };
}

#endif //EYE_LIB_EYERMPD_HPP
