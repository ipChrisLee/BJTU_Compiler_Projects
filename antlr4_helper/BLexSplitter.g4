grammar BLexSplitter;

import BLex;

compUnit : item* EOF;
item : 
//  keyword
Void |
Int |
Float |
Double |
If |
Else |
For |
Do |
While |
Break |
Continue |

//  seperator
SEP_LParen |
SEP_RParen |
SEP_LBrace |
SEP_RBrace |
SEP_LBrkt |
SEP_RBrkt |
SEP_Semicolon |

//  operator
OP_Minus |
OP_Bang |
OP_Add |
OP_Mul |
OP_Div |
OP_Mod |
OP_LAnd |
OP_LOR |
OP_Assign |
OP_EQ |
OP_NEQ |
OP_LT |
OP_LE |
OP_GT |
OP_GE |

//  Some element
Literal_Int |
Identifier |

//  Some char to skip
WS |
Line_Comment |
Comment;
