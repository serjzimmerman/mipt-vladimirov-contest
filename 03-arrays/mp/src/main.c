#include <assert.h>
#include <malloc.h>
#include <stdio.h>

typedef struct {
  int *coefficients;
  int len;
} polynomial;

polynomial *polynomial_init(int len) {
  polynomial *new;

  new = (polynomial *)malloc(sizeof(polynomial));

  new->len = len;
  new->coefficients = (int *)calloc(len, sizeof(int));

  return new;
}

polynomial *polynomial_create(int *array, int len) {
  int i;

  polynomial *poly = polynomial_init(len);

  for (i = 0; i < poly->len; i++) {
    poly->coefficients[i] = array[i];
  }

  return poly;
}

void polynomial_free(polynomial *poly) {
  free(poly->coefficients);
  free(poly);
}

void polynomial_sum(polynomial *a, polynomial *b) {
  int i;

  if (a->len < b->len) {
    a->coefficients = (int *)realloc(a->coefficients, b->len * sizeof(int));
  }

  for (i = 0; i < a->len; i++) {
    a->coefficients[i] += b->coefficients[i];
  }

  for (i = a->len; i < b->len; i++) {
    a->coefficients[i] = b->coefficients[i];
  }

  a->len = b->len;
}

polynomial *polynomial_mul(polynomial *a, polynomial *b) {
  polynomial *r = polynomial_init(b->len + a->len - 1);
  int i, j;

  for (i = 0; i < a->len; i++) {
    r->coefficients[i] = 0;
  }

  for (i = 0; i < a->len; i++) {
    for (j = 0; j < b->len; j++) {
      r->coefficients[i + j] += a->coefficients[i] * b->coefficients[j];
    }
  }

  return r;
}

int main() {
  int i, j, n, m, *array1, *array2;
  polynomial *p1, *p2, *p3;

  scanf("%d %d", &n, &m);

  array1 = malloc(n * sizeof(int));
  array2 = malloc(m * sizeof(int));

  for (i = 0; i < n; i++) {
    scanf("%d", &array1[i]);
  }
  for (i = 0; i < m; i++) {
    scanf("%d", &array2[i]);
  }

  p1 = polynomial_create(&array1[0], n);
  p2 = polynomial_create(&array2[0], m);

  free(array1);
  free(array2);

  p3 = polynomial_mul(p1, p2);

  for (j = p3->len - 1; p3->coefficients[j] == 0; j--) {
    ;
  }

  for (i = 0; i <= j; i++) {
    printf("%d ", p3->coefficients[i]);
  }

  polynomial_free(p1);
  polynomial_free(p2);
  polynomial_free(p3);

  return 0;
}