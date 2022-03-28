#pragma once

#include "../turing_machine.h"

#include "chars.h"
#include "states.h"

template <class...>
struct ConcatenateRules;

template <class... firstRules, class... secondRules, class... otherRules>
struct ConcatenateRules<RuleList<firstRules...>, RuleList<secondRules...>, otherRules...> {
    using rules = typename ConcatenateRules<RuleList<firstRules..., secondRules...>, otherRules...>::rules;
};

template <class... rules_>
struct ConcatenateRules<RuleList<rules_...>> {
    using rules = RuleList<rules_...>;
};

template<class State, class Char>
using RuleMoveRight = Rule<State, Char, State, Char, MoveRight>;

template<class State, class Char>
using RuleMoveLeft = Rule<State, Char, State, Char, MoveLeft>;

template <class State>
using FindCurrentChar = RuleList<
    RuleMoveRight<State, Unit<0>>,
    RuleMoveRight<State, Unit<1>>,
    RuleMoveRight<State, Unit<2>>,
    RuleMoveRight<State, Unit<3>>,
    RuleMoveRight<State, Command<'+'>>,
    RuleMoveRight<State, Command<'-'>>,
    RuleMoveRight<State, Command<'.'>>,
    RuleMoveRight<State, Command<','>>,
    RuleMoveRight<State, Command<'['>>,
    RuleMoveRight<State, Command<']'>>,
    RuleMoveRight<State, Command<'<'>>,
    RuleMoveRight<State, Command<'>'>>,
    RuleMoveRight<State, CurCommand<'+'>>,
    RuleMoveRight<State, CurCommand<'-'>>,
    RuleMoveRight<State, CurCommand<'.'>>,
    RuleMoveRight<State, CurCommand<','>>,
    RuleMoveRight<State, CurCommand<'['>>,
    RuleMoveRight<State, CurCommand<']'>>,
    RuleMoveRight<State, CurCommand<'<'>>,
    RuleMoveRight<State, CurCommand<'>'>>,
    RuleMoveRight<State, CodeBegin>,
    RuleMoveRight<State, CodeEnd>,
    RuleMoveRight<State, RamBegin>,
    RuleMoveRight<State, RamEnd>,
    RuleMoveRight<State, InputBegin>,
    RuleMoveRight<State, InputEnd>
>;

using AddRules = ConcatenateRules<
    RuleList<
        Rule<AddToCurCell, CurUnit<0>, ReturnToCommand, CurUnit<1>, Stay>,
        Rule<AddToCurCell, CurUnit<1>, ReturnToCommand, CurUnit<2>, Stay>,
        Rule<AddToCurCell, CurUnit<2>, ReturnToCommand, CurUnit<3>, Stay>,
        Rule<AddToCurCell, CurUnit<3>, ReturnToCommand, CurUnit<0>, Stay>
    >,
    FindCurrentChar<AddToCurCell>
>::rules;

using SubRules = ConcatenateRules<
    RuleList<
        Rule<SubToCurCell, CurUnit<0>, ReturnToCommand, CurUnit<3>, Stay>,
        Rule<SubToCurCell, CurUnit<1>, ReturnToCommand, CurUnit<0>, Stay>,
        Rule<SubToCurCell, CurUnit<2>, ReturnToCommand, CurUnit<1>, Stay>,
        Rule<SubToCurCell, CurUnit<3>, ReturnToCommand, CurUnit<2>, Stay>
    >,
    FindCurrentChar<SubToCurCell>
>::rules;

template <class State>
using FindCurrentCommandRules = RuleList<
    RuleMoveLeft<State, CurUnit<0>>,
    RuleMoveLeft<State, CurUnit<1>>,
    RuleMoveLeft<State, CurUnit<2>>,
    RuleMoveLeft<State, CurUnit<3>>,
    RuleMoveLeft<State, Unit<0>>,
    RuleMoveLeft<State, Unit<1>>,
    RuleMoveLeft<State, Unit<2>>,
    RuleMoveLeft<State, Unit<3>>,
    RuleMoveLeft<State, Command<'+'>>,
    RuleMoveLeft<State, Command<'-'>>,
    RuleMoveLeft<State, Command<'.'>>,
    RuleMoveLeft<State, Command<','>>,
    RuleMoveLeft<State, Command<'['>>,
    RuleMoveLeft<State, Command<']'>>,
    RuleMoveLeft<State, Command<'<'>>,
    RuleMoveLeft<State, Command<'>'>>,
    RuleMoveLeft<State, CodeEnd>,
    RuleMoveLeft<State, InputBegin>,
    RuleMoveLeft<State, InputEnd>,
    RuleMoveLeft<State, RamBegin>,
    RuleMoveLeft<State, RamEnd>,
    RuleMoveLeft<State, OutputBegin>,
    RuleMoveLeft<State, OutputEnd>
>;

template <class State>
using FindCurrentCommandRightRules = RuleList<
    RuleMoveRight<State, CurUnit<0>>,
    RuleMoveRight<State, CurUnit<1>>,
    RuleMoveRight<State, CurUnit<2>>,
    RuleMoveRight<State, CurUnit<3>>,
    RuleMoveRight<State, Unit<0>>,
    RuleMoveRight<State, Unit<1>>,
    RuleMoveRight<State, Unit<2>>,
    RuleMoveRight<State, Unit<3>>,
    RuleMoveRight<State, Command<'+'>>,
    RuleMoveRight<State, Command<'-'>>,
    RuleMoveRight<State, Command<'.'>>,
    RuleMoveRight<State, Command<','>>,
    RuleMoveRight<State, Command<'['>>,
    RuleMoveRight<State, Command<']'>>,
    RuleMoveRight<State, Command<'<'>>,
    RuleMoveRight<State, Command<'>'>>,
    RuleMoveRight<State, CodeEnd>,
    RuleMoveRight<State, InputBegin>,
    RuleMoveRight<State, InputEnd>,
    RuleMoveRight<State, RamBegin>,
    RuleMoveRight<State, RamEnd>,
    RuleMoveRight<State, OutputBegin>,
    RuleMoveRight<State, OutputEnd>
>;

using ReturnToCommandRules = ConcatenateRules<
    RuleList<
        Rule<ReturnToCommand, CurCommand<'+'>, NextCommand, CurCommand<'+'>, Stay>,
        Rule<ReturnToCommand, CurCommand<'-'>, NextCommand, CurCommand<'-'>, Stay>,
        Rule<ReturnToCommand, CurCommand<'.'>, NextCommand, CurCommand<'.'>, Stay>,
        Rule<ReturnToCommand, CurCommand<','>, NextCommand, CurCommand<','>, Stay>,
        Rule<ReturnToCommand, CurCommand<']'>, NextCommand, CurCommand<']'>, Stay>,
        Rule<ReturnToCommand, CurCommand<'['>, NextCommand, CurCommand<'['>, Stay>,
        Rule<ReturnToCommand, CurCommand<'<'>, NextCommand, CurCommand<'<'>, Stay>,
        Rule<ReturnToCommand, CurCommand<'>'>, NextCommand, CurCommand<'>'>, Stay>
    >,
    FindCurrentCommandRules<ReturnToCommand>
>::rules;

using ReturnToCommandRightRules = ConcatenateRules<
    RuleList<
        Rule<ReturnToCommandRight, CurCommand<'+'>, NextCommand, CurCommand<'+'>, Stay>,
        Rule<ReturnToCommandRight, CurCommand<'-'>, NextCommand, CurCommand<'-'>, Stay>,
        Rule<ReturnToCommandRight, CurCommand<'.'>, NextCommand, CurCommand<'.'>, Stay>,
        Rule<ReturnToCommandRight, CurCommand<','>, NextCommand, CurCommand<','>, Stay>,
        Rule<ReturnToCommandRight, CurCommand<']'>, NextCommand, CurCommand<']'>, Stay>,
        Rule<ReturnToCommandRight, CurCommand<'['>, NextCommand, CurCommand<'['>, Stay>,
        Rule<ReturnToCommandRight, CurCommand<'<'>, NextCommand, CurCommand<'<'>, Stay>,
        Rule<ReturnToCommandRight, CurCommand<'>'>, NextCommand, CurCommand<'>'>, Stay>
    >,
    FindCurrentCommandRightRules<ReturnToCommandRight>
>::rules;

using MoveRightCurCharRules =  ConcatenateRules<
    RuleList<
        Rule<MoveRightCurChar, CurUnit<0>, SetCurrentChar, Unit<0>, MoveRight>,
        Rule<MoveRightCurChar, CurUnit<1>, SetCurrentChar, Unit<1>, MoveRight>,
        Rule<MoveRightCurChar, CurUnit<2>, SetCurrentChar, Unit<2>, MoveRight>,
        Rule<MoveRightCurChar, CurUnit<3>, SetCurrentChar, Unit<3>, MoveRight>
    >,
    FindCurrentChar<MoveRightCurChar>
>::rules;

using MoveLeftCurCharRules =  ConcatenateRules<
    RuleList<
        Rule<MoveLeftCurChar, CurUnit<0>, SetCurrentChar, Unit<0>, MoveLeft>,
        Rule<MoveLeftCurChar, CurUnit<1>, SetCurrentChar, Unit<1>, MoveLeft>,
        Rule<MoveLeftCurChar, CurUnit<2>, SetCurrentChar, Unit<2>, MoveLeft>,
        Rule<MoveLeftCurChar, CurUnit<3>, SetCurrentChar, Unit<3>, MoveLeft>
    >,
    FindCurrentChar<MoveLeftCurChar>
>::rules;

using SetCurrentCharRules = RuleList<
    Rule<SetCurrentChar, Unit<0>, ReturnToCommand, CurUnit<0>, Stay>,
    Rule<SetCurrentChar, Unit<1>, ReturnToCommand, CurUnit<1>, Stay>,
    Rule<SetCurrentChar, Unit<2>, ReturnToCommand, CurUnit<2>, Stay>,
    Rule<SetCurrentChar, Unit<3>, ReturnToCommand, CurUnit<3>, Stay>
>;

using NextCommandRules = RuleList<
    Rule<NextCommand, CurCommand<'+'>, NextCommand, Command<'+'>, MoveRight>,
    Rule<NextCommand, CurCommand<'-'>, NextCommand, Command<'-'>, MoveRight>,
    Rule<NextCommand, CurCommand<'.'>, NextCommand, Command<'.'>, MoveRight>,
    Rule<NextCommand, CurCommand<','>, NextCommand, Command<','>, MoveRight>,
    Rule<NextCommand, CurCommand<'<'>, NextCommand, Command<'<'>, MoveRight>,
    Rule<NextCommand, CurCommand<'>'>, NextCommand, Command<'>'>, MoveRight>,
    Rule<NextCommand, CurCommand<'['>, NextCommand, Command<'['>, MoveRight>,
    Rule<NextCommand, CurCommand<']'>, NextCommand, Command<']'>, MoveRight>,
    Rule<NextCommand, Command<'+'>, DoCommand, CurCommand<'+'>, Stay>,
    Rule<NextCommand, Command<'-'>, DoCommand, CurCommand<'-'>, Stay>,
    Rule<NextCommand, Command<'.'>, DoCommand, CurCommand<'.'>, Stay>,
    Rule<NextCommand, Command<','>, DoCommand, CurCommand<','>, Stay>,
    Rule<NextCommand, Command<'<'>, DoCommand, CurCommand<'<'>, Stay>,
    Rule<NextCommand, Command<'>'>, DoCommand, CurCommand<'>'>, Stay>,
    Rule<NextCommand, Command<']'>, DoCommand, CurCommand<']'>, Stay>,
    Rule<NextCommand, Command<'['>, DoCommand, CurCommand<'['>, Stay>,
    Rule<NextCommand, CodeEnd, Terminate, CodeEnd, Stay>
>;

using FindFirstCommandRules = RuleList<
    Rule<FindFirstCommand, CodeBegin, DoCommand, CodeBegin, MoveRight>
>;

template <class State>
using FindOutputEnd = RuleList<
    RuleMoveRight<State, Unit<0>>,
    RuleMoveRight<State, Unit<1>>,
    RuleMoveRight<State, Unit<2>>,
    RuleMoveRight<State, Unit<3>>,
    RuleMoveRight<State, CurUnit<0>>,
    RuleMoveRight<State, CurUnit<1>>,
    RuleMoveRight<State, CurUnit<2>>,
    RuleMoveRight<State, CurUnit<3>>,
    RuleMoveRight<State, RamEnd>,
    RuleMoveRight<State, OutputBegin>
>;

using InputRules = ConcatenateRules<
    RuleList<
        RuleMoveRight<InputCharStart, Command<'+'>>,
        RuleMoveRight<InputCharStart, Command<'-'>>,
        RuleMoveRight<InputCharStart, Command<']'>>,
        RuleMoveRight<InputCharStart, Command<'['>>,
        RuleMoveRight<InputCharStart, Command<'.'>>,
        RuleMoveRight<InputCharStart, Command<','>>,
        RuleMoveRight<InputCharStart, Command<'>'>>,
        RuleMoveRight<InputCharStart, Command<'<'>>
    >,
    RuleList<
        RuleMoveRight<InputCharStart, CurCommand<'+'>>,
        RuleMoveRight<InputCharStart, CurCommand<'-'>>,
        RuleMoveRight<InputCharStart, CurCommand<']'>>,
        RuleMoveRight<InputCharStart, CurCommand<'['>>,
        RuleMoveRight<InputCharStart, CurCommand<'.'>>,
        RuleMoveRight<InputCharStart, CurCommand<','>>,
        RuleMoveRight<InputCharStart, CurCommand<'>'>>,
        RuleMoveRight<InputCharStart, CurCommand<'<'>>
    >,
    RuleList<
        RuleMoveRight<InputCharStart, CodeEnd>,
        RuleMoveRight<InputCharStart, InputBegin>
    >,
    RuleList<
        Rule<InputCharStart, Unit<0>, InputChar<0>, InputBegin, Stay>,
        Rule<InputCharStart, Unit<1>, InputChar<1>, InputBegin, Stay>,
        Rule<InputCharStart, Unit<2>, InputChar<2>, InputBegin, Stay>,
        Rule<InputCharStart, Unit<3>, InputChar<3>, InputBegin, Stay>
    >,
    FindCurrentChar<InputChar<0>>,
    FindCurrentChar<InputChar<1>>,
    FindCurrentChar<InputChar<2>>,
    FindCurrentChar<InputChar<3>>,
    RuleList<
        Rule<InputChar<0>, CurUnit<0>, ReturnToCommand, CurUnit<0>, Stay>,
        Rule<InputChar<0>, CurUnit<1>, ReturnToCommand, CurUnit<0>, Stay>,
        Rule<InputChar<0>, CurUnit<2>, ReturnToCommand, CurUnit<0>, Stay>,
        Rule<InputChar<0>, CurUnit<3>, ReturnToCommand, CurUnit<0>, Stay>,
        Rule<InputChar<1>, CurUnit<0>, ReturnToCommand, CurUnit<1>, Stay>,
        Rule<InputChar<1>, CurUnit<1>, ReturnToCommand, CurUnit<1>, Stay>,
        Rule<InputChar<1>, CurUnit<2>, ReturnToCommand, CurUnit<1>, Stay>,
        Rule<InputChar<1>, CurUnit<3>, ReturnToCommand, CurUnit<1>, Stay>,
        Rule<InputChar<2>, CurUnit<0>, ReturnToCommand, CurUnit<2>, Stay>,
        Rule<InputChar<2>, CurUnit<1>, ReturnToCommand, CurUnit<2>, Stay>,
        Rule<InputChar<2>, CurUnit<2>, ReturnToCommand, CurUnit<2>, Stay>,
        Rule<InputChar<2>, CurUnit<3>, ReturnToCommand, CurUnit<2>, Stay>,
        Rule<InputChar<3>, CurUnit<0>, ReturnToCommand, CurUnit<3>, Stay>,
        Rule<InputChar<3>, CurUnit<1>, ReturnToCommand, CurUnit<3>, Stay>,
        Rule<InputChar<3>, CurUnit<2>, ReturnToCommand, CurUnit<3>, Stay>,
        Rule<InputChar<3>, CurUnit<3>, ReturnToCommand, CurUnit<3>, Stay>
    >
>::rules;

using OutputRules = ConcatenateRules<
    FindCurrentChar<OutputCharStart>,
    RuleList<
        Rule<OutputCharStart, CurUnit<0>, OutputChar<0>, CurUnit<0>, Stay>,
        Rule<OutputCharStart, CurUnit<1>, OutputChar<1>, CurUnit<1>, Stay>,
        Rule<OutputCharStart, CurUnit<2>, OutputChar<2>, CurUnit<2>, Stay>,
        Rule<OutputCharStart, CurUnit<3>, OutputChar<3>, CurUnit<3>, Stay>
    >,
    FindOutputEnd<OutputChar<0>>,
    FindOutputEnd<OutputChar<1>>,
    FindOutputEnd<OutputChar<2>>,
    FindOutputEnd<OutputChar<3>>,
    RuleList<
        Rule<OutputChar<0>, OutputEnd, SetOutputEnd, Unit<0>, MoveRight>,
        Rule<OutputChar<1>, OutputEnd, SetOutputEnd, Unit<1>, MoveRight>,
        Rule<OutputChar<2>, OutputEnd, SetOutputEnd, Unit<2>, MoveRight>,
        Rule<OutputChar<3>, OutputEnd, SetOutputEnd, Unit<3>, MoveRight>
    >
>::rules;

using SetoutputEndRules = RuleList<
    Rule<SetOutputEnd, Void, ReturnToCommand, OutputEnd, Stay>
>;

using CircleRules = ConcatenateRules<
    FindCurrentChar<CircleStart>,
    RuleList<
        Rule<CircleStart, CurUnit<0>, Circle<false>, CurUnit<0>, Stay>,
        Rule<CircleStart, CurUnit<1>, Circle<true>, CurUnit<1>, Stay>,
        Rule<CircleStart, CurUnit<2>, Circle<true>, CurUnit<2>, Stay>,
        Rule<CircleStart, CurUnit<3>, Circle<true>, CurUnit<3>, Stay>
    >,
    FindCurrentCommandRules<Circle<false>>,
    FindCurrentCommandRules<Circle<true>>,
    RuleList<
        Rule<Circle<false>, CurCommand<']'>, NextCommand, CurCommand<']'>, Stay>,
        Rule<Circle<true>, CurCommand<']'>, FindOpenBracket, CurCommand<']'>, MoveLeft>,
        Rule<Circle<false>, CurCommand<'['>, FindCloseBracket, CurCommand<'['>, MoveRight>,
        Rule<Circle<true>, CurCommand<'['>, NextCommand, CurCommand<'['>, Stay>
    >,
    RuleList<
        RuleMoveLeft<FindOpenBracket, Command<'+'>>,
        RuleMoveLeft<FindOpenBracket, Command<'-'>>,
        RuleMoveLeft<FindOpenBracket, Command<'>'>>,
        RuleMoveLeft<FindOpenBracket, Command<'<'>>,
        RuleMoveLeft<FindOpenBracket, Command<'.'>>,
        RuleMoveLeft<FindOpenBracket, Command<','>>,
        RuleMoveLeft<FindOpenBracket, Command<'('>>,
        Rule<FindOpenBracket, Command<'['>, ReturnToCloseBracket, CurCommand<'['>, MoveRight>,
        Rule<FindOpenBracket, Command<']'>, MarkOpenBracket, Command<')'>, MoveLeft>
    >,
    RuleList<
        RuleMoveRight<ReturnToCloseBracket, Command<'+'>>,
        RuleMoveRight<ReturnToCloseBracket, Command<'-'>>,
        RuleMoveRight<ReturnToCloseBracket, Command<'<'>>,
        RuleMoveRight<ReturnToCloseBracket, Command<'>'>>,
        RuleMoveRight<ReturnToCloseBracket, Command<'.'>>,
        RuleMoveRight<ReturnToCloseBracket, Command<','>>,
        Rule<ReturnToCloseBracket, Command<'('>, ReturnToCloseBracket, Command<'['>, MoveRight>,
        Rule<ReturnToCloseBracket, Command<')'>, ReturnToCloseBracket, Command<']'>, MoveRight>,
        Rule<ReturnToCloseBracket, CurCommand<']'>, ReturnToCommand, Command<']'>, Stay>
    >,
    RuleList<
        RuleMoveLeft<MarkOpenBracket, Command<'+'>>,
        RuleMoveLeft<MarkOpenBracket, Command<'-'>>,
        RuleMoveLeft<MarkOpenBracket, Command<'>'>>,
        RuleMoveLeft<MarkOpenBracket, Command<'<'>>,
        RuleMoveLeft<MarkOpenBracket, Command<','>>,
        RuleMoveLeft<MarkOpenBracket, Command<'.'>>,
        RuleMoveLeft<MarkOpenBracket, Command<']'>>,
        RuleMoveLeft<MarkOpenBracket, Command<'('>>,
        Rule<MarkOpenBracket, Command<'['>, ReturnToMarkedCloseBracket, Command<'('>, Stay>
    >,
    RuleList<
        RuleMoveRight<ReturnToMarkedCloseBracket, Command<'+'>>,
        RuleMoveRight<ReturnToMarkedCloseBracket, Command<'-'>>,
        RuleMoveRight<ReturnToMarkedCloseBracket, Command<'.'>>,
        RuleMoveRight<ReturnToMarkedCloseBracket, Command<','>>,
        RuleMoveRight<ReturnToMarkedCloseBracket, Command<'>'>>,
        RuleMoveRight<ReturnToMarkedCloseBracket, Command<'<'>>,
        RuleMoveRight<ReturnToMarkedCloseBracket, Command<'('>>,
        Rule<ReturnToMarkedCloseBracket, Command<')'>, FindOpenBracket, Command<')'>, MoveLeft>
    >,
    RuleList<
        RuleMoveRight<FindCloseBracket, Command<'+'>>,
        RuleMoveRight<FindCloseBracket, Command<'-'>>,
        RuleMoveRight<FindCloseBracket, Command<'>'>>,
        RuleMoveRight<FindCloseBracket, Command<'<'>>,
        RuleMoveRight<FindCloseBracket, Command<'.'>>,
        RuleMoveRight<FindCloseBracket, Command<','>>,
        RuleMoveRight<FindCloseBracket, Command<')'>>,
        Rule<FindCloseBracket, Command<']'>, ReturnToOpenBracket, CurCommand<']'>, MoveLeft>,
        Rule<FindCloseBracket, Command<'['>, MarkCloseBracket, Command<'('>, MoveRight>
    >,
    RuleList<
        RuleMoveLeft<ReturnToOpenBracket, Command<'+'>>,
        RuleMoveLeft<ReturnToOpenBracket, Command<'-'>>,
        RuleMoveLeft<ReturnToOpenBracket, Command<'<'>>,
        RuleMoveLeft<ReturnToOpenBracket, Command<'>'>>,
        RuleMoveLeft<ReturnToOpenBracket, Command<'.'>>,
        RuleMoveLeft<ReturnToOpenBracket, Command<','>>,
        Rule<ReturnToOpenBracket, Command<')'>, ReturnToOpenBracket, Command<']'>, MoveLeft>,
        Rule<ReturnToOpenBracket, Command<'('>, ReturnToOpenBracket, Command<'['>, MoveLeft>,
        Rule<ReturnToOpenBracket, CurCommand<'['>, ReturnToCommandRight, Command<'['>, Stay>
    >,
    RuleList<
        RuleMoveRight<MarkCloseBracket, Command<'+'>>,
        RuleMoveRight<MarkCloseBracket, Command<'-'>>,
        RuleMoveRight<MarkCloseBracket, Command<'>'>>,
        RuleMoveRight<MarkCloseBracket, Command<'<'>>,
        RuleMoveRight<MarkCloseBracket, Command<','>>,
        RuleMoveRight<MarkCloseBracket, Command<'.'>>,
        RuleMoveRight<MarkCloseBracket, Command<'['>>,
        RuleMoveRight<MarkCloseBracket, Command<')'>>,
        Rule<MarkCloseBracket, Command<']'>, ReturnToMarkedOpenBracket, Command<')'>, Stay>
    >,
    RuleList<
        RuleMoveLeft<ReturnToMarkedOpenBracket, Command<'+'>>,
        RuleMoveLeft<ReturnToMarkedOpenBracket, Command<'-'>>,
        RuleMoveLeft<ReturnToMarkedOpenBracket, Command<'.'>>,
        RuleMoveLeft<ReturnToMarkedOpenBracket, Command<','>>,
        RuleMoveLeft<ReturnToMarkedOpenBracket, Command<'>'>>,
        RuleMoveLeft<ReturnToMarkedOpenBracket, Command<'<'>>,
        RuleMoveLeft<ReturnToMarkedOpenBracket, Command<')'>>,
        Rule<ReturnToMarkedOpenBracket, Command<'('>, FindCloseBracket, Command<'('>, MoveRight>
    >
>::rules;

using DoCommandRules = RuleList<
    Rule<DoCommand, CurCommand<'+'>, AddToCurCell, CurCommand<'+'>, Stay>,
    Rule<DoCommand, CurCommand<'-'>, SubToCurCell, CurCommand<'-'>, Stay>,
    Rule<DoCommand, CurCommand<'>'>, MoveRightCurChar, CurCommand<'>'>, Stay>,
    Rule<DoCommand, CurCommand<'<'>, MoveLeftCurChar, CurCommand<'<'>, Stay>,
    Rule<DoCommand, CurCommand<'.'>, OutputCharStart, CurCommand<'.'>, Stay>,
    Rule<DoCommand, CurCommand<','>, InputCharStart, CurCommand<','>, Stay>,
    Rule<DoCommand, CurCommand<'['>, CircleStart, CurCommand<'['>, Stay>,
    Rule<DoCommand, CurCommand<']'>, CircleStart, CurCommand<']'>, Stay>
>;
