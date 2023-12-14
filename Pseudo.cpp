#include <cctype>
#include <cstdio>
#include <cstdlib>

#include <string>


enum Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,
  tok_print = -6,
  tok_input = -7,
  tok_if = -8,
  tok_then = -9,
  tok_else = -10,
  tok_elseif = -11,
  tok_for = -12,
  tok_while = -13,
  tok_next = -14,
  tok_until = -15,
  tok_do = -16,
  tok_declare = -17,
  tok_return = -18,
  tok_and = -19,
  tok_or = -20,
  tok_not = -21,

  // primary
  tok_identifier = -4,
  tok_number = -5,
};

static std::string IdentifierStr;
static double NumVal;

static int gettok() {

  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar)) {
    LastChar = getchar();
  }

  if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar()))) {
      IdentifierStr += LastChar;
    }

    if (IdentifierStr == "PROCEDURE") {
      return tok_def;
    }
    if (IdentifierStr == "OUTPUT") {
      return tok_print;
    }

    if (IdentifierStr == "EXTERN") {
      return tok_extern;
    }

    if (IdentifierStr == "INPUT") {
      return tok_input;
    }

    if (IdentifierStr == "IF") {
      return tok_if;
    }

    if (IdentifierStr == "THEN") {
      return tok_then;
    }

    if (IdentifierStr == "ELSE") {
      return tok_else;
    }
    if (IdentifierStr == "ELSEIF") {
      return tok_elseif;
    }

    if (IdentifierStr == "FOR") {
      return tok_for;
    }

    if (IdentifierStr == "WHILE") {
      return tok_while;
    }

    if (IdentifierStr == "NEXT") {
      return tok_next;
    }

    if (IdentifierStr == "UNTIL") {
      return tok_until;
    }

    if (IdentifierStr == "DO") {
      return tok_do;
    }

    if (IdentifierStr == "DECLARE") {
      return tok_declare;
    }

    if (IdentifierStr == "RETURN") {
      return tok_return;
    }

    if (IdentifierStr == "AND") {
      return tok_and;
    }

    if (IdentifierStr == "OR") {
      return tok_or;
    }

    if (IdentifierStr == "NOT") {
      return tok_not;
    }

    return tok_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }

  if (LastChar == '#') {
    // Comment until end of line.
    do {
      LastChar = getchar();
    } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF) {
      return gettok();
    }
  }

  // Check for end of file.  Don't eat the EOF.
  if (LastChar == EOF) {
    return tok_eof;
  }

  // Otherwise, just return the character as its ascii value.
  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}
