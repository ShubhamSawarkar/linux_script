#ifndef SCANNER_H
#define SCANNER_H

#include "common.h"
#include "type/list.h"

enum TokenType {
  // Syntactical
  TOKEN_ERROR,
  TOKEN_LITERAL_NUMBER,
  TOKEN_LITERAL_STRING,
  TOKEN_IDENTIFIER,
  TOKEN_KEYWORD,
  TOKEN_BRACE_OPEN,
  TOKEN_BRACE_CLOSE,
  TOKEN_BRACKET_OPEN,
  TOKEN_BRACKET_CLOSE,

  // Arithmatic
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,

  // Assignment
  TOKEN_EQUAL,
  TOKEN_PLUS_EQUAL,
  TOKEN_MINUS_EQUAL,
  TOKEN_STAR_EQUAL,
  TOKEN_SLASH_EQUAL,

  // Equality Check
  TOKEN_EQUAL_EQUAL,
  TOKEN_NOT_EQUAL,
  
  // Comparison
  TOKEN_GREATER_THAN,
  TOKEN_LESS_THAN,
  TOKEN_GREATER_THAN_EQUAL,
  TOKEN_LESS_THAN_EQUAL
};

typedef enum TokenType TokenType;

struct Token {
  TokenType type;
  byte_t *start;
  byte_t *end;
  size_t line;
};

typedef struct Token Token;

List scan(const char *source);

#endif