/// This file is meant to test Boost.SML aginst Miro Samek's non-trivial
/// HSM that he uses to regression-test QP.

#include <boost/sml.hpp>
#include <iostream>
#include <assert.h>

namespace sml = boost::sml;

// Define events
//
struct eA {};
static auto evtA = sml::event<eA>;
struct eB {};
static auto evtB = sml::event<eB>;
struct eC {};
static auto evtC = sml::event<eC>;
struct eD {};
static auto evtD = sml::event<eD>;
struct eE {};
static auto evtE = sml::event<eE>;
struct eF {};
static auto evtF = sml::event<eF>;
struct eG {};
static auto evtG = sml::event<eG>;
struct eH {};
static auto evtH = sml::event<eH>;
struct eI {};
static auto evtI = sml::event<eI>;

// Define states
//
static auto s11 = sml::state<class s11>;
static auto s211 = sml::state<class s211>;

class smachine;
class s1machine;
class s2machine;
class s21machine;


// Define actions
auto outer_initialAction = []{ std::cout << "outer initial transition" << std::endl; };
auto s_initialAction = []{ std::cout << "s initial transition" << std::endl; };
auto s1_initialAction = []{ std::cout << "s1 initial transition" << std::endl; };
auto s2_initialAction = []{ std::cout << "s2 initial transition" << std::endl; };
auto s21_initialAction = []{ std::cout << "s21 initial transition" << std::endl; };


class smachine
{
public:
    auto operator()() const noexcept
    {
        using namespace sml;
        return sml::make_transition_table(

                    *"initial"_s / s_initialAction = s11,
                    state<s1machine> + evtC  = state<s2machine>,
                    state<s2machine> + evtC  = state<s1machine>,
                    state<s2machine> + evtF  = s11

                );
    }
};

class s1machine
{
public:
    auto operator()() const noexcept
    {
        using namespace sml;
        return sml::make_transition_table(
                    *"initial"_s / s1_initialAction          = s11
                    );
    }
};

class s2machine
{
public:
    auto operator()() const noexcept
    {
        using namespace sml;
        return sml::make_transition_table(
                    *"initial"_s / s2_initialAction          = s211
                    );
    }
};

class s21machine
{
public:
    auto operator()() const noexcept
    {
        using namespace sml;
        return sml::make_transition_table(
                    *"initial"_s / s21_initialAction = s211
                    );
    }
};


class basemachine
{
public:
    auto operator()() const noexcept
    {
        using namespace sml;
        return sml::make_transition_table(
                    *"initial"_s / outer_initialAction = state<s2machine>,
                    state<smachine> + evtE = s11,
                    state<s1machine> + evtD = state<smachine>

                );
    }

};


int main()
{
    sml::sm<basemachine> basestatemachine;

    using namespace sml;
    basestatemachine.visit_current_states([](auto state) { std::cout << state.c_str() << std::endl;});

//    assert(basestatemachine.is(s211));
    basestatemachine.process_event(eC{});
    basestatemachine.visit_current_states([](auto state) { std::cout << state.c_str() << std::endl;});

//    assert(basestatemachine.is(state<s2machine>));
//    basestatemachine.process_event(eC{});
//    assert(basestatemachine.is(state<s1machine>));
}
