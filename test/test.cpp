#include "../src/turing_machine.h"

#define ASSERT_EQUAL(...) static_assert(IsSameV<__VA_ARGS__>, "aren't equal");

template <char ch>
struct Char {
    static const char value = ch;
};

template <int idx>
struct TState {
    static const int value = idx;
};

template <int idx>
struct StateHelper {
    using value = TState<idx>;
};

template <>
struct StateHelper<9> {
    using value = Terminate;
};

template <int idx>
using State = typename StateHelper<idx>::value;

using MyRules = RuleList<
    Rule<State<0>, Char<'1'>, State<0>, Char<'1'>, MoveRight>,
    Rule<State<1>, Char<'1'>, State<2>, Char<'a'>, MoveRight>,
    Rule<State<2>, Char<'1'>, State<2>, Char<'1'>, MoveLeft>,
    Rule<State<3>, Char<'1'>, State<4>, Char<'a'>, MoveRight>,
    Rule<State<4>, Char<'1'>, State<4>, Char<'1'>, MoveRight>,
    Rule<State<7>, Char<'1'>, State<2>, Char<'a'>, MoveRight>,
    Rule<State<0>, Char<'x'>, State<1>, Char<'x'>, MoveRight>,
    Rule<State<2>, Char<'x'>, State<3>, Char<'x'>, MoveLeft>,
    Rule<State<4>, Char<'x'>, State<4>, Char<'x'>, MoveRight>,
    Rule<State<6>, Char<'x'>, State<7>, Char<'x'>, MoveRight>,
    Rule<State<8>, Char<'x'>, State<9>, Char<'x'>, Stay>,
    Rule<State<2>, Char<'='>, State<2>, Char<'='>, MoveLeft>,
    Rule<State<4>, Char<'='>, State<4>, Char<'='>, MoveRight>,
    Rule<State<7>, Char<'='>, State<8>, Char<'='>, MoveLeft>,
    Rule<State<2>, Char<'a'>, State<2>, Char<'a'>, MoveLeft>,
    Rule<State<3>, Char<'a'>, State<3>, Char<'a'>, MoveLeft>,
    Rule<State<4>, Char<'a'>, State<4>, Char<'a'>, MoveRight>,
    Rule<State<6>, Char<'a'>, State<6>, Char<'1'>, MoveRight>,
    Rule<State<7>, Char<'a'>, State<7>, Char<'a'>, MoveRight>,
    Rule<State<8>, Char<'a'>, State<8>, Char<'1'>, MoveLeft>,
    Rule<State<3>, Char<'*'>, State<6>, Char<'*'>, MoveRight>,
    Rule<State<4>, Char<'*'>, State<5>, Char<'1'>, MoveRight>,
    Rule<State<5>, Void, State<2>, Char<'*'>, MoveLeft>,
    Rule<State<0>, Char<'*'>, State<0>, Char<'*'>, MoveRight>
>;

using Input =   Tape<
                    CharList<>,
                    Char<'*'>,
                    CharList<Char<'1'>, Char<'1'>, Char<'1'>, Char<'x'>, Char<'1'>, Char<'1'>, Char<'='>, Char<'*'>>
                >;

ASSERT_EQUAL(
    TuringMachine<
        MyRules,
        State<0>,
        Input
    >::result,
    Tape<
        CharList<
            Char<'*'>,
            Char<'1'>,
            Char<'1'>,
            Char<'1'>
        >,
        Char<'x'>,
        CharList<
            Char<'1'>,
            Char<'1'>,
            Char<'='>,
            Char<'1'>,
            Char<'1'>,
            Char<'1'>,
            Char<'1'>,
            Char<'1'>,
            Char<'1'>,
            Char<'*'>
        >
    >
)
