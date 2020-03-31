#include "MBCanvas.hpp"

#include "MBCore/MBCore.hpp"
#include "MBTGA.hpp"

namespace MB
{
    MBCanvas::MBCanvas(int _width, int _height)
    {
        width = _width;
        height = _height;

        pixelData = (unsigned char *)malloc(width * height * 4 * sizeof(unsigned char));
        for(int h=0;h<height;h++){
            for(int w=0;w<width;w++){
                pixelData[(h * width + w) * 4 + 0] = 255; // R
                pixelData[(h * width + w) * 4 + 1] = 255; // G
                pixelData[(h * width + w) * 4 + 2] = 255; // B
                pixelData[(h * width + w) * 4 + 3] = 255; // A
            }
        }
    }

    MBCanvas::~MBCanvas()
    {
        if(pixelData != nullptr){
            free(pixelData);
            pixelData = nullptr;
        }
    }


    int MBCanvas::DrawTriangleNormail(MBVertex v0, MBVertex v1, MBVertex v2)
    {
        MBVec2 p0((v0.GetPosX() + 1.0f) / 2.0 * width, (v0.GetPosY() + 1.0f) / 2.0 * height);
        MBVec2 p1((v1.GetPosX() + 1.0f) / 2.0 * width, (v1.GetPosY() + 1.0f) / 2.0 * height);
        MBVec2 p2((v2.GetPosX() + 1.0f) / 2.0 * width, (v2.GetPosY() + 1.0f) / 2.0 * height);

        if (p0.y() == p1.y() && p0.y() == p2.y()) return -1;
        if (p0.y()>p1.y()) std::swap(p0, p1); 
        if (p0.y()>p2.y()) std::swap(p0, p2); 
        if (p1.y()>p2.y()) std::swap(p1, p2); 
        int total_height = p2.y()-p0.y(); 
        for (int i=0; i<total_height; i++) { 
            bool second_half = i>p1.y()-p0.y() || p1.y() == p0.y(); 
            int segment_height = second_half ? p2.y()-p1.y() : p1.y()-p0.y(); 
            float alpha = (float)i/total_height; 
            float beta  = (float)(i-(second_half ? p1.y()-p0.y() : 0)) / segment_height; // be careful: with above conditions no division by zero here 
            MBVec2 A =               p0 + (p2 - p0) * alpha; 
            MBVec2 B = second_half ? p1 + (p2 - p1) * beta : p0 + (p1 - p0) * beta;

            if (A.x()>B.x()){
                std::swap(A, B);
            }
            for (int j=A.x(); j<=B.x(); j++) {
                // image.set(j, t0.y+i, color); // attention, due to int casts t0.y+i != A.y 

                
                SetBufferPix(j, p0.y() + i, 255, 0, 0);
            } 
        }
        return 0;
    }



    int MBCanvas::FindYPoint(MBVec2 & p0, MBVec2 & p1, MBVec2 & p2,int x, int y, int & top, int & bottom)
    {
        
        return 0;
    }

    int MBCanvas::DrawTriangle(MBVec2 p0, MBVec2 p1, MBVec2 p2, unsigned char r, unsigned char g, unsigned char b)
    {
        if (p0.y() == p1.y() && p0.y() == p2.y()) return -1;
        if (p0.y()>p1.y()) std::swap(p0, p1); 
        if (p0.y()>p2.y()) std::swap(p0, p2); 
        if (p1.y()>p2.y()) std::swap(p1, p2); 
        int total_height = p2.y()-p0.y(); 
        for (int i=0; i<total_height; i++) { 
            bool second_half = i>p1.y()-p0.y() || p1.y()==p0.y(); 
            int segment_height = second_half ? p2.y()-p1.y() : p1.y()-p0.y(); 
            float alpha = (float)i/total_height; 
            float beta  = (float)(i-(second_half ? p1.y()-p0.y() : 0)) / segment_height; // be careful: with above conditions no division by zero here 
            MBVec2 A =               p0 + (p2-p0)*alpha; 
            MBVec2 B = second_half ? p1 + (p2-p1)*beta : p0 + (p1-p0)*beta; 
            if (A.x()>B.x()) std::swap(A, B); 
            for (int j=A.x(); j<=B.x(); j++) { 
                // image.set(j, t0.y+i, color); // attention, due to int casts t0.y+i != A.y 
                SetBufferPix(j, p0.y() + i, r, g, b);
            } 
        }
        return 0;
    }


    int MBCanvas::DrawTriangle(MBVertex & v0, MBVertex & v1, MBVertex & v2)
    {
        DrawTriangleNormail(v0, v1, v2);

        return 0;
    }


    int MBCanvas::DrawTriangle2(MBVec2 p0, MBVec2 p1, MBVec2 p2, unsigned char r, unsigned char g, unsigned char b)
    {
        if (p0.y()>p1.y()) std::swap(p0, p1); 
        if (p0.y()>p2.y()) std::swap(p0, p2); 
        if (p1.y()>p2.y()) std::swap(p1, p2); 

        int total_height = p2.y() - p0.y(); 
        if(total_height <= 0){
            return -1;
        }
        for (int y=p0.y(); y<=p1.y(); y++) { 
            int segment_height = p1.y() - p0.y() + 1; 
            float alpha = (float)(y - p0.y()) / total_height; 
            float beta  = (float)(y - p0.y()) / segment_height; // be careful with divisions by zero 
            MBVec2 A = p0 + (p2 - p0) * alpha; 
            MBVec2 B = p0 + (p1 - p0) * beta;

            // printf("A-x:%f, A-y:%f\n", A.x(), A.y());

            if (A.x() > B.x()) std::swap(A, B); 
            for (int j=A.x(); j<=B.x(); j++) {
                // printf("======A-x:%d, A-y:%d\n", j, y);
                SetBufferPix(j, y, r, g, b);
            }

            // image.set(A.x, y, red); 
            // image.set(B.x, y, green); 
        } 

        for (int y=p1.y(); y<=p2.y(); y++) { 
            int segment_height = p2.y() - p1.y() + 1; 
            float alpha = (float)(y - p0.y()) / total_height; 
            float beta  = (float)(y - p1.y()) / segment_height; // be careful with divisions by zero 
            MBVec2 A = p0 + (p2-p0) * alpha; 
            MBVec2 B = p1 + (p2-p1) * beta; 
            if (A.x() > B.x()) std::swap(A, B); 
            for (int j=A.x(); j<=B.x(); j++) { 
                SetBufferPix(j, y, r, g, b);
            } 
        } 

        // DrawLine(p0, p1, 0, 255, 0);
        // DrawLine(p1, p2, 0, 255, 0);
        // DrawLine(p2, p0, 255, 0, 0);

        return 0;
    }

    int MBCanvas::DrawLine(MBVec2 p0, MBVec2 p1, unsigned char r, unsigned char g, unsigned char b)
    {
        int x0 = (int)p0.x();
        int y0 = (int)p0.y();
        int x1 = (int)p1.x();
        int y1 = (int)p1.y();
        return DrawLine(x0, y0, x1, y1, r, g, b);
    }

    int MBCanvas::DrawLine(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g, unsigned char b)
    {
        bool steep = false;
        if (std::abs(x0-x1)<std::abs(y0-y1)) {
            std::swap(x0, y0);
            std::swap(x1, y1);
            steep = true;
        }
        if (x0>x1) {
            std::swap(x0, x1);
            std::swap(y0, y1);
        }
        int dx = x1-x0;
        int dy = y1-y0;
        int derror2 = std::abs(dy)*2;
        int error2 = 0;
        int y = y0;
        for (int x=x0; x<=x1; x++) {
            if (steep) {
                SetBufferPix(y, x, r, g, b);
            } else {
                SetBufferPix(x, y, r, g, b);
            }
            error2 += derror2;
            if (error2 > dx) {
                y += (y1>y0?1:-1);
                error2 -= dx*2;
            }
        }

        return 0;
    }

    int MBCanvas::DrawLine2(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b)
    {
        int x, y, rem = 0;
        //line is a pixel
        if (x1 == x2 && y1 == y2) 
        {
            SetBufferPix(x1, y1, r, g, b);
        }
        //vertical line
        else if (x1 == x2) 
        {
            int inc = (y1 <= y2) ? 1 : -1;
            for (y = y1; y != y2; y += inc) {
                SetBufferPix(x1, y, r, g, b);
            }
            SetBufferPix(x2, y2, r, g, b);
        }
        //horizontal line
        else if (y1 == y2) 
        {
            int inc = (x1 <= x2) ? 1 : -1;
            for (x = x1; x != x2; x += inc) {
                SetBufferPix(x, y1, r, g, b);
            }
            SetBufferPix(x2, y2, r, g, b);
        }

        else{
            int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
		    int dy = (y1 < y2) ? y2 - y1 : y1 - y2;

            // slope < 1
            if (dx >= dy) 
            {
                if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
                for (x = x1, y = y1; x <= x2; x++) 
                {
                    SetBufferPix(x, y, r, g, b);
                    rem += dy;
                    if (rem >= dx) 
                    {
                        rem -= dx;
                        y += (y2 >= y1) ? 1 : -1;
                    }
                }
                SetBufferPix(x2, y2, r, g, b);
            }
            // slope > 1
            else {
                if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
                for (x = x1, y = y1; y <= y2; y++) 
                {
                    SetBufferPix(x, y, r, g, b);
                    rem += dx;
                    if (rem >= dy) 
                    {
                        rem -= dy;
                        x += (x2 >= x1) ? 1 : -1;
                    }
                }
                SetBufferPix(x2, y2, r, g, b);
            }
        }

        return 0;
    }

    int MBCanvas::SetClearColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        return 0;
    }

    int MBCanvas::SetBufferPix(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        // printf("x:%d === y:%d\n", x, y);
        if(x >= width){
            return -1;
        }
        if(x < 0){
            return -1;
        }
        if(y >= height){
            return -1;
        }
        if(y < 0){
            return -1;
        }

        pixelData[(y * width + x) * 4 + 0] = r; // R
        pixelData[(y * width + x) * 4 + 1] = g; // G
        pixelData[(y * width + x) * 4 + 2] = b; // B
        pixelData[(y * width + x) * 4 + 3] = a; // A

        return 0;
    }

    int MBCanvas::RenderToTGA(MBString path)
    {
        MB::MBTgaImage image(width, height, MB::MBTgaImage::RGB);

        for(int h=0;h<height;h++){
            for(int w=0;w<width;w++){
                unsigned char r = pixelData[(h * width + w) * 4 + 0]; // R
                unsigned char g = pixelData[(h * width + w) * 4 + 1]; // G
                unsigned char b = pixelData[(h * width + w) * 4 + 2]; // B
                unsigned char a = pixelData[(h * width + w) * 4 + 3]; // A

                MB::MBTGAColor color = MB::MBTGAColor(r, g, b, 255);

                image.set(w, h, color);
            }
        }

        image.flip_vertically();
	    image.write_tga_file(path.str);
        return 0;
    }
}