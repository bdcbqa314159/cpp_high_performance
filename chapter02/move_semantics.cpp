#if _MSVC_VER
#pragma warning(disable : 4996)
#endif

#include <algorithm>
#include <cctype>
#include <gtest/gtest.h>
#include <initializer_list>
#include <locale>
#include <vector>

namespace{

    class Buffer{
        public:
            Buffer(const std::initializer_list<float>& values): size_{values.size()}{
                ptr_ = new float[values.size()];
                std::copy(values.begin(), values.end(), ptr_);
            }

            Buffer(const Buffer& other):size_{other.size_}{
                ptr_ = new float[size_];
                std::copy(other.ptr_, other.ptr_+size_, ptr_);
            }

            auto& operator=(const Buffer& other){
                delete[] ptr_;
                ptr_ = new float[other.size_];
                size_ = other.size_;
                std::copy(other.ptr_, other.ptr_+size_, ptr_);
                return *this;
            }

            ~Buffer(){
                delete[] ptr_;
                ptr_ = nullptr;
            }

            Buffer(Buffer&& other) noexcept: size_{other.size_}, ptr_{other.ptr_}{
                other.ptr_ = nullptr;
                other.size_ = 0;
            }

            auto& operator=(Buffer&& other) noexcept{
                ptr_ = other.ptr_;
                size_ = other.size_;
                other.ptr_ = nullptr;
                other.size_ = 0;
                return *this;
            }

            auto begin() const{return ptr_;}
            auto end() const{return ptr_ + size_;}

        private:
            size_t size_{};
            float* ptr_{nullptr};
    };

    TEST(MoveSemantics, RuleOfFive){
        auto b0 = Buffer({0.f, 0.5f, 1.f, 1.5f});
        auto b1 = b0;
        b0 = b1;
    }

    class Button{
        public:
            Button(){}

            //Copy constructor / copy assignement
            //Button(const Button&) = default;
            //auto operator=(const Button&) -> Button& = default;
            //
            //Move constructor / move assignement
            //Button(Button&&) noexcept = default;
            //auto operator=(Button&&) noexcept -> Button& = default;
            //
            //Destructor
            //~Button() = default;
            //

            auto set_title(const std::string& s){title_ = s;}
            auto set_title(std::string&& s){title_ = std::move(s);}

        private:
            std::string title_{};
    };

    auto get_ok(){return std::string("OK");}

    TEST(MoveSemantics, NamedVariablesAndRVariables){
        auto button = Button{};

        {
            auto str = std::string{"OK"};
            button.set_title(str);
        }

        {
            auto str = std::string{"OK"};
            button.set_title(std::move(str));
        }

        {
            button.set_title(get_ok());
        }

        {
            auto str = get_ok();
            button.set_title(str);
        }

        {
            const auto str = get_ok();
            button.set_title(std::move(str));
        }
    }

    class Menu{
        public:
            Menu(const std::initializer_list<std::string>& items):items_{items}{}
            void select(int i){index_ = i;}
            auto selected_item() const{return index_ != -1 ? items_[index_]: "";}

        private:
            int index_{-1};
            std::vector<std::string> items_{};
    };

    TEST(MoveSemantics, MovingNonResources){
        auto a = Menu{"New", "Open","Close", "Save"};
        a.select(2);
        ASSERT_TRUE(a.selected_item() == "Close");
        auto b = std::move(a);
        std::cout<<"after move\n";

        //Object a has been moved from but a.index_ is still 2
        //Calling a.selected_item() will likely crash since
        //a.index_ is 2 and a.items_ has been moved
        //auto selected = a.selected_item(); -> crash
        //

    }

    auto str_to_lower(std::string str){
        for (auto & c: str)
            c = std::tolower(c);

        return str;
    }

    class Widget{
        public:
            Widget(std::string s):s_{std::move(s)}{}
        private:
            std::string s_;
    };

    TEST(MoveSemantics, StrToLower){
        std::cout<<"tolower\n";
        auto upper = std::string{"ABC"};
        auto lower = str_to_lower(std::move(upper));
        ASSERT_TRUE(upper.empty());
        ASSERT_FALSE(lower.empty());
    }

    TEST(MoveSemantics, InitializingClassMembers){
        const auto w1 = Widget{"ABC"};
        const auto s = std::string{"ABC"};
        const auto w2 = Widget{s};
    }

}
