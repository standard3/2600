# Keywords
# --------------------------
# auto         double      int        struct
# break        else        long       switch
# case         enum        register   typedef
# char         extern      return     union
# const        float       short      unsigned
# continue     for         signed     void
# default      goto        sizeof     volatile
# do           if          static     while

# Identifiers
# --------------------------
# They must begin with a letter or underscore(_).
# They must consist of only letters, digits, or underscore. No other special character is allowed.
# It should not be a keyword.
# It must not contain white space.
# It should be up to 31 characters long as only the first 31 characters are significant.

# Constants
# --------------------------
# const int c_var = 20;
# const int* const ptr = &c_var;

# Strings
# --------------------------
# char string[20] = {‘g’, ’e’, ‘e’, ‘k’, ‘s’, ‘f’, ‘o’, ‘r’, ‘g’, ’e’, ‘e’, ‘k’, ‘s’, ‘\0’};
# char string[20] = “geeksforgeeks”;
# char string [] = “geeksforgeeks”;

# Symbols
# --------------------------
# Brackets[]: Opening and closing brackets are used as array element references. These indicate single and multidimensional subscripts.
# Parentheses(): These special symbols are used to indicate function calls and function parameters.
# Braces{}: These opening and ending curly braces mark the start and end of a block of code containing more than one executable statement.
# Comma (, ): It is used to separate more than one statement like for separating parameters in function calls.
# Colon(:): It is an operator that essentially invokes something called an initialization list.
# Semicolon(;): It is known as a statement terminator.  It indicates the end of one logical entity. That’s why each individual statement must be ended with a semicolon.
# Asterisk (*): It is used to create a pointer variable and for the multiplication of variables.
# Assignment operator(=): It is used to assign values and for logical operation validation.
# Pre-processor (#): The preprocessor is a macro processor that is used automatically by the compiler to transform your program before actual compilation.
# Period (.): Used to access members of a structure or union.
# Tilde(~): Used as a destructor to free some space from memory.

# Operators
# --------------------------
# Unary Operators: Those operators that require only a single operand to act upon are known as unary operators.For Example increment and decrement operators
# Binary Operators: Those operators that require two operands to act upon are called binary operators. Binary operators can further are classified into:
#
    # Arithmetic operators
    # Relational Operators
    # Logical Operators
    # Assignment Operators
    # Bitwise Operator

# Ternary Operator: The operator that requires three operands to act upon is called the ternary operator. Conditional Operator(?) is also called the ternary operator.

# Spaces and comments
# --------------------------

# syntax (?P<nom_groupe>pattern)

LEXEMES = r"""(?umx)
    (?P<keywords>
        ( auto | break | case | char | const | continue | default | do  | double
        | else | enum | extern | float | for | goto | if | int | long
        | register | return | short | signed | sizeof | static | struct | switch
        | typedef | union | unsigned | void | volatile | while )
    \b)
    | (?P<constants>
        \' (?: \\. | [^\'] ) *\'
        | ( 0[xXbB][0-9a-zA-Z]+ )
        | (?P<floats>
            \d+\.\d* | \d*\.\d+
        )
        (
            [eE][-+]?\d+ | [jJiIfFlL]
        )?
        | (?P<integers>
            \d+[u+U+][l+L] | \d+
    ))
    | (?P<identifiers>
        [a-zA-Z_]\w*
    )
    | (?P<strings>
        \"(?:
            \\. | [^\"]
        ) *\"
    )
    | (?P<operators>
        \|\= | \+\= | -\= | /\= | \*\= | <\= | >\= | \=\= | !\= | <<\= | >>\=
        | % | << | >> | < | > | \.\.\. | \. | -> | \+\+ | -- | \+ | - | ~ | && | \^ | \| | & | \|\| | \? )
    | (?P<comments>
        //[^\n]* | /\* (?: . | [\r\n] ) *?\*/ )
    | (?P<symbols>
        \[ | \] | \( | \) | \{ | \} | \, | \: | \; | \* | \= | \# | \. | \~ )
    | (?P<spaces> \s+ )
    | (?P<unknown> . )
"""