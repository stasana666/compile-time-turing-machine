#include "turing_machine.h"

#include "chars.h"
#include "rules.h"
#include "input.h"
#include "states.h"

using BrainFuckInterpreterRules = ConcatenateRules<
    AddRules,
    SubRules,
    ReturnToCommandRules,
    ReturnToCommandRightRules,
    FindFirstCommandRules,
    DoCommandRules,
    NextCommandRules,
    MoveRightCurCharRules,
    MoveLeftCurCharRules,
    SetCurrentCharRules,
    OutputRules,
    SetoutputEndRules,
    InputRules,
    CircleRules
>::rules;

using Input = MovedTape<Tape<
    CharList<>,
    Void,
    InputList
>, MoveRight>::value;

static_assert(
    IsSameV<
        TuringMachine<
            BrainFuckInterpreterRules,
            InitState,
            Input
        >::result,
        Tape<
            CharList<
                Void,
                CodeBegin,
                Command<','>,
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
                Command<']'>
            >,
            CodeEnd,
            CharList<
                InputBegin,
                InputBegin,
                InputBegin,
                InputEnd,
                RamBegin,
                Unit<1>,
                CurUnit<0>,
                RamEnd,
                OutputBegin,
                Unit<2>,
                Unit<1>,
                Unit<0>,
                Unit<0>,
                Unit<0>,
                OutputEnd
            >
        >
    >
, "");
