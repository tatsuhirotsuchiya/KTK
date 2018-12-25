#include <stdio.h>
#include <stdlib.h>
#include "covering_array.h"

Design *reduced_product(Design *d, Design *bd)
{
  // bd is a design such that
  //  a zero tuple is contained,
  //  a block structured design is obtained by removing the column with maximum index,
  //  and the value in the above column represents the block number.

  // the range must be the same for every parameter.
  
  int i, j, k;
  int new_value;
  Design *product;
  int *tuple, *head;
  int cordinate;
  
  product = (Design *)malloc(sizeof(Design));
  
  product->no_pars = d->no_pars * (bd->no_pars-1) + 1;
  product->size = 0;
  product->value = NULL;
  product->range = (int *)calloc(product->no_pars, sizeof(int));
  for(i = 0; i < product->no_pars; i++) 
    *(product->range + i) = *d->range;
  
  tuple  = (int *)malloc(sizeof(int) * product->no_pars);
  
  for(i = 0; i < d->size; i++) {
    head = tuple;
    cordinate = 0;
    for (j = 0; j < bd->no_pars -1; j++) {
      for (k = 0; k < d->no_pars; k++) {
        *head = read_value(d, i, k);
        head++; cordinate++;
      }
    }
    *head = 0;
    add_tuple(product, tuple);
  }

  for(i = 0; i < bd->size; i++) {
    if (read_value(bd, i, bd->no_pars-1) == 0)
      continue;
    head = tuple;
    cordinate = 0;
    for (j = 0; j < bd->no_pars -1; j++) {
      new_value = read_value(bd, i, j);
      for (k = 0; k < d->no_pars; k++) {
        *head = new_value;
        head++; cordinate++;
      }
    }
    *head = read_value(bd, i, bd->no_pars-1);
    add_tuple(product, tuple);
  }

  free(tuple);
  return product;
}
