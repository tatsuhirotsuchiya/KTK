#include <stdio.h>
#include <stdlib.h>
#include "covering_array.h"

int check_coverage(Design *b)
{
  int p1, p2;
  int v1, v2;
  int i, flag;

  
  for(p1 = 0; p1 < b->no_pars; p1++)
      for(p2 = 0; p2 < b->no_pars; p2++)
        {
          if (p1 == p2)
            continue;
          for(v1 = 0; v1 < *(b->range + p1); v1++)
            for(v2 = 0; v2 < *(b->range + p2); v2++)
              {
                // check
                flag = 0;
                for (i = 0; i< b->size; i++)
                  if ((read_value(b, i, p1) == v1) &&
                      (read_value(b, i, p2) == v2)) {
                    flag = 1; break;
                  }
                if (!flag)
                  return 0;
              }
        }

  return 1;
}

void set_dontcare_value(Design *b)
{
  int i,j ;
  int v;

  for(i = 0; i < b->size; i++)
    for (j = 0; j < b->no_pars; j++) {
      v = read_value(b, i, j);
      if (v >= *(b->range + j))
        set_value(b, i, j, -1);
    }
}


void truncate_design(Design *b, int n)
{
  int i,j;
  int *new_values, *head, *new_ranges;

  if (n > b->no_pars)
    exit(1);

  if (n == b->no_pars)
    return;

  head = new_values = (int *)calloc(n * b->size, sizeof(int));
  for(i = 0; i < b->size; i++)
    for(j = 0; j < n; j++) {
      *head = read_value(b, i, j);
      head++;
    }
  free(b->value);
  b->value = new_values;
  b->no_pars = n;

  new_ranges = (int *)calloc(n, sizeof(int));
  for(j = 0; j < n; j++)
    *(new_ranges + j) = *(b->range + j);
  free(b->range);
  b->range = new_ranges;
}

void add_tuple(Design *b, int *tuple)
{
  int *new_values;
  int i,j;
  int *head1, *head2;
  
  if (b->no_pars < 1)
    exit(0);

  if (b->size < 0)
    exit(0);

  new_values = (int *)calloc((b->size +1) * b->no_pars, sizeof(int));
  head1 = new_values;
  head2 = b->value;
  for(i = 0; i< b->size; i++)
    for(j = 0; j < b->no_pars; j++) {
      *head1 = *head2; head1++; head2++;
    }
  head2 = tuple;
  for(j = 0; j < b->no_pars; j++) {
    *head1 = *head2; head1++; head2++;
  }
  if (b->value != NULL)
    free(b->value);
  b->value = new_values;
  b->size++;
}

void set_value(Design *b, int row, int col, int value)
{
  b->value[col + row * b->no_pars] = value;
}

int read_value(Design *b, int row, int col)
{
  return b->value[col + row * b->no_pars];
}

void print_design(Design *b)
{
  int i,j ;

  printf("no of parameters %d\n", b->no_pars);
  printf("ranges\n");
  for (i = 0; i< b->no_pars; i++)
    printf("%2d ", b->range[i]);

  printf("\nvalues\n");
  for (i = 0; i< b->size; i++) {
    for (j = 0; j< b->no_pars; j++)
      printf("%2d ", read_value(b, i, j));
    printf("\n");
  }
  printf("size %d\n", b->size);
}

int smallest_prime_power(int value)
     // value should be at least 2
{
  int flag_prime = 1;
  int flag_prime_power = 1;
  int factor, tmp;
  
  if (value < 1) {
    fprintf(stderr, "limit exceeded\n");
    exit(1);
  }

  for(factor = 2; factor < value; factor++) {
    if (value % factor == 0) {
      flag_prime = 0;
      break;
    }
  }
  if (flag_prime)
    return value;

 
  tmp = value;
  while(tmp > 1) {
    if (tmp % factor != 0) {
      flag_prime_power = 0;
      break;
    }
    tmp = tmp / factor;
  }
  if (flag_prime_power)
    return value;

  return smallest_prime_power(value+1);
}

int greatest_prime_power(int value)
     // value should be at least 2
{
  int flag_prime = 1;
  int flag_prime_power = 1;
  int factor, tmp;
  
  if (value < 1) {
    fprintf(stderr, "limit exceeded\n");
    exit(1);
  }

  for(factor = 2; factor < value; factor++) {
    if (value % factor == 0) {
      flag_prime = 0;
      break;
    }
  }
  if (flag_prime)
    return value;

 
  tmp = value;
  while(tmp > 1) {
    if (tmp % factor != 0) {
      flag_prime_power = 0;
      break;
    }
    tmp = tmp / factor;
  }
  if (flag_prime_power)
    return value;

  return greatest_prime_power(value-1);
}
