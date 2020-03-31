#ifndef	EYER_LIB_REDNER_CANVAS_AV_H
#define	EYER_LIB_REDNER_CANVAS_AV_H

#include "MBCore/MBCore.hpp"
#include "MBLine.hpp"
#include "MBVertex.hpp"

#include <vector>

namespace MB
{
    class MBCanvas;

    class MBCanvas
    {
    private:
        int width = 0;
        int height = 0;

        unsigned char * pixelData = nullptr;


        int FindYPoint(MBVec2 & p0, MBVec2 & p1, MBVec2 & p2, int x, int y,int & top, int & bottom);
    public:
        MBCanvas(int _width, int _height);
        ~MBCanvas();

        int DrawLine(MBVec2 p0, MBVec2 p1, unsigned char r, unsigned char g, unsigned char b);
        int DrawLine(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b);

        int DrawTriangle2(MBVec2 p0, MBVec2 p1, MBVec2 p2, unsigned char r = 255, unsigned char g = 0, unsigned char b = 0);
        int DrawTriangle(MBVec2 p0, MBVec2 p1, MBVec2 p2, unsigned char r = 255, unsigned char g = 0, unsigned char b = 0);
        int DrawTriangle(MBVertex & v0, MBVertex & v1, MBVertex & v2);
        int DrawTriangleNormail(MBVertex v0, MBVertex v1, MBVertex v2);


        int DrawLine2(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);

        int SetBufferPix(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
        
        int SetClearColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

        int RenderToTGA(MBString path);
    };


    class MBObjModel
    {
    private:
        MBString path;

        std::vector<MBVec3> verts_;
	    std::vector<std::vector<int> > faces_;
    public:
        MBObjModel(MBString _path);
        ~MBObjModel();

        int nverts();
        int nfaces();
        MBVec3 vert(int i);
        std::vector<int> face(int idx);
    };
}

#endif