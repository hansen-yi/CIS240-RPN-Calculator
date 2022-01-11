all: rpn.c stack.c
	clang -g -o rpn rpn.c stack.c
