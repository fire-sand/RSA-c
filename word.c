#include "word.h"

const unsigned int WORD_SIZE = (unsigned int)(sizeof(Word) * 8);
const unsigned int HALF_WORD_SIZE = WORD_SIZE / 2;
const unsigned int LOWER_HALF_WORD_MASK = (1 << HALF_WORD_SIZE) - 1;
const unsigned int UPPER_HALF_WORD_MASK = LOWER_HALF_WORD_MASK << HALF_WORD_SIZE;

Word add_WW(Word a, Word b, Word *c) {
  if (a == 0) {
    *c = 0;
    return b;
  }
  if (b == 0) {
    *c = 0;
    return a;
  }

  Word a_l = a & LOWER_HALF_WORD_MASK;
  Word b_l = b & LOWER_HALF_WORD_MASK;
  Word lower = a_l + b_l;
  Word lower_carry = (lower & UPPER_HALF_WORD_MASK) >> HALF_WORD_SIZE;
  lower = lower & LOWER_HALF_WORD_MASK;

  Word a_h = (a & UPPER_HALF_WORD_MASK) >> HALF_WORD_SIZE;
  Word b_h = (b & UPPER_HALF_WORD_MASK) >> HALF_WORD_SIZE;
  Word upper = a_h + b_h + lower_carry;

  *c = (upper & UPPER_HALF_WORD_MASK) >> HALF_WORD_SIZE;
  return (upper << HALF_WORD_SIZE) | lower;
}
