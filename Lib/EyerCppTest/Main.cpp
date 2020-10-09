#include <gtest/gtest.h>
#include <stdio.h>

class Base
{
public:
    Base()
    {
        printf("Base()\n");
    }
    virtual ~Base()
    {
        printf("~Base()\n");
    }

    Base(const Base & base) : Base()
    {
        printf("Base(const Base & base)\n");
        *this = base;
    }

    Base & operator = (const Base & base)
    {
        if(this == &base){
            return *this;
        }
        printf("Base & operator = (const Base base)\n");
        return *this;
    }
};

class Child : public Base
{
public:
    Child()
    {
        printf("Child()\n");
    }

    Child(const Child & child) : Child()
    {
        printf("Child(const Child & child)\n");
        *this = child;
    }

    ~Child()
    {
        printf("~Child()\n");
    }

    Child & operator = (const Child & child)
    {
        if(this == &child){
            return *this;
        }

        Base::operator=(child);

        printf("Child & operator = (const Child child)\n");
        return *this;
    }
};

TEST(CppTest, Cpp_Extends){
    {
        Child child;
        Child childC = child;
    }
    printf("============================\n");
    {
        Child childA;
        Child childB;

        childB = childA;
    }
    printf("============================\n");
    {
        Child * child = new Child();
        delete child;
    }
    printf("============================\n");
    {
        Base * child = new Child();
        delete child;
    }
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}