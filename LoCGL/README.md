# LoCGL

Lots of Compiler Generator Libraries.

Here lists some useful libraries for compiler generator.

# Format of grammar file

Every line is something like "`RuleName` `->` `RuleDef`" or "`|` `RuleDef`".

Like

```text
CompUnit -> V Eq E
E -> T E_
E_ -> A T E_
	| $
```

`CompUnit` is always the beginning state.

`RuleName` consists of upper letters and lower letters and underline.

`$` means $\epsilon$

# ll1

For LL(1) analyzer, we assume that:

* The grammar you input should not contain left-recursive.
* The grammar is simplified.
* For now, epsilon is not terminator.