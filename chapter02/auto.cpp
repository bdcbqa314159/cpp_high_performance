#include <gtest/gtest.h>
#include <vector>

namespace old_syntax{

    class Foo{
        public:
            int val() const {return m_;}
            const int &cref() const {return m_;}
            int &mref() {return m_;}
        private:
            int m_{};
    };

}

namespace new_syntax{

    class Foo{
        public:
            auto val(){return m_;}
            const auto &cref() const{return m_;}
            auto &mref(){return m_;}

        private:
            int m_{};
    };
}

TEST(Auto, ConstAndMutableReference){

    auto foo = new_syntax::Foo{};
    auto &cref = foo.cref();
    auto &mref = foo.mref();

    static_assert(std::is_const_v<std::remove_reference_t<decltype(cref)>>, "");
    static_assert(!std::is_const_v<std::remove_reference_t<decltype(mref)>>, "");
}
