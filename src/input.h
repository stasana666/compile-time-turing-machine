#pragma once

#include "chars.h"

using InputList = CharList<
    CodeBegin,
    CurCommand<','>,
    Command<'>'>,
    Command<','>,
    Command<'['>,
    Command<'<'>,
    Command<'['>,
    Command<'-'>,
    Command<'.'>,
    Command<']'>,
    Command<'+'>,
    Command<'>'>,
    Command<'-'>,
    Command<']'>,
    CodeEnd,
    InputBegin,
    Unit<3>,
    Unit<3>,
    InputEnd,
    RamBegin,
    CurUnit<0>,
    Unit<0>,
    RamEnd,
    OutputBegin,
    OutputEnd
>;
