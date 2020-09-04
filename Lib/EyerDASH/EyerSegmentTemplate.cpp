#include "EyerSegmentTemplate.hpp"
#include <libxml2/libxml/parser.h>
#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    EyerSegmentTemplate::EyerSegmentTemplate()
    {

    }

    EyerSegmentTemplate::~EyerSegmentTemplate()
    {

    }

    EyerSegmentTemplate::EyerSegmentTemplate(const EyerSegmentTemplate & segmentTemplate) : EyerSegmentTemplate()
    {
        *this = segmentTemplate;
    }

    EyerSegmentTemplate & EyerSegmentTemplate::operator = (const EyerSegmentTemplate & segmentTemplate)
    {
        initialization = segmentTemplate.initialization;
        return *this;
    }

    int EyerSegmentTemplate::LoadFromXML(void * node){
        xmlNode * segmentTemplateNode = (xmlNode *)node;
        SetInitialization((char *)xmlGetProp(segmentTemplateNode, BAD_CAST"initialization"));
        return 0;
    }

    int EyerSegmentTemplate::SetInitialization(char * str)
    {
        initialization = str;
        return 0;
    }

    EyerString & EyerSegmentTemplate::GetInitialization()
    {
        return initialization;
    }
}