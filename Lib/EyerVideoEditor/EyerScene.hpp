#ifndef	EYER_LIB_EYER_VIDEO_EDITOR_SCENE_H
#define	EYER_LIB_EYER_VIDEO_EDITOR_SCENE_H

#include "EyerLayer.hpp"
#include "EyerSpirit.hpp"
#include "EyerCamera.hpp"

#include <vector>

namespace Eyer
{
    class EyerScene
    {
    public:
        EyerScene();
        ~EyerScene();

        int AddLayer(EyerLayer & layer);

        int AddSpirit(EyerSpirit * spirit);

        int Render(int frameIndex);

        int SetCamera(EyerCamera * _camera);

    private:
        std::vector<EyerLayer *> layerList;
        std::vector<EyerSpirit *> spiritList;

        EyerCamera * camera = nullptr;
    };
}

#endif