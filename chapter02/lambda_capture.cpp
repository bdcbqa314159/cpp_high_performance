#include <algorithm>
#include <cassert>
#include <gtest/gtest.h>
#include <iostream>
#include <list>
#include <string>
#include <vector>

auto count_value_above(const std::vector<int>& vals, int x){
    auto is_above = [x](int v){return v>x;};
    return std::count_if(vals.begin(), vals.end(), is_above);
}

TEST(LambdaCapture, CountValueAbove){
    const auto vals = {1,2,3,4,5,6};
    const auto c= count_value_above(vals,2);
    ASSERT_EQ(4,c);
}

TEST(LambdaCapture, CaptureByValue){
    auto vals = {1,2,3,4,5,6};
    auto x = 3;
    auto is_above = [x](int v){return v>x;};
    x = 4;
    auto count_b = std::count_if(vals.begin(), vals.end(), is_above);
    ASSERT_EQ(3, count_b);
}

TEST(LambdaCapture, CaptureByReference){
    auto vals = {1,2,3,4,5,6};
    auto x = 3;
    auto is_above = [&x](int v){return v>x;};
    x = 4;
    auto count_b = std::count_if(vals.begin(), vals.end(), is_above);
    ASSERT_EQ(2, count_b);
}

TEST(LambdaCapture, Initialization){
    auto func = [c = std::list{4,2}](){
        for (auto v: c){
            std::cout<<v;
        }
    };

    func();
}

TEST(LambdaCapture, MutatingCapture){
    auto counter_func = [counter = 1]() mutable{std::cout<<counter++;};

    counter_func();
    counter_func();
    counter_func();
}

TEST(LambdaCapture, MutatingCaptureByValueVSReference){
    {
        auto v = 7;
        auto lambda = [v]() mutable{
            std::cout<<v<<" ";
            ++v;
        };
        ASSERT_EQ(7,v);
        lambda();
        lambda();
        ASSERT_EQ(7,v);
        std::cout<<v;
    }

    {
        auto v = 7;
        auto lambda = [&v](){
            std::cout<<v<<" ";
            ++v;
        };
        ASSERT_EQ(7,v);
        lambda();
        lambda();
        ASSERT_EQ(9,v);
        std::cout<<v;
    }

}

class Foo{
    public:
        auto member_function(){
            auto a = 0;
            auto b = 1.f;

            auto lambda_0 = [=](){std::cout<<a<<b;};

            auto lambda_1 = [&](){std::cout<<a<<b;};

            auto lambda_2 = [this](){std::cout<<m_;};

            auto lamda_3 = [*this](){std::cout<<m_;};
        }

    private:
        int m_{};
};

