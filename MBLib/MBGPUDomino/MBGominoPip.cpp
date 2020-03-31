#include "MBGPUDomino.hpp"
#include "MBGL/MBGL.hpp"

namespace MB
{
    MBGominoPip::MBGominoPip()
    {

    }

    MBGominoPip::~MBGominoPip()
    {
        ClearAll();
    }

    int MBGominoPip::operator << (MBGomino * gomino)
    {
        gomineList.insertBack(gomino);
        return 0;
    }

    int MBGominoPip::PrintStruct()
    {
        for(int i=0;i<gomineList.getLength();i++){
            MBGomino * g = nullptr;
            gomineList.find(i, g);

            printf("=============================\n");
            printf("Gomino Layer Index: %d\n", i);
            printf("Gomino Layer name: %s\n", g->name.str);
        }

        return 0;
    }

    int MBGominoPip::Go(MBGLTexture * input, MBGLTexture * output, int width, int height)
    {
        MBLinkedList<MBGLTexture *> tList;
        MBGLTexture * iT = input;
        MBGLTexture * oT = nullptr;
        for(int i=0;i<gomineList.getLength();i++){
            MBGomino * g = nullptr;
            gomineList.find(i, g);

            if(i == gomineList.getLength() - 1){
                oT = output;
            }
            else{
                oT = new MBGLTexture();
                tList.insertBack(oT);
            }

            // Render
            g->Go(iT, oT, width, height);

            iT = oT;
        }


        for(int i=0;i<tList.getLength();i++){
            MBGLTexture * t = nullptr;
            tList.find(i, t);
            if(t != nullptr){
                delete t;
            }
        }
        tList.clear();

        return 0;
    }

    int MBGominoPip::ClearAll()
    {
        /*
        for(int i=0;i<gomineList.getLength();i++){
            MBGomino * g = nullptr;
            gomineList.find(i, g);
            if(g != nullptr){
                delete g;
            }
        }
        */
        gomineList.clear();
        return 0;
    }
}