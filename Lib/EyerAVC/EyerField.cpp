#include "EyerField.hpp"

namespace Eyer
{
    EyerField::EyerField()
    {

    }

    EyerField::EyerField(const EyerString & _key, const unsigned int & _val, const EyerString & _remarks, int _level) : EyerField()
    {
        key = _key;
        unsignedIntVal = _val;

        type = EyerFieldType::UNSIGNED_INT;

        level = _level;

        remarks = _remarks;
    }

    EyerField::EyerField(const EyerString & _key, const int & _val, const EyerString & _remarks, int _level) : EyerField()
    {
        key = _key;
        intVal = _val;

        type = EyerFieldType::INT;

        level = _level;

        remarks = _remarks;
    }

    EyerField::EyerField(const EyerString & _key, const EyerString & _remarks, int _level)
    {
        key = _key;

        type = EyerFieldType::VOID;

        level = _level;

        remarks = _remarks;
    }

    EyerField::~EyerField()
    {

    }

    EyerField::EyerField(const EyerField & field) : EyerField()
    {
        *this = field;
    }

    EyerField & EyerField::operator = (const EyerField & field)
    {
        type = field.type;

        key = field.key;

        unsignedIntVal = field.unsignedIntVal;
        intVal = field.intVal;

        level = field.level;

        remarks = field.remarks;

        return *this;
    }

    EyerString & EyerField::GetKey()
    {
        return key;
    }

    EyerFieldType EyerField::GetType()
    {
        return type;
    }

    unsigned int EyerField::GetUnsignedIntVal()
    {
        return unsignedIntVal;
    }

    int EyerField::GetIntVal()
    {
        return intVal;
    }

    int EyerField::GetLevel()
    {
        return level;
    }

    EyerString & EyerField::GetRemarks()
    {
        return remarks;
    }
}