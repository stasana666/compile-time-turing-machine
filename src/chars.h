#pragma once

#include "turing_machine.h"

struct InputBegin;
struct InputEnd;
struct OutputBegin;
struct OutputEnd;
struct CodeBegin;
struct CodeEnd;
struct RamBegin;
struct RamEnd;

template <char ch>
struct Command {
    static const char value = ch;
};

template <char ch>
struct CurCommand {
    static const char value = ch;
};

template <char ch>
struct Unit {
    static const char value = ch;
};

template <char ch>
struct CurUnit {
    static const char value = ch;
};
