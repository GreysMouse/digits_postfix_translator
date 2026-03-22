#include "../include/stack.h"
#include "../include/stream.h"
#include "../include/translator.h"
#include "../macro/exceptions.h"
#include <stdio.h>
#include <stdlib.h>

static void expr(FILE *input, stack *result, int lpar, long *ppos);
static void term(FILE *input, stack *result, int lpar, long *ppos);
static void fact(FILE *input, stack *result, long *ppos);
static void rpar(FILE *input, stack *result, long *ppos);

void translate(FILE *input, stack *result)
{
    long pos = 0;
    int peek = file_pull_c(input, &pos);

    if (peek == EOF) {
        NO_INPUT_DATA_MSG();
    }

    file_push_c(input, peek, &pos);

    fact(input, result, &pos);
    expr(input, result, 0, &pos);

    stack_push_c(result, '\0');
}

static void expr(FILE *input, stack *result, int lpar, long *ppos)
{
    int peek;

    while ((peek = file_pull_c(input, ppos)) != EOF) {
        if (peek == '+' || peek == '-') {
            fact(input, result, ppos);
            term(input, result, lpar, ppos);
            stack_push_c(result, (char)peek);
        } else if (peek == '*' || peek == '/') {
            file_push_c(input, peek, ppos);
            term(input, result, lpar, ppos);
        } else if (peek == ')') {
            if (!lpar) {
                SYNTAX_LPAREN_ERR(*ppos);
            }
            file_push_c(input, peek, ppos);
            break;
        } else {
            SYNTAX_INVAL_OP_ERR(*ppos, peek);
        };
    }
}

static void term(FILE *input, stack *result, int lpar, long *ppos)
{
    int peek;

    while ((peek = file_pull_c(input, ppos)) != EOF) {
        if (peek == '*' || peek == '/') {
            fact(input, result, ppos);
            stack_push_c(result, (char)peek);
        } else if (peek == '+' || peek == '-') {
            file_push_c(input, peek, ppos);
            break;
        } else if (peek == ')') {
            if (!lpar) {
                SYNTAX_LPAREN_ERR(*ppos);
            }
            file_push_c(input, peek, ppos);
            break;
        } else {
            SYNTAX_INVAL_OP_ERR(*ppos, peek);
        };
    }
}

static void fact(FILE *input, stack *result, long *ppos)
{
    int peek = file_pull_c(input, ppos);

    if (peek >= '0' && peek <= '9') {
        stack_push_c(result, peek);
    } else if (peek == '(') {
        fact(input, result, ppos);
        expr(input, result, 1, ppos);
        rpar(input, result, ppos);
    } else if (peek == EOF) {
        SYNTAX_NO_OPND_ERR(*ppos + 1);
    } else {
        SYNTAX_INVAL_OPND_ERR(*ppos, peek);
    }
}

static void rpar(FILE *input, stack *result, long *ppos)
{
    int peek = file_pull_c(input, ppos);

    if (peek != ')') {
        SYNTAX_RPAREN_ERR(*ppos + 1);
    }
}