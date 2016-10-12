#ifndef _WORD_H_
#define _WORD_H_

typedef unsigned int Word;

extern const unsigned int WORD_SIZE;
extern const unsigned int HALF_WORD_SIZE;
extern const unsigned int LOWER_HALF_WORD_MASK;
extern const unsigned int UPPER_HALF_WORD_MASK;

Word add_WW(Word a, Word b, Word *c);

#endif
