# Generated from BLexSplitter.g4 by ANTLR 4.11.1
# encoding: utf-8
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
	from typing import TextIO
else:
	from typing.io import TextIO

def serializedATN():
    return [
        4,1,38,15,2,0,7,0,2,1,7,1,1,0,5,0,6,8,0,10,0,12,0,9,9,0,1,0,1,0,
        1,1,1,1,1,1,0,0,2,0,2,0,1,1,0,1,38,13,0,7,1,0,0,0,2,12,1,0,0,0,4,
        6,3,2,1,0,5,4,1,0,0,0,6,9,1,0,0,0,7,5,1,0,0,0,7,8,1,0,0,0,8,10,1,
        0,0,0,9,7,1,0,0,0,10,11,5,0,0,1,11,1,1,0,0,0,12,13,7,0,0,0,13,3,
        1,0,0,0,1,7
    ]

class BLexSplitterParser ( Parser ):

    grammarFileName = "BLexSplitter.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [ "<INVALID>", "'void'", "'int'", "'float'", "'double'", 
                     "'if'", "'else'", "'for'", "'do'", "'while'", "'break'", 
                     "'continue'", "'('", "')'", "'{'", "'}'", "'['", "']'", 
                     "';'", "'-'", "'!'", "'+'", "'*'", "'/'", "'%'", "'&&'", 
                     "'||'", "'='", "'=='", "'!='", "'<'", "'<='", "'>'", 
                     "'>='" ]

    symbolicNames = [ "<INVALID>", "Void", "Int", "Float", "Double", "If", 
                      "Else", "For", "Do", "While", "Break", "Continue", 
                      "SEP_LParen", "SEP_RParen", "SEP_LBrace", "SEP_RBrace", 
                      "SEP_LBrkt", "SEP_RBrkt", "SEP_Semicolon", "OP_Minus", 
                      "OP_Bang", "OP_Add", "OP_Mul", "OP_Div", "OP_Mod", 
                      "OP_LAnd", "OP_LOR", "OP_Assign", "OP_EQ", "OP_NEQ", 
                      "OP_LT", "OP_LE", "OP_GT", "OP_GE", "Literal_Int", 
                      "Identifier", "WS", "Line_Comment", "Comment" ]

    RULE_compUnit = 0
    RULE_item = 1

    ruleNames =  [ "compUnit", "item" ]

    EOF = Token.EOF
    Void=1
    Int=2
    Float=3
    Double=4
    If=5
    Else=6
    For=7
    Do=8
    While=9
    Break=10
    Continue=11
    SEP_LParen=12
    SEP_RParen=13
    SEP_LBrace=14
    SEP_RBrace=15
    SEP_LBrkt=16
    SEP_RBrkt=17
    SEP_Semicolon=18
    OP_Minus=19
    OP_Bang=20
    OP_Add=21
    OP_Mul=22
    OP_Div=23
    OP_Mod=24
    OP_LAnd=25
    OP_LOR=26
    OP_Assign=27
    OP_EQ=28
    OP_NEQ=29
    OP_LT=30
    OP_LE=31
    OP_GT=32
    OP_GE=33
    Literal_Int=34
    Identifier=35
    WS=36
    Line_Comment=37
    Comment=38

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.11.1")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None




    class CompUnitContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def EOF(self):
            return self.getToken(BLexSplitterParser.EOF, 0)

        def item(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(BLexSplitterParser.ItemContext)
            else:
                return self.getTypedRuleContext(BLexSplitterParser.ItemContext,i)


        def getRuleIndex(self):
            return BLexSplitterParser.RULE_compUnit

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterCompUnit" ):
                listener.enterCompUnit(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitCompUnit" ):
                listener.exitCompUnit(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitCompUnit" ):
                return visitor.visitCompUnit(self)
            else:
                return visitor.visitChildren(self)




    def compUnit(self):

        localctx = BLexSplitterParser.CompUnitContext(self, self._ctx, self.state)
        self.enterRule(localctx, 0, self.RULE_compUnit)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 7
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while ((_la) & ~0x3f) == 0 and ((1 << _la) & 549755813886) != 0:
                self.state = 4
                self.item()
                self.state = 9
                self._errHandler.sync(self)
                _la = self._input.LA(1)

            self.state = 10
            self.match(BLexSplitterParser.EOF)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ItemContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def Void(self):
            return self.getToken(BLexSplitterParser.Void, 0)

        def Int(self):
            return self.getToken(BLexSplitterParser.Int, 0)

        def Float(self):
            return self.getToken(BLexSplitterParser.Float, 0)

        def Double(self):
            return self.getToken(BLexSplitterParser.Double, 0)

        def If(self):
            return self.getToken(BLexSplitterParser.If, 0)

        def Else(self):
            return self.getToken(BLexSplitterParser.Else, 0)

        def For(self):
            return self.getToken(BLexSplitterParser.For, 0)

        def Do(self):
            return self.getToken(BLexSplitterParser.Do, 0)

        def While(self):
            return self.getToken(BLexSplitterParser.While, 0)

        def Break(self):
            return self.getToken(BLexSplitterParser.Break, 0)

        def Continue(self):
            return self.getToken(BLexSplitterParser.Continue, 0)

        def SEP_LParen(self):
            return self.getToken(BLexSplitterParser.SEP_LParen, 0)

        def SEP_RParen(self):
            return self.getToken(BLexSplitterParser.SEP_RParen, 0)

        def SEP_LBrace(self):
            return self.getToken(BLexSplitterParser.SEP_LBrace, 0)

        def SEP_RBrace(self):
            return self.getToken(BLexSplitterParser.SEP_RBrace, 0)

        def SEP_LBrkt(self):
            return self.getToken(BLexSplitterParser.SEP_LBrkt, 0)

        def SEP_RBrkt(self):
            return self.getToken(BLexSplitterParser.SEP_RBrkt, 0)

        def SEP_Semicolon(self):
            return self.getToken(BLexSplitterParser.SEP_Semicolon, 0)

        def OP_Minus(self):
            return self.getToken(BLexSplitterParser.OP_Minus, 0)

        def OP_Bang(self):
            return self.getToken(BLexSplitterParser.OP_Bang, 0)

        def OP_Add(self):
            return self.getToken(BLexSplitterParser.OP_Add, 0)

        def OP_Mul(self):
            return self.getToken(BLexSplitterParser.OP_Mul, 0)

        def OP_Div(self):
            return self.getToken(BLexSplitterParser.OP_Div, 0)

        def OP_Mod(self):
            return self.getToken(BLexSplitterParser.OP_Mod, 0)

        def OP_LAnd(self):
            return self.getToken(BLexSplitterParser.OP_LAnd, 0)

        def OP_LOR(self):
            return self.getToken(BLexSplitterParser.OP_LOR, 0)

        def OP_Assign(self):
            return self.getToken(BLexSplitterParser.OP_Assign, 0)

        def OP_EQ(self):
            return self.getToken(BLexSplitterParser.OP_EQ, 0)

        def OP_NEQ(self):
            return self.getToken(BLexSplitterParser.OP_NEQ, 0)

        def OP_LT(self):
            return self.getToken(BLexSplitterParser.OP_LT, 0)

        def OP_LE(self):
            return self.getToken(BLexSplitterParser.OP_LE, 0)

        def OP_GT(self):
            return self.getToken(BLexSplitterParser.OP_GT, 0)

        def OP_GE(self):
            return self.getToken(BLexSplitterParser.OP_GE, 0)

        def Literal_Int(self):
            return self.getToken(BLexSplitterParser.Literal_Int, 0)

        def Identifier(self):
            return self.getToken(BLexSplitterParser.Identifier, 0)

        def WS(self):
            return self.getToken(BLexSplitterParser.WS, 0)

        def Line_Comment(self):
            return self.getToken(BLexSplitterParser.Line_Comment, 0)

        def Comment(self):
            return self.getToken(BLexSplitterParser.Comment, 0)

        def getRuleIndex(self):
            return BLexSplitterParser.RULE_item

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterItem" ):
                listener.enterItem(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitItem" ):
                listener.exitItem(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitItem" ):
                return visitor.visitItem(self)
            else:
                return visitor.visitChildren(self)




    def item(self):

        localctx = BLexSplitterParser.ItemContext(self, self._ctx, self.state)
        self.enterRule(localctx, 2, self.RULE_item)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 12
            _la = self._input.LA(1)
            if not(((_la) & ~0x3f) == 0 and ((1 << _la) & 549755813886) != 0):
                self._errHandler.recoverInline(self)
            else:
                self._errHandler.reportMatch(self)
                self.consume()
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx





