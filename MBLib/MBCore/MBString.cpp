#include "MBString.hpp"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

namespace MB {
    MBString::MBString()
    {

    }

    MBString::MBString(const MBString & str)
    {
        *this = str;
    }

    MBString::~MBString()
    {
        ClearStr();
    }

    MBString::MBString(const char _str[])
    {
        ClearStr();

        if(_str == nullptr){
            return;
        }

        int _strLen = strlen(_str) + 1;
        str = (char *)malloc(_strLen);
        memcpy(str, _str, _strLen);
    }

    MBString & MBString::operator = (const MBString & s)
    {
        ClearStr();

        if(s.str == nullptr){
            return *this;
        }

        int _strLen = strlen(s.str) + 1;
        str = (char *)malloc(_strLen);
        memcpy(str, s.str, _strLen);

        return *this;
    }

    bool MBString::operator == (const MBString & s)
    {
        if(IsEmpty() && s.IsEmpty()){
            return true;
        }

        if(IsEmpty()){
            return false;
        }

        if(s.IsEmpty()){
            return false;
        }

        if (strcmp(str, s.str) == 0) {
            return true;
        }

        return false;
    }

    bool MBString::operator > (const MBString & s)
    {
        if(strcmp(str, s.str) > 0){
            return false;
        }
        return true;
    }

    bool MBString::operator < (const MBString & s)
    {
        if(strcmp(str, s.str) < 0){
            return false;
        }
        return true;
    }

    MBString MBString::operator + (const MBString & s){
        MBString outStr;

        if(IsEmpty() && s.IsEmpty()){
            return outStr;
        }

        int strALen = 0;
        if(!IsEmpty()){
            strALen = strlen(str);
        }

        int strBLen = 0;
        if(!s.IsEmpty()){
            strBLen = strlen(s.str);
        }

        int strLen = strALen + strBLen;
        if(strLen <= 0){
            return outStr;
        }

        // alloc
        outStr.str = (char *)malloc(strLen + 1);
        if(strALen > 0){
            memcpy(outStr.str, str, strALen);
        }

        if(strBLen > 0){
            memcpy(outStr.str + strALen, s.str, strBLen);
        }

        outStr.str[strLen] = '\0';

        return outStr;
    }

    bool MBString::IsEmpty() const
    {
        if(str == nullptr){
            return true;
        }
        return false;
    }

    int MBString::ClearStr()
    {
        if(str != nullptr){
            free(str);
            str = nullptr;
        }

        return 0;
    }

    MBString MBString::Number(int num, MBString format)
    {
        char str[1024];

        sprintf(str, format.str, num);

        return str;
    }

    MBString Number(long num)
    {
        char str[1024];

        sprintf(str, "%ld", num);

        return str;
    }

    MBString Number(long long num)
    {
        char str[1024];

        sprintf(str, "%lld", num);

        return str;
    }
}
