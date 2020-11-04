#include <gtest/gtest.h>



TEST(Lua, LuaTest)
{
    printf("Eyer Lua Test\n");
}

int main(int argc,char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
