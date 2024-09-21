#include <cassert>
#include <vector>
#include <gtest/gtest.h>

class Person{

    public:
        auto age() const{
            return age_;
        }

        auto set_age(int age){
            age_ = age;
        }

    private:
        int age_{};

};

class Team{
    public:
        auto& leader() const{
            return leader_;
        }

        auto& leader(){
            return leader_;
        }

    private:
        Person leader_{};
};

auto nomutating_func(const std::vector<Team>& teams){
    auto total_age = int{0};
    for (const auto& team : teams)
        total_age+=team.leader().age();

    /*
     for (auto& team: teams)
        team.leader.set_age(20);
     */
}

auto mutating_func(std::vector<Team>& teams){
    auto total_age = int{0};
    for (const auto& team : teams)
        total_age+=team.leader().age();


    for (auto& team: teams)
        team.leader().set_age(20);

}

TEST(ConstCorrectness, Nonmutating){
    const auto teams = std::vector<Team>{};
    nomutating_func(teams);
    //mutating_func(teams);
}

TEST(ConstCorrectnessm, Mutating){
    auto teams = std::vector<Team>{};
    nomutating_func(teams);
    mutating_func(teams);
}


