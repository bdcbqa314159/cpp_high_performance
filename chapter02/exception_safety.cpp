#include <cassert>
#include <gtest/gtest.h>

namespace{

    struct Number{
        bool operator==(const Number& rhs) const {return i_ == rhs.i_;}
        bool operator!=(const Number& rhs) const {return !(*this == rhs);}

        int i_{};
    };

    class Widget{
        public:
            Widget(const Number& x, const Number& y): x_{x}, y_{y}{
                assert(is_valid());
            }

            void update(const Number& a, const Number& b);
            bool is_valid() const{
                return x_ != y_;
            }

        private:
            Number x_{}, y_{};
    };

    void Widget::update(const Number& x, const Number& y){
        assert(x != y);
        assert(is_valid());

        auto x_tmp = x;
        auto y_tmp = y;

        std::swap(x_tmp, x_);
        std::swap(y_tmp, y_);

        assert(is_valid());
    }

    TEST(ExceptionSafety, CopyAndSwap){
        auto w = Widget{{1}, {2}};
        w.update({2}, {3});

        ASSERT_TRUE(w.is_valid());
    }


}
