#include "EyerAdaptationSet.hpp"
#include <libxml2/libxml/parser.h>
#include "EyerCore/EyerCore.hpp"
#include "EyerRepresentation.hpp"

namespace Eyer
{
    EyerAdaptationSet::EyerAdaptationSet()
    {

    }

    EyerAdaptationSet::~EyerAdaptationSet()
    {
        for(int i=0;i<representationList.size();i++){
            delete representationList[i];
        }
        representationList.clear();
    }

    EyerAdaptationSet::EyerAdaptationSet(const EyerAdaptationSet & adaptationSet) : EyerAdaptationSet()
    {
        *this = adaptationSet;
    }

    EyerAdaptationSet & EyerAdaptationSet::operator = (const EyerAdaptationSet & adaptationSet)
    {
        segmentTemplate = adaptationSet.segmentTemplate;

        for(int i=0;i<representationList.size();i++){
            delete representationList[i];
        }
        representationList.clear();

        for(int i=0;i<adaptationSet.representationList.size();i++){
            EyerRepresentation * representation = new EyerRepresentation(*adaptationSet.representationList[i]);
            representationList.push_back(representation);
        }
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
                EyerRepresentation * representation = new EyerRepresentation();
                representation->LoadFromXML(representationNode);
                representationList.push_back(representation);
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

    int EyerAdaptationSet::GetRepresentationSize()
    {
        return representationList.size();
    }

    EyerRepresentation & EyerAdaptationSet::GetRepresentation(int i)
    {
        return *representationList[i];
    }
}