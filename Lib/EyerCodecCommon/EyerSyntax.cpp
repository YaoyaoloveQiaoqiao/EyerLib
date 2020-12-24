#include "EyerSyntax.hpp"

namespace Eyer
{
    EyerSyntax::EyerSyntax() : EyerSyntax(true, "root")
    {
    }

    EyerSyntax::~EyerSyntax()
    {
        for(int i=0;i<childList.size();i++){
            delete childList[i];
        }
        childList.clear();
    }

    EyerSyntax::EyerSyntax(bool _valid, const EyerString & _name, int _level)
    {
        valid   = _valid;
        level   = _level;
        name    = _name;
    }

    EyerSyntax::EyerSyntax(const EyerSyntax & syntax)
    {
        *this = syntax;
    }

    EyerSyntax & EyerSyntax::operator = (const EyerSyntax & syntax)
    {
        for(int i=0;i<syntax.childList.size();i++){
            EyerSyntax * tempSyntax = new EyerSyntax(*syntax.childList[i]);
            childList.push_back(tempSyntax);
        }
        name    = syntax.name;
        level   = syntax.level;
        value   = syntax.value;
        valid   = syntax.valid;
        return *this;
    }

    int EyerSyntax::GetLevel()
    {
        return level;
    }

    EyerString & EyerSyntax::GetName()
    {
        return name;
    }

    int EyerSyntax::SetValid(bool _valid)
    {
        valid = _valid;
        return 0;
    }

    bool EyerSyntax::GetValid()
    {
        return valid;
    }


    int EyerSyntax::SetValue(const EyerString & _value)
    {
        value = _value;
        return 0;
    }

    EyerString & EyerSyntax::GetValue()
    {
        return value;
    }

    int EyerSyntax::Put(const EyerSyntax & _syntax)
    {
        EyerSyntax * syntax = new EyerSyntax(_syntax);
        childList.push_back(syntax);
        return 0;
    }

    int EyerSyntax::Put(bool valid, const EyerString & name, int value)
    {
        return Put(valid, name, EyerString::Number(value));
    }

    int EyerSyntax::Put(bool valid, const EyerString & _name, const EyerString & _value)
    {
        EyerSyntax * syntax = new EyerSyntax(valid, _name, level + 1);
        syntax->SetValue(_value);
        childList.push_back(syntax);
        return 0;
    }



    int EyerSyntax::PutValid(const EyerString & _name)
    {
        return Put(true, _name, "");
    }

    int EyerSyntax::PutValid(const EyerString & _name, int val)
    {
        return Put(true, _name, EyerString::Number(val));
    }


    int EyerSyntax::PutUnValid(const EyerString & _name)
    {
        return Put(false, _name, "");
    }

    int EyerSyntax::PutUnValid(const EyerString & _name, int val)
    {
        return Put(false, _name, EyerString::Number(val));;
    }

    int EyerSyntax::GetChildSize()
    {
        return childList.size();
    }

    int EyerSyntax::GetChild(EyerSyntax & syntax, int i)
    {
        syntax = *childList[i];
        return 0;
    }

    int EyerSyntax::PrintInfo()
    {
        EyerString t = "";
        for(int i=0;i<level;i++){
            t = t + "\t";
        }
        EyerLog("%s%s %s\n", t.str, name.str, value.str);
        for(int i=0;i<childList.size();i++){
            childList[i]->PrintInfo();
        }
        return 0;
    }
}
