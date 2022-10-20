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