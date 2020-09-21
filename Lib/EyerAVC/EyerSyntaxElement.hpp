#ifndef EYERLIB_EYERSYNTAXELEMENT_HPP
#define EYERLIB_EYERSYNTAXELEMENT_HPP

namespace Eyer{
    class EyerSyntaxElement {
    public:
        int           type;                  //!< type of syntax element for data part.
        int           value1;                //!< numerical value of syntax element
        int           value2;                //!< for blocked symbols, e.g. run/level
        int           len;                   //!< length of code
        int           inf;                   //!< info part of CAVLC code
        unsigned int  bitpattern;            //!< CAVLC bitpattern
        int           context;               //!< CABAC context
        int           k;                     //!< CABAC context for coeff_count,uv


    public:
        void linfo_ue(int len, int info, int * value1, int * dummy);
    };
}

#endif //EYERLIB_EYERSYNTAXELEMENT_HPP
