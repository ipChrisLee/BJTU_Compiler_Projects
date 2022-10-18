# LiaLEX Is Another LEX

## Format of lialex file

Every line is something like "`RuleType` `RuleName` = `Rule`" or "`/` `some comment`".

`RuleType` is one of `+`, `-` and `@`. `+` means explicit rule and `-` means implicit rule.

The token will be one of explicit rules, and implicit rule can only be used as middle rule.

`@` is now legal now. I will add this feature later.

`/` indicates the beginning of the comment line.