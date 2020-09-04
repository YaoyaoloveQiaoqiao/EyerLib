#include "EyerAdaptationSet.hpp"
#include <libxml2/libxml/parser.h>
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerAdaptationSet::EyerAdaptationSet()
    {

    }

    EyerAdaptationSet::~EyerAdaptationSet()
    {

    }

    EyerAdaptationSet::EyerAdaptationSet(const EyerAdaptationSet & adaptationSet) : EyerAdaptationSet()
    {
        *this = adaptationSet;
    }

    EyerAdaptationSet & EyerAdaptationSet::operator = (const EyerAdaptationSet & adaptationSet)
    {
        segmentTemplate = adaptationSet.segmentTemplate;
        return *this;
    }

    int EyerAdaptationSet::LoadFromXML(void * node)
    {
        xmlNode * adaptationSetNode = (xmlNode *)node;

        xmlNode * representationNode = nullptr;
        for(representationNode = adaptationSetNode->children; representationNode; representationNode = representationNode->next) {
            if (xmlStrcasecmp(representationNode->name, BAD_CAST "SegmentTemplate") == 0){
                segmentTemplate.LoadFromXML(representationNode);
            }
            if (xmlStrcasecmp(representationNode->name, BAD_CAST "Representation") == 0){
            }
        }

        return 0;
    }

    EyerSegmentTemplate & EyerAdaptationSet::GetSegmentTemplate()
    {
        return segmentTemplate;
    }
    int EyerAdaptationSet::SetSegmentTemplate(EyerSegmentTemplate & _segmentTemplate)
    {
        segmentTemplate = _segmentTemplate;
        return 0;
    }
}