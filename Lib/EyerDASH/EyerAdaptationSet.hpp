#ifndef EYE_LIB_EYERADAPTATIONSET_HPP
#define EYE_LIB_EYERADAPTATIONSET_HPP

#include "EyerSegmentTemplate.hpp"

namespace Eyer{
    class EyerAdaptationSet {
    public:
        EyerAdaptationSet();
        ~EyerAdaptationSet();

        EyerAdaptationSet(const EyerAdaptationSet & adaptationSet);

        EyerAdaptationSet & operator = (const EyerAdaptationSet & adaptationSet);

        int LoadFromXML(void * node);


        EyerSegmentTemplate & GetSegmentTemplate();
        int SetSegmentTemplate(EyerSegmentTemplate & segmentTemplate);
    private:
        EyerSegmentTemplate segmentTemplate;
    };
}

#endif //EYE_LIB_EYERADAPTATIONSET_HPP
