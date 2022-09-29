lexer grammar BLex;

//  keyword
Void : 'void';
Int : 'int';
Float : 'float';
Double : 'double';
If : 'if';
Else : 'else';
For : 'for';
Do : 'do';
While : 'while';
Break : 'break';
Continue : 'continue';

//  seperator
SEP_LParen : '(';
SEP_RParen : ')';
SEP_LBrace : '{';
SEP_RBrace : '}';
SEP_LBrkt : '[';
SEP_RBrkt : ']';
SEP_Semicolon : ';';

//  operator
OP_Minus : '-';
OP_Bang : '!';
OP_Add : '+';
OP_Mul : '*';
OP_Div : '/';
OP_Mod : '%';
OP_LAnd : '&&';
OP_LOR : '||';
OP_Assign : '=';
OP_EQ : '==';
OP_NEQ : '!=';
OP_LT : '<';
OP_LE : '<=';
OP_GT : '>';
OP_GE : '>=';

//  Some element
Literal_Int : [0-9]+;
Identifier : [a-zA-Z_][a-zA-Z_0-9]*;

//  Some char to skip
WS : [ \t\r\n] -> skip;
Line_Comment : '//'.*?'\n';
Comment : '/*'.*?'*/' ;