#include "EyerScene.hpp"

namespace Eyer
{
    EyerScene::EyerScene()
    {

    }

    EyerScene::~EyerScene()
    {
        for(int i=0;i<layerList.size();i++){
            delete layerList[i];
        }
        layerList.clear();
    }

    int EyerScene::AddLayer(EyerLayer & layer)
    {
        EyerLayer * tempLayer = new EyerLayer();
        *tempLayer = layer;

        layerList.push_back(tempLayer);

        return 0;
    }

    int EyerScene::AddSpirit(EyerSpirit * spirit)
    {
        spiritList.push_back(spirit);

        return 0;
    }

    int EyerScene::SetCamera(EyerCamera * _camera)
    {
        camera = _camera;
        return 0;
    }

    int EyerScene::Render(int frameIndex)
    {
        for(int i=0;i<layerList.size();i++){
            EyerLayer * tempLayer = layerList[i];
            tempLayer->Render(frameIndex);
        }

        EatrixF4x4 vp;
        camera->Render(vp, frameIndex);

        for(int i=0;i<spiritList.size();i++){
            EyerSpirit * tempSpirit = spiritList[i];
            tempSpirit->Render(camera->vp, frameIndex);
        }

        return 0;
    }
}