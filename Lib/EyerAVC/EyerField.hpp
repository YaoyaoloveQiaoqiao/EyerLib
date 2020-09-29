#ifndef EYERLIB_EYERFIELD_HPP
#define EYERLIB_EYERFIELD_HPP

#include "EyerCore/EyerCore.hpp"
#include "EyerAVCCommon.hpp"

namespace Eyer{
    enum EyerFieldType{
        BOOL = 1,
        UNSIGNED_INT = 2,
    };

    class EyerField {
    public:
        EyerField();
        EyerField(const EyerString & key, const Boolean & val);
        EyerField(const EyerString & key, const unsigned int & val);
        ~EyerField();

        EyerField(const EyerField & field);
        EyerField operator = (const EyerField & field);

        EyerString & GetKey();

        EyerFieldType & GetType();

        unsigned int & GetUnsignedIntVal();
        Boolean & GetBooleanVal();

    private:
        EyerFieldType type = EyerFieldType::BOOL;

        EyerString key;

        Boolean boolVal                     = Boolean::TRUE;
        unsigned int unsignedIntVal         = 0;
    };
}

#endif //EYERLIB_EYERFIELD_HPP
