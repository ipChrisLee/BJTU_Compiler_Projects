grammar BGrammar;

import BLex;

compUnit : (stmt|decl)* EOF;

decl : btype Identifier ('[' constExp ']');

constExp : Literal_Int;

btype : Int | Float;

stmt : 'a';


