#include <gtest/gtest.h>
#include <string.h>

#include <algorithm>
#include <forward_list>
#include <string>

namespace{

    struct string_elem_t{
        const char* str_;
        string_elem_t* next_;
    };

    int num_hamlet(string_elem_t* books){
        const char* hamlet = "Hamlet";
        int n = 0;
        string_elem_t* b;
        for (b = books; b!=0; b = b->next_)
            if (strcmp(b->str_, hamlet) == 0)
                ++n;

        return n;
    }

    auto num_hamlet(const std::forward_list<std::string>& books){
        return std::count(books.begin(), books.end(), "Hamlet");
    }

}

TEST(Abstractions, NumHamlet_CVersion){
    auto a = string_elem_t{"Hamlet", nullptr};
    auto b = string_elem_t{"Romeo and Juliet", nullptr};
    auto c = string_elem_t{"Hamlet", nullptr};

    a.next_ = &b;
    b.next_ = &c;

    auto* books = &a;
    auto count = num_hamlet(books);

    ASSERT_TRUE(count == 2);
}

TEST(Abstractions, NumHamlet_CppVersion){
    auto books = std::forward_list<std::string>{"Hamlet", "Romeo and Juliet", "Hamlet"};

    auto count = num_hamlet(books);

    ASSERT_TRUE(count == 2);
}

