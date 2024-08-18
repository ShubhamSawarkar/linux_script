#include "scanner.h"

#include "error.h"

#define MAKE_TOKEN(type, start, end, line) (Token) { type, start, end, line }

#define IS_DIGIT(c) c >= '0' && c <= '9'

#define IS_BLANK(c) c == ' ' || c == '\t' || c == '\r'

#define IS_LINE_TERMINATOR(c) c == '\n'

struct Scanner {
  char prev;
  char *curr;
  size_t curr_line;
  List tokens;
} sc;

typedef struct Scanner Scanner;

static char peek() {
  return *sc.curr;
}

static char next() {
  sc.prev = peek() ? *sc.curr++ : '\0';
  return sc.prev;
}

static char peekNext() {
  return sc.curr[1];
}

static Token error(const char *errorMsg) {
  return MAKE_TOKEN(TOKEN_ERROR, errorMsg, NULL, sc.curr_line);
}

static Token string() {
  Token token = MAKE_TOKEN(TOKEN_LITERAL_STRING, sc.curr, NULL, sc.curr_line);
  while (next() != '"' && sc.prev) if (IS_LINE_TERMINATOR(sc.prev)) ++sc.curr_line;
  if (sc.prev != '"') error(COMPILATION_ERROR_UNCLOSED_STRING);
  token.end = sc.curr - 1;
  return token;
}

static Token number() {
  Token token = MAKE_TOKEN(TOKEN_LITERAL_NUMBER, sc.curr - 1, NULL, sc.curr_line);
  while (IS_DIGIT(peek())) next();
  if (sc.prev == '.' && IS_DIGIT(peekNext())) while (IS_DIGIT(peek())) next();
  token.end = sc.curr;
  return token;
}

static Token operator() {
  Token token;

  switch (sc.prev) {
    case '(':
      token = MAKE_TOKEN(TOKEN_BRACKET_OPEN, sc.curr - 1, sc.curr, sc.curr_line);
      break;

    case ')':
      token = MAKE_TOKEN(TOKEN_BRACKET_CLOSE, sc.curr - 1, sc.curr, sc.curr_line);
      break;

    case '{':
      token = MAKE_TOKEN(TOKEN_BRACE_OPEN, sc.curr - 1, sc.curr, sc.curr_line);
      break;

    case '}':
      token = MAKE_TOKEN(TOKEN_BRACE_CLOSE, sc.curr - 1, sc.curr, sc.curr_line);
      break;

    case '+':
      if (peek() == '=') {
        next();
        token = MAKE_TOKEN(TOKEN_PLUS_EQUAL, sc.curr - 2, sc.curr, sc.curr_line);
      } else {
        token = MAKE_TOKEN(TOKEN_PLUS, sc.curr - 1, sc.curr, sc.curr_line);
      }      
      break;

    case '-':
      if (peek() == '=') {
        next();
        token = MAKE_TOKEN(TOKEN_MINUS_EQUAL, sc.curr - 2, sc.curr, sc.curr_line);
      } else {
        token = MAKE_TOKEN(TOKEN_MINUS, sc.curr - 1, sc.curr, sc.curr_line);
      }      
      break;

    case '*':
      if (peek() == '=') {
        next();
        token = MAKE_TOKEN(TOKEN_STAR_EQUAL, sc.curr - 2, sc.curr, sc.curr_line);
      } else {
        token = MAKE_TOKEN(TOKEN_STAR, sc.curr - 1, sc.curr, sc.curr_line);
      }      
      break;

    case '/':
      if (peek() == '=') {
        next();
        token = MAKE_TOKEN(TOKEN_SLASH_EQUAL, sc.curr - 2, sc.curr, sc.curr_line);
      } else {
        token = MAKE_TOKEN(TOKEN_SLASH, sc.curr - 1, sc.curr, sc.curr_line);
      }      
      break;

    case '=':
      if (peek() == '=') {
        next();
        token = MAKE_TOKEN(TOKEN_EQUAL_EQUAL, sc.curr - 2, sc.curr, sc.curr_line);
      } else {
        token = MAKE_TOKEN(TOKEN_EQUAL, sc.curr - 1, sc.curr, sc.curr_line);
      }
      break;

    case '!':
      if (next() != '=') {
        return error(COMPILATION_ERROR_UNRECONGNIZED_TOKEN);
      }
      token = MAKE_TOKEN(TOKEN_NOT_EQUAL, sc.curr - 2, sc.curr, sc.curr_line);
      break;

    case '>':
      if (peek() == '=') {
        next();
        token = MAKE_TOKEN(TOKEN_GREATER_THAN_EQUAL, sc.curr - 2, sc.curr, sc.curr_line);
      } else {
        token = MAKE_TOKEN(TOKEN_GREATER_THAN, sc.curr - 1, sc.curr, sc.curr_line);
      }
      break;

    case '<':
      if (peek() == '=') {
        next();
        token = MAKE_TOKEN(TOKEN_LESS_THAN_EQUAL, sc.curr - 2, sc.curr, sc.curr_line);
      } else {
        token = MAKE_TOKEN(TOKEN_LESS_THAN, sc.curr - 1, sc.curr, sc.curr_line);
      }
      break;

    default:
      return error(COMPILATION_ERROR_UNRECONGNIZED_TOKEN);
      break;
  }
  return token;
}

List scan(const char *source) {
  List tokens = list(sizeof(Token));
  sc = (Scanner) { *source, source, 1, tokens };

  while (next()) {
    if (sc.prev == '\n') {
      ++sc.curr_line;
    } else if (IS_BLANK(sc.prev)) {
      continue;
    }

    Token token;
    if (IS_DIGIT(sc.prev)) {
      token = number();
    } else if (sc.prev == '"') {
      token = string();
    } else {
      token = operator();
    }

    add(&sc.tokens, &token);
  }
  return sc.tokens;
}