About: 

    Infix to postfix translator for arithmetic expressions consisting of 
    digits separated by the operators '+', '-', '/' and '*' with possible 
    use of parentheses to specify the precedence of operations. The operators 
    '*' and '/' have higher precedence than '+' and '-'.

    Invalid arithmetic expressions are not transpiled and exceptions are 
    thrown to the standard diagnostic stream indicating the position number 
    in the line where the error occurred.

    To apply predictive analysis to the source string, the left-recursive 
    grammar was adapted by converting it to a right-recursive one.

Initial grammar (left-recursive):

    expr -> expr + term | expr - term | term;
    term -> term * fact | term / fact | fact;
    fact -> ( expr ) | digit;
    digit -> 0 | 1 | ... | 9.

Initial translation scheme:

    expr -> expr + term {print('+')};
    expr -> expr - term {print('-')};
    expr -> term;

    term -> term * fact {print('*')};
    term -> term / fact {print('/')};
    term -> fact;

    fact -> ( expr );
    fact -> digit;

    digit -> 0 {print('0')};
    digit -> 1 {print('1')};
    ...
    digit -> 9 {print('9')}.

Adapted grammar (right-recursive):

    expr -> term r1;
    r1 -> + term r1 | - term r1 | null;

    term -> fact r2;
    r2 -> * fact r2 | / fact r2 | null;

    fact -> ( expr ) | digit;
    digit -> 0 | 1 | ... | 9.

Adapted translation scheme:

    expr -> term r1;
    r1 -> + term {print('+')} r1;
    r1 -> - term {print('-')} r1;
    r1 -> null;

    term -> fact r2;
    r2 -> * fact {print('*')} r2;
    r2 -> / fact {print('/')} r2;
    r2 -> null;

    fact -> ( expr );
    fact -> digit;

    digit -> 0 {print('0')};
    digit -> 1 {print('1')};
    ...
    digit -> 9 {print('9')}.

Examples:

    "1+2" -> "12+";
    "1+2*(3+4)" -> "1234+*+";
    "1+2)" -> "Syntax error: there is no '(' for ')' in position 4".

Usage:

    executable <input file> [<output file>]

    The input file must contain a valid text expression string terminated by EOF only. 

Compilaton and linking:

    gcc -Wall main.c src/stream.c src/stack.c src/translator.c -o bin/main
