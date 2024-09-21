#if __has_include(<experimental/propagate_const>)

#include <experimental/propagate_const>

class Foo{
    private:
        std::experimental::propagate_const<int*> ptr_ = nullptr;
        int val_{};

    public:
        auto set_ptr(int* p) const{
            //ptr_ = p; -> will not compile
        }

        auto set_val(int v) const{
            //val_ = v; -> will not compile
        }

        auto set_ptr_val(int v) const {
            //*ptr_ = v; will not compile 
        }
};


#endif
