#include "word.h"
#include "bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bn_print(bignum *bn) {
  if (bn->neg) printf("-");
  for (int i = bn->len; i >= 0; --i)
  {
    printf("%.*x", (int)WORD_SIZE / 4, bn->words[i]);
  }
  printf("\n");
}

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

bignum *bn_add(bignum *x, bignum *y, bignum *z) {
  int m = x->len;
  int n = y->len;

  if (m < n) return bn_add(y, x, z);

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
    z->len = i;
  } else {
    z->len = i - 1;
  }

  return z;
}

void bn_free(bignum *bn) {
  free(bn);
}

int main(int argc, char const *argv[])
{

  bignum *bn1 = bn_init();
  bignum *bn2 = bn_init();

  bn_print(bn1);
  bn_print(bn2);

  bn_set_int(0xFFFFFFFF, bn1);
  bn_set_int(0xFFFFFFFF, bn2);

  bn_print(bn1);
  bn_print(bn2);

  bignum *bn3 = bn_init();

  bn_add(bn1, bn2, bn3);

  bn_print(bn1);
  bn_print(bn2);
  bn_print(bn3);

  printf("hello world!\n");

  return 0;
}
