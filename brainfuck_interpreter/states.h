#pragma once

#include "../turing_machine.h"

using ReturnToCommand = struct ReturnToCommand;
using ReturnToCommandRight = struct ReturnToCommandRight;
using AddToCurCell = struct AddToCurCell;
using SubToCurCell = struct SubToCurCell;
using InitState = struct FindFirstCommand;
using NextCommand = struct NextCommand;
using DoCommand = struct DoCommand;
using MoveRightCurChar = struct MoveRightCurChar;
using MoveLeftCurChar = struct MoveLeftCurChar;
using SetCurrentChar = struct SetCurrentChar;
using OutputCharStart = struct OutputCharStart;

template <char ch>
struct OutputChar {
    static const char value = ch;
};

using InputCharStart = struct InputCharStart;

template <char ch>
struct InputChar {
    static const char value = ch;
};

using SetOutputEnd = struct SetOutputEnd;

using CircleStart = struct CircleStart;

template <bool Value>
struct Circle {
    static const bool value = Value;
};

using FindOpenBracket = struct FindOpenBracket;
using FindCloseBracket = struct FindCloseBracket;
using ReturnToCloseBracket = struct ReturnToCloseBracket;
using ReturnToOpenBracket = struct ReturnToOpenBracket;
using MarkOpenBracket = struct MarkOpenBracket;
using MarkCloseBracket = struct MarkCloseBracket;
using ReturnToMarkedCloseBracket = struct ReturnToMarkedCloseBracket;
using ReturnToMarkedOpenBracket = struct ReturnToMarkedOpenBracket;
