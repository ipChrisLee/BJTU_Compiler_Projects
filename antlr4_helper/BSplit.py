import sys

import antlr4.tree.Tree
from antlr4 import *
from BSplitter.BLexSplitterVisitor import BLexSplitterVisitor
from BSplitter.BLexSplitterLexer import BLexSplitterLexer
from BSplitter.BLexSplitterParser import BLexSplitterParser


class PrintVisitor(BLexSplitterVisitor):
	def visitItem(self, ctx: BLexSplitterParser.ItemContext):
		for s in ctx.getChildren():
			s: antlr4.tree.Tree.TerminalNodeImpl = s
			print(
				f'{BLexSplitterLexer.symbolicNames[s.symbol.type]} : {s.getText()}')


def main(argv):
	input_stream = FileStream(argv[1])
	lexer = BLexSplitterLexer(input_stream)
	stream = CommonTokenStream(lexer)
	parser = BLexSplitterParser(stream)
	tree = parser.compUnit()
	visitor = PrintVisitor()
	tree.accept(visitor)


if __name__ == '__main__':
	main(sys.argv)
