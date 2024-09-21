#include <cassert>
#include <gtest/gtest.h>
#include <set>
#include <string>

class Bagel{
    public:
        Bagel(std::set<std::string> ts):toppings_(std::move(ts)){}
    private:
        std::set<std::string> toppings_;
};

TEST(ValueSemantics, CreateBagels){
    auto t = std::set<std::string>{};
    t.insert("salt");

    auto a = Bagel{t};

    t.insert("pepper");
    auto b = Bagel{t};

    t.insert("oregano");
}
