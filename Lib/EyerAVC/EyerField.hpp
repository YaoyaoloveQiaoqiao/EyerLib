#ifndef EYERLIB_EYERFIELD_HPP
#define EYERLIB_EYERFIELD_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer{
    enum EyerFieldType{
        FIELD_UNSIGNED_INT = 2,
        FIELD_INT = 3,
        FIELD_VOID = 4
    };

    class EyerField {
    public:
        EyerField();
        EyerField(const EyerString & key,   const unsigned int & val,       const EyerString & remarks = nullptr,           int level = 0);
        EyerField(const EyerString & key,   const int & val,                const EyerString & remarks = nullptr,           int level = 0);
        EyerField(const EyerString & key,                                   const EyerString & remarks = nullptr,           int level = 0);
        ~EyerField();

        EyerField(const EyerField & field);
        EyerField & operator = (const EyerField & field);

        EyerString & GetKey();

        EyerFieldType GetType();

        unsigned int GetUnsignedIntVal();
        int GetIntVal();

        int GetLevel();

        EyerString & GetRemarks();

    private:
        EyerFieldType type = EyerFieldType::FIELD_INT;
        EyerString key = "";

        unsigned int unsignedIntVal         = 0;
        int intVal                          = 0;

        int level = 0;

        EyerString remarks = "";
    };

    typedef std::vector<EyerField *> EyerFieldList;
}

#endif //EYERLIB_EYERFIELD_HPP
