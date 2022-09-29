#!/bin/zsh
#  copy from BLex to BLexSplitter and replace.
antlr4 -Dlanguage=Python3 BLexSplitter.g4 -visitor -o BSplitter