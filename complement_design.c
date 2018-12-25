#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "covering_array.h"

Design *finite_field_based_design(int);

Design *complement_design(int number, int *ranges)
{
  // values[] must be an descending ordered array of values of length number

  int i, j;
  int v1, v2;
  Design *new_design;
  Design *base;

  int *tuple;
  int l, r, q;

  if (number < 2)
    exit(1);
  
  new_design = (Design *)malloc(sizeof(Design));
  new_design->no_pars = number;
  new_design->size = 0;
  new_design->range = (int *)calloc(number, sizeof(int));
  memcpy(new_design->range, ranges, number*sizeof(int));
  
  tuple = (int *)calloc(number, sizeof(int));
  
  r = greatest_prime_power(*(ranges+1));
  
  // Case 1
  if (number <= r+1)
    {
      base = finite_field_based_design(r);
      truncate_design(base, new_design->no_pars);
      new_design->size = base->size;  
      new_design->value = base->value;
      free(base->range); free(base);

      // determine l
      for(l = 1; l < number; l++) {
        if (l + 1 == number)
          break;
        if (r > *(ranges + l + 1))
          break;
      }
      
      for (v1 = r ; v1 < *(ranges + l); v1++) {
        for(v2 = 0; v2 < r; v2++) {
          for(j = 0; j < number; j++)
            *(tuple + j) = v2;
          *(tuple + l) = v1;
          add_tuple(new_design, tuple);
        }
      }

      //
      for (i = l-1; i >= 0; i--) {  // l-1, l-2, ..., 0
        for (v1 = r ; v1 < *(ranges + i); v1++) {
          for(v2 = 0; v2 < *(ranges + i + 1); v2++) {
            for(j = 0; j < number; j++)
              *(tuple + j) = v2;
            *(tuple + i) = v1;
            add_tuple(new_design, tuple);
          }
        }
      }
      
    }
  else // Case 2
    {
      q = smallest_prime_power(*ranges);
      base = finite_field_based_design(q);
      truncate_design(base, new_design->no_pars);
      new_design->size = base->size;
      new_design->value = base->value;
      free(base->range); free(base);
    }

  set_dontcare_value(new_design);
  free(tuple);
  return new_design;
}
