#pragma once

#include "logic_operations.h"

struct MoveLeft;
struct MoveRight;
struct Stay;

struct Void;
struct Terminate;

template <class...>
struct CharList;

template <class...>
struct Concatenate;

template <class... Chars, class Char>
struct Concatenate<CharList<Chars...>, Char> {
    using value = CharList<Chars..., Char>;
};

template <class... Chars, class Char>
struct Concatenate<Char, CharList<Chars...>> {
    using value = CharList<Char, Chars...>;
};

template <class...>
struct ExtractLeft;

template <class... Chars, class LeftChar>
struct ExtractLeft<CharList<LeftChar, Chars...>> {
    using list = CharList<Chars...>;
    using elem = LeftChar;
};

template <>
struct ExtractLeft<CharList<>> {
    using list = CharList<>;
    using elem = Void;
};

template <class...>
class ExtractRightHelper;

template <class... Args, class Cur>
class ExtractRightHelper<CharList<Args...>, CharList<Cur>> {
public:
    using elem = Cur;
    using list = CharList<Args...>;
};

template<>
class ExtractRightHelper<CharList<>, CharList<>> {
public:
    using elem = Void;
    using list = CharList<>;
};

template <class... Args1, class Cur, class... Args2>
class ExtractRightHelper<CharList<Args1...>, CharList<Cur, Args2...>> {
    using value = ExtractRightHelper<CharList<Args1..., Cur>, CharList<Args2...>>;

public:
    using elem = typename value::elem;
    using list = typename value::list;
};

template <class list_>
class ExtractRight {
    using value = ExtractRightHelper<CharList<>, list_>;

public:
    using elem = typename value::elem;
    using list = typename value::list;
};

template <class left_, class current_, class right_>
struct Tape {
    using left = left_;
    using current = current_;
    using right = right_;
};

template <class...>
class MovedTape;

template <class tape>
class MovedTape<tape, MoveLeft> {
    using left = ExtractRight<typename tape::left>;

public:
    using value   = Tape<
                        typename left::list,
                        typename left::elem, 
                        typename Concatenate<
                            typename tape::current,
                            typename tape::right
                        >::value
                    >;
};

template <class tape>
class MovedTape<tape, MoveRight> {
    using right = ExtractLeft<typename tape::right>;

public:
    using value   = Tape<
                        typename Concatenate<
                            typename tape::left,
                            typename tape::current
                        >::value,
                        typename right::elem,
                        typename right::list
                    >;
};

template <class tape>
class MovedTape<tape, Stay> {
public:
    using value = tape;
};

template <class srcState_, class srcChar_, class dstState_, class dstChar_, class move_>
struct Rule {
    using srcState = srcState_;
    using srcChar = srcChar_;
    using dstState = dstState_;
    using dstChar = dstChar_;
    using move = move_;
};

template <class...>
struct RuleList;

template <class F_, class S_>
struct Pair {
    using S = S_;
    using F = F_;
};

template <class...>
struct ApplyRule;

template <class dstState, class dstChar, class move, class... rulesArgs, class state, class left, class cur, class right>
struct ApplyRule<RuleList<Rule<state, cur, dstState, dstChar, move>, rulesArgs...>, state, Tape<left, cur, right>> {
    using result = Pair<dstState, typename MovedTape<Tape<left, dstChar, right>, move>::value>;

    using newState = typename result::F;
    using newTape = typename result::S;
};

template <class rule, class... rulesArgs, class state, class left, class cur, class right>
struct ApplyRule<RuleList<rule, rulesArgs...>, state, Tape<left, cur, right>> {
    using result = typename ApplyRule<RuleList<rulesArgs...>, state, Tape<left, cur, right>>::result;

    using newState = typename result::F;
    using newTape = typename result::S;
};

template <class state, class left, class cur, class right>
struct ApplyRule<RuleList<>, state, Tape<left, cur, right>>;

template <class...>
struct TuringMachine;

template <class... rulesArgs, class state, class left, class cur, class right>
struct TuringMachine<RuleList<rulesArgs...>, state, Tape<left, cur, right>> {
    using next = ApplyRule<RuleList<rulesArgs...>, state, Tape<left, cur, right>>;
public:
    using result = typename TuringMachine<
                                RuleList<rulesArgs...>,
                                typename next::newState,
                                typename next::newTape
                            >::result;
};

template <class... rulesArgs, class left, class cur, class right>
struct TuringMachine<RuleList<rulesArgs...>, Terminate, Tape<left, cur, right>> {
    using result = Tape<left, cur, right>;
};
