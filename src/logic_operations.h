#pragma once

///////////////////////////////////////////////////////

template <class S, class F>
struct IsSame {
    static const bool value = false;
};

template<class T>
struct IsSame<T, T> {
    static const bool value = true;
};

template <class S, class F>
static const bool IsSameV = IsSame<S, F>::value;

///////////////////////////////////////////////////////

template <bool statement, class T, class F>
struct IfElse {
    using value = T;
};

template <class T, class F>
struct IfElse<false, T, F> {
    using value = F;
};

template <bool statement, class T, class F>
using IfElseV = typename IfElse<statement, T, F>::value;

///////////////////////////////////////////////////////

template <bool x, bool... args>
static const bool And = x && And<args...>;

template <bool x>
static const bool And<x> = x;
