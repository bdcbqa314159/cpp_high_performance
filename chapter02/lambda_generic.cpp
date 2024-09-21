#include <gtest/gtest.h>

TEST(LambdaGeneric, BasicExample){

    auto v = 3;
    auto lambda = [v](auto v0, auto v1){return v+v0*v1;};

    auto res_int = lambda(1,2);
    ASSERT_EQ(5, res_int);
    auto res_float = lambda(1.f, 2.f);
    ASSERT_NEAR(5.f, res_float, 0.1f);
}

TEST(LambdaGeneric, AutoAndTypename){
    auto x = [](auto v){return v+1;};
    auto y = []<typename Val>(Val v){return v+1;};

    {
        auto v = 'a';
        ASSERT_EQ(v+1, x(v));
        ASSERT_EQ(v+1, y(v));
    }

    {
        ASSERT_EQ(42, x(41));
        ASSERT_EQ(42, y(41));
    }

    {
        auto v = std::uint64_t{41};
        ASSERT_EQ(v+1, x(v));
        ASSERT_EQ(v+1, y(v));
    }
}
