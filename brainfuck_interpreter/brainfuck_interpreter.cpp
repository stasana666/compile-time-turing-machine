#include "../turing_machine.h"

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
                Command<'['>,
                Command<'['>,
                Command<']'>,
                Command<']'>
            >,
            CodeEnd,
            CharList<
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
            >
        >
    >
, "");
