#include "EyerCanvas.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

namespace Eyer
{
    EyerObjModel::EyerObjModel(EyerString _path)
    {
        path = _path;

        std::ifstream in;
        in.open (path.str, std::ifstream::in);
        if (in.fail()) return;
        std::string line;
        while (!in.eof()) {
            std::getline(in, line);
            std::istringstream iss(line.c_str());
            char trash;
            if (!line.compare(0, 2, "v ")) {
                iss >> trash;
                EyerVec3 v;

                float s = 0.0f; 
                iss >> s;
                v.SetX(s);

                iss >> s;
                v.SetY(s);

                iss >> s;
                v.SetZ(s);

                verts_.push_back(v);
            } else if (!line.compare(0, 2, "f ")) {
                std::vector<int> f;
                int itrash, idx;
                iss >> trash;
                while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                    idx--; // in wavefront obj all indices start at 1, not zero
                    f.push_back(idx);
                }
                faces_.push_back(f);
            }
        }
        // std::cerr << "# v# " << verts_.size() << " f# "  << faces_.size() << std::endl;
    }

    EyerObjModel::~EyerObjModel()
    {

    }

    int EyerObjModel::nverts()
    {
        return (int)verts_.size();
    }

    int EyerObjModel::nfaces()
    {
        return (int)faces_.size();
    }

    EyerVec3 EyerObjModel::vert(int i)
    {
        return verts_[i];
    }

    std::vector<int> EyerObjModel::face(int idx)
    {
        return faces_[idx];
    }
}