#ifndef _BIGNUM_H_
#define _BIGNUM_H_

#define MAX_WORDS 128

typedef struct {
  Word words[MAX_WORDS];
  int neg;
  int len;
} bignum;

extern const bignum _BN_ZERO;
extern const bignum _BN_ONE;


bignum *bn_init(void);

bignum *bn_set_int(unsigned int n, bignum *bn);

bignum *bn_from_int(unsigned int n);

void bn_clear(bignum *bn);

void bn_free(bignum *bn);

int bn_cmp(const bignum *x, const bignum *y);

bignum *bn_add(const bignum *x, const bignum *y, bignum *z);

bignum *bn_mul(const bignum *x, const bignum *y, bignum *z);

void bn_print(const bignum *bn);

#endif
