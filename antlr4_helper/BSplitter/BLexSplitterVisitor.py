# Generated from BLexSplitter.g4 by ANTLR 4.11.1
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .BLexSplitterParser import BLexSplitterParser
else:
    from BLexSplitterParser import BLexSplitterParser

# This class defines a complete generic visitor for a parse tree produced by BLexSplitterParser.

class BLexSplitterVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by BLexSplitterParser#compUnit.
    def visitCompUnit(self, ctx:BLexSplitterParser.CompUnitContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by BLexSplitterParser#item.
    def visitItem(self, ctx:BLexSplitterParser.ItemContext):
        return self.visitChildren(ctx)



del BLexSplitterParser