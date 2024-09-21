#include <cassert>
#include <gtest/gtest.h>
#include <vector>

struct Car{
    int doors_{};
};

auto some_func(){
    auto num_doors = 2;
    auto car1 = Car{num_doors};
    auto car2 = Car{num_doors};
}

auto car_list(){
    const auto n = 17;
    auto cars = std::vector<Car>{};
    cars.reserve(n);

    for (size_t i = 0; i<n; ++i){
        cars.push_back(Car{});
    }
}

TEST(HeapAllocations, Car){
    some_func();
    car_list();
}
