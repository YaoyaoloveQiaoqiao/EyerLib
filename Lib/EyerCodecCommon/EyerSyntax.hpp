#ifndef EYERLIB_EYERSYNTAX_HPP
#define EYERLIB_EYERSYNTAX_HPP

#include "EyerCore/EyerCore.hpp"

namespace Eyer
{
    class EyerSyntax {
    public:
        EyerSyntax();
        ~EyerSyntax();
        EyerSyntax(bool _valid, const EyerString & name, int level = 0);
        EyerSyntax(const EyerSyntax & syntax);
        EyerSyntax & operator = (const EyerSyntax & syntax);

        EyerString & GetName();
        int GetLevel();

        int SetValid(bool _valid);
        bool GetValid();

        int SetValue(const EyerString & value);
        EyerString & GetValue();

        int Put         (const EyerSyntax & syntax);
        int Put         (bool valid, const EyerString & name, int value);
        int Put         (bool valid, const EyerString & name, const EyerString & value);
        int PutValid    (const EyerString & name);
        int PutValid    (const EyerString & name, int val);
        int PutUnValid  (const EyerString & name);
        int PutUnValid  (const EyerString & name, int val);

        int GetChildSize();
        int GetChild(EyerSyntax & syntax, int i);

        int PrintInfo();
    private:
        EyerString name;
        EyerString value;
        int level = 0;
        bool valid = true;
        std::vector<EyerSyntax *> childList;
    };
}

#endif //EYERLIB_EYERSYNTAX_HPP
