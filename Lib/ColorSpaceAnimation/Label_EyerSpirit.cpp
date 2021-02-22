#include "Label_EyerSpirit.hpp"
#include "image_r.hpp"

namespace Eyer
{
    Label_EyerSpirit::Label_EyerSpirit(unsigned char * data, int len)
    {
        imageBuffer.Append(data, len);
    }

    int Label_EyerSpirit::RenderInit()
    {
        plane = new MVPImagePlane(imageBuffer.GetPtr(), imageBuffer.GetLen());
        return 0;
    }

    int Label_EyerSpirit::RenderDestory()
    {
        if(plane != nullptr){
            delete plane;
            plane = nullptr;
        }
        return 0;
    }

    int Label_EyerSpirit::RenderContent(EatrixF4x4 & vp, EyerKey & key)
    {
        plane->SetVP(vp);
        plane->SetModel(key.position, key.rotato, key.scale);
        plane->Draw();
        return 0;
    }


}