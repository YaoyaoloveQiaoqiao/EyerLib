#include "EyerNALU.hpp"

namespace Eyer
{
    EyerNALU::EyerNALU()
    {

    }

    EyerNALU::EyerNALU(const EyerNALU & nalu)
    {
        *this = nalu;
    }

    EyerNALU::~EyerNALU()
    {
    }

    EyerNALU & EyerNALU::operator = (const EyerNALU & nalu)
    {
        naluData    = nalu.naluData;
        valid       = nalu.valid;
        rootSyntax  = nalu.rootSyntax;
        return *this;
    }

    int EyerNALU::SetNALUData(EyerNALUData & _naluData)
    {
        naluData = _naluData;
        return 0;
    }

    NALUType & EyerNALU::GetNALUType()
    {
        return naluData.GetNALUType();
    }

    int EyerNALU::Parse()
    {
        return 0;
    }

    bool EyerNALU::isValid()
    {
        return valid;
    }

    int EyerNALU::PrintInfo()
    {
        // EyerLog("==============================================================\n");
        rootSyntax.PrintInfo();
        // EyerLog("==============================================================\n");
        return 0;
    }

    int EyerNALU::intlog2(int x)
    {
        int log = 0;
        if (x < 0) { x = 0; }
        while ((x >> log) > 0)
        {
            log++;
        }
        if (log > 0 && x == 1<<(log-1)) { log--; }
        return log;
    }
}