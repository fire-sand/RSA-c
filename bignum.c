#include "word.h"
#include "bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const bignum _BN_ZERO = {{0}, 0, 0};
const bignum _BN_ONE = {{1}, 0, 0};

bignum *bn_init(void) {
  bignum *bn = (bignum *)malloc(sizeof(bignum));
  memset(bn->words, 0, MAX_WORDS * WORD_SIZE);
  bn->neg = 0;
  bn->len = 0;

  return bn;
}

bignum *bn_set_int(unsigned int n, bignum *bn) {
  bn->words[0] = (Word)n;
  return bn;
}

bignum *bn_from_int(unsigned int n) {
  bignum *ret = bn_init();
  bn_set_int(n, ret);
  return ret;
}

bignum *bn_add(const bignum *x, const bignum *y, bignum *z) {
  int m = x->len;
  int n = y->len;

  if (m < n) return bn_add(y, x, z);

  bn_clear(z);

  int i;
  Word carry = 0;
  for (i = 0; i <= n; ++i) {
    Word tmp_carry = 0;
    z->words[i] = add_WW(x->words[i], y->words[i], &tmp_carry);
    if (carry) z->words[i] = add_WW(carry, z->words[i], &tmp_carry);
    if (carry || tmp_carry) carry = 1;
  }

  for (; i <= m; ++i) {
    if (carry) z->words[i] = add_WW(carry, x->words[i], &carry);
  }

  if (carry) {
    z->words[i] = (Word) carry;
  }

  z->len = i - 1 + carry;

  return z;
}

int bn_cmp(const bignum *x, const bignum *y) {
  int m = x->len;
  int n = y->len;

  if (m > n) return 1;
  if (m < n) return -1;

  for (int i = 0; i <= m; ++i){
    Word xi = x->words[i];
    Word yi = y->words[i];
    if (!(xi == yi)) {
      if (xi < yi) return -1;
      if (xi > yi) return 1;
    }
  }

  return 0;
}

void bn_clear(bignum *bn) {
  memset(bn->words, 0, MAX_WORDS * WORD_SIZE);
  bn->neg = 0;
  bn->len = 0;
}

bignum *bn_mul(const bignum *x, const bignum *y, bignum *z) {
  bignum *tmp = bn_init();
  bn_clear(z);

  while (bn_cmp(tmp, y) != 0) {
    bn_add(z, x, z);
    bn_add(tmp, &_BN_ONE, tmp);
  }

  bn_free(tmp);
  return z;
}

void bn_print(const bignum *bn) {
  if (bn->neg) printf("-");
  for (int i = bn->len; i >= 0; --i)
  {
    printf("%.*x", (int)WORD_SIZE / 4, bn->words[i]);
  }
  printf("\n");
}

void bn_free(bignum *bn) {
  free(bn);
}

int main(int argc, char const *argv[]) {

  bignum *bn1 = bn_init();
  bignum *bn2 = bn_init();
  bignum *bn3 = bn_init();

  bn_print(bn1);
  bn_print(bn2);

  bn_set_int(0xFFFFFFFF, bn1);
  bn_set_int(2, bn2);

  bn_print(bn1);
  bn_print(bn2);

  bn_mul(bn1, bn2, bn3);

  bn_print(bn1);
  bn_print(bn2);
  bn_print(bn3);

  bn_free(bn1);
  bn_free(bn2);
  bn_free(bn3);

  printf("hello world!\n");

  return 0;
}
