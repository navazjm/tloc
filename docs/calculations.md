# Calculations

*Last Updated: 2024-08-24* 

This documentation will attempt to explain how `tloc` parse each individual file,
in an attempt to calculate blank lines, comment lines, and source code lines. If
after reading this documentation, you still have any questions or concerns, feel 
free to start a [discussion](https://github.com/navazjm/tloc/discussions).

## Overiew

In order, `tloc` will perform the following operations:

1. Trim leading and trailing whitespace from the line

1. If and only if the line is empty or an espace sequence representing whitespace, 
it is counted as a blank line.

1. If and only if the line `starts` with characters 
indicating the start of a multiline comment block does tloc flag that it has found 
the beginning of a multiline comment.
    - Unless the line is counted as a blank line, `tloc` will count all subsequent 
    lines as a comment line until a line `ends` with characters indicating the 
    end of a multiline comment. This includes the line that flags the beginning 
    of a multiline comment block.
        
1. If and only if the line `begins` with characters that denote a single-line 
comment, it is counted as a comment.

1. Any line that does not meet the above conditions is counted 
as source code.

## Examples

### Example 1

Given the following main.c file

```c
#include <stdio.h>

/*
    Returns the sum of two integers

    @param a -> int
    @param b -> int
*/
int calculate_sum(int a, int b) {
    return a + b; // add a + b
}

int main(void) {

    // todo: get user input from stdin
    int num1 = 10;
    int num2 = 5;

    printf("%i + %i = %i\n", num1, num2, calculate_sum(num1, num2));

    return 0;
}
```

Breakdown:

Line 01: `#include <stdio.h>\n` -> source code \
Line 02: `\n` -> blank line \
Line 03: `/*\n` -> comment \
Line 04: `Returns the sum of two integers\n` -> comment \
Line 05: `\n` -> blank line, even though it is wihin a multline comment block \
Line 06: `@param a -> int\n` -> comment \
Line 07: `@param b -> int\n` -> comment \
Line 08: `*/\n` -> comment \
Line 09: `int calculate_sum(int a, int b) {\n` -> source code \
Line 10: `return a + b; // add a + b\n` -> source code since comment is at end of line. \
Line 11: `}\n` -> source code \
Line 12: `\n` -> blank line \
Line 13`int main(void) {\n` -> source code \
Line 14: `\n` -> blank line \
Line 15: `// todo: get user input from stdin\n` -> comment \
Line 16: `int num1 = 10;\n` -> source code \
Line 17: `int num2 = 5;\n` -> source code \
Line 18: `\n` -> blank line \
Line 19: `printf("%i + %i = %i\n", num1, num2, calculate_sum(num1, num2));\n` -> source code \
Line 20: `\n` -> blank line \
Line 21: `return 0;\n` -> source code \
Line 22: `}\n` -> source code

### Example 2

Give the following `c` block od code.

```c 
  int a = 10; /* this is
  a valid
  code block */ int b = 2;

  printf("%i + %i = %i\n", a, b, a + b); // print sum of a,b to stdout
```

Breakdown:

Line 01: `int a = 10; /* this is\n` -> source code, does NOT flag beginning of multiline 
comment since it is found in the middle of the line \
Line 02: `a valid\n` -> source code, since above line does not flag beginning of multiline comment \
Line 03: `code block */ int b = 2;\n` -> source code, since start of multiline comment was not flagged \
Line 04: `\n` -> blank line \
line 05: `printf("%i + %i = %i\n", a, b, a + b); // print sum of a,b to stdout ` -> source
code since comment is not found at beginning of line

### Example 3

Give the following `c` block od code.

```c 
  int a = 10; 
  /* this is
  a valid
  code block */ int b = 2;

  printf("%i + %i = %i\n", a, b, a + b);
```

Breakdown:

Line 01: `int a = 10;\n` -> source code \
Line 02: `/* this is\n` -> comment, flags start of multiline comment since `/*` is found at beginning of line \
Line 03: `a valid\n` -> comment, within a multiline comment \
Line 04: `code block */ int b = 2;\n` -> comment, does NOT flag end of multiline
comment since `*/` was not found at end of line \
Line 05: `\n` -> blank line \
line 06: `printf("%i + %i = %i\n", a, b, a + b);\n` -> comment, since end of multiline
comment was never flagged.

Even though both example 2 and 3 are valid `C` code and does compile, if you write a multiline comment
like this, then I am not sorry `tloc` does not catch it as a comment O_o


