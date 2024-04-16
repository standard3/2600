#include <stdbool.h>
#include <ctype.h>
#include "my_calc.h"

void whitespace(struct parser * p) {
  int save = p -> current_pos;
  if (readtext(p, "//")) {
    while (p -> content[p -> current_pos] && p -> content[p -> current_pos] != '\n' && p -> content[p -> current_pos] != '\0') {
      if (p -> current_pos > p -> last_pos)
        p -> last_pos = p -> current_pos;
    }
  } else if (p -> content[p -> current_pos] && isspace(p -> content[p -> current_pos])) {
    while (p -> content[p -> current_pos] && isspace(p -> content[p -> current_pos])) {
      p -> current_pos += 1;
      if (p -> current_pos > p -> last_pos) {
        p -> last_pos = p -> current_pos;
      }
    }
  } else {
    p -> current_pos = save;
  }
}

bool read_var_name(struct parser * p) {
  whitespace(p);
  if (readrange(p, 'a', 'z') || readrange(p, 'A', 'Z') || readchar(p, '_')) {
    while (readrange(p, 'a', 'z') || readrange(p, 'A', 'Z') || readchar(p, '_')) {}
    return true;
  }
  return false;
}

bool assigment(struct parser * p, struct scope * s) {

  int save_pos = p -> current_pos;

  if (read_var_name(p)) {
    whitespace(p);
    if (readchar(p, '='))
      if (expression(p, s))
        return true;
  }
  p -> current_pos = save_pos;
  return false;
}

bool variable(struct parser * p, struct scope * s) {
  if (assigment(p, s)) {
    return true;
  }
  if (read_var_name(p)) {
    return true;
  }
  return false;
}

bool value(struct parser * p, struct scope * s) {
  whitespace(p);
  if (readint(p)) {
    return true;
  }
  if (expression(p, s)) {
    return true;
  }
  if (variable(p, s)) {
    return true;
  }
  return false;
}

bool power(struct parser * p, struct scope * s) {
  if (value(p, s)) {
    whitespace(p);
    if (readchar(p, '^')) {
      if (!power(p, s)) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool product(struct parser * p, struct scope * s) {
  if (power(p, s)) {
    if (readchar(p, '*') || readchar(p, '/')) {
      if (!power(p, s)) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool sum(struct parser * p, struct scope * s) {
  whitespace(p);
  if (product(p, s)) {
    if (readchar(p, '+') || readchar(p, '-')) {
      if (!product(p, s)) {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool expression(struct parser * p, struct scope * s) {
  if (!sum(p, s)) {
    return false;
  }
  return true;
}

int my_calc(struct parser * p, struct scope * s) {
  return (expression(p, s));
}
