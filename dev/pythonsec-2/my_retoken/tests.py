import my_retoken as m

lex = m.Lexer()

def test_file(path):
    with open(path) as testfile:
        content = testfile.read()
        res = lex.get_tokens(content)

        for match in res:
            if match[0] == 'spaces':
                continue
            print(match)

print("Commentaires")
test_file("tests/comments")

print("\nConstants")
test_file("tests/constants")

print("\nIdentifiers")
test_file("tests/identifiers")

print("\nKeywords")
test_file("tests/keywords")

print("\nOperators")
test_file("tests/operators")

print("\nStrings")
test_file("tests/strings")

print("\nSymbols")
test_file("tests/symbols")