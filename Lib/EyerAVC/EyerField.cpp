#include "EyerField.hpp"

namespace Eyer
{
    EyerField::EyerField()
    {

    }

    EyerField::EyerField(const EyerString & _key, const Boolean & _val, int _level) : EyerField()
    {
        key = _key;
        boolVal = _val;

        type = EyerFieldType::BOOL;

        level = _level;
    }

    EyerField::EyerField(const EyerString & _key, const unsigned int & _val, int _level) : EyerField()
    {
        key = _key;
        unsignedIntVal = _val;

        type = EyerFieldType::UNSIGNED_INT;

        level = _level;
    }

    EyerField::EyerField(const EyerString & _key, const int & _val, int _level) : EyerField()
    {
        key = _key;
        intVal = _val;

        type = EyerFieldType::INT;

        level = _level;
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

        boolVal = field.boolVal;
        unsignedIntVal = field.unsignedIntVal;
        intVal = field.intVal;

        level = field.level;

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

    Boolean EyerField::GetBooleanVal()
    {
        return boolVal;
    }

    int EyerField::GetIntVal()
    {
        return intVal;
    }

    int EyerField::GetLevel()
    {
        return level;
    }
}