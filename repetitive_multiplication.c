#include <stdio.h>
#include <stdlib.h>
#include "covering_array.h"

Design *reduced_product(Design *, Design *);
Design *finite_field_based_design(int);     
Design *repetitive_multiplication(int v, int number)
{

  int i;
  Design *product, *base, *new_product;
  int primepower;

  primepower = smallest_prime_power(v);

  product = finite_field_based_design(v);
  base = finite_field_based_design(v);
  while (product->no_pars < number) {
    new_product = reduced_product(product, base);
    free(product->range); free(product->value); free(product);
    product = new_product;
  }

  free(base->range); free(base->value); free(base);
  
  for (i = 0; i < product->no_pars; i++)
    *(product->range + i) = v;

  truncate_design(product, number);
  set_dontcare_value(product);
  return product;
}
