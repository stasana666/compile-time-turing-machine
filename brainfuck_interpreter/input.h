#pragma once

#include "chars.h"

using InputList = CharList<
    CodeBegin,
    CurCommand<'['>,
    Command<'['>,
    Command<']'>,
    Command<']'>,
    CodeEnd,
    InputBegin,
    InputEnd,
    RamBegin,
    CurUnit<0>,
    Unit<0>,
    Unit<0>,
    Unit<0>,
    RamEnd,
    OutputBegin,
    OutputEnd
>;
