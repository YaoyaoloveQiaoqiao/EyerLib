#ifndef EYERLIB_EYERNALU_HPP
#define EYERLIB_EYERNALU_HPP

#include "EyerNALUData.hpp"
#include "EyerField.hpp"

namespace Eyer
{
    class EyerNALU {
    public:
        EyerNALU();
        ~EyerNALU();

        virtual int Parse() = 0;

        int SetNALUData(EyerNALUData & _naluData);

        int PrintInfo();
    protected:
        EyerNALUData naluData;
        std::vector<EyerField *> fieldList;
    };
}

#endif //EYERLIB_EYERNALU_HPP
