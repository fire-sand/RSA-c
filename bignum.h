#ifndef _BIGNUM_H_
#define _BIGNUM_H_

#define MAX_WORDS 512

typedef struct {
  Word words[MAX_WORDS];
  int neg;
  int len;
} bignum;


bignum *bn_init(void);

bignum *bn_set_int(unsigned int n, bignum *bn);

void bn_free(bignum *bn);

bignum *bn_add(bignum *x, bignum *y, bignum *z);

void bn_print(bignum *bn);

#endif
