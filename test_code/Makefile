CXX = clang
INCLUDE = -I./include
FLAGS = -emit-ast

TARGETS = ClassA.ast ClassB.ast

all: ${TARGETS}

${TARGETS}: %.ast: %.cc
	$(CXX) ${FLAGS} ${INCLUDE} $<


.PHONY: clean
clean:
	rm *.ast
