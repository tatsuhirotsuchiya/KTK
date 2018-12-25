#include <stdio.h>
#include <stdlib.h>
#include "covering_array.h"

struct parameter_value {
  int value;
  int number;
};

extern int no_parameters;
extern struct parameter_value parameter[100];

Design *complement_design(int , int *);
Design *finite_field_based_design(int);
Design *repetitive_multiplication(int, int);
Design *single_parameter(int);
Design *concatinate(Design *, Design *);
     
Design *construct_design(void)
{
  int i, j, k, v;
  int flag;
  int *ranges, *tuple, *head;
  Design *p, *q, *tmp;
  

  flag = 1;
  for (i = 0; i < no_parameters; i++)
    if (parameter[i].number > 1) {
      flag = 0; break;
    }

  if (flag && (no_parameters > 1)) // see Section 2.3
    {
      ranges = (int *)calloc(no_parameters, sizeof(int));
      for (i = 0; i < no_parameters; i++)
        *(ranges + i) = parameter[i].value;
      p = complement_design(no_parameters, ranges);
      free(ranges);
      print_design(p);
      return p;
    }
  
  i = 0;
  if(parameter[i].number > 1) 
    p = repetitive_multiplication(parameter[i].value, parameter[i].number);
  else     // parameter[i].number == 1 
    p = single_parameter(parameter[i].value);
    
  for (i = 1; i < no_parameters ; i++) {
    if(parameter[i].number > 1) 
      q = repetitive_multiplication(parameter[i].value, parameter[i].number);
    else     // parameter[i].number == 1
      q = single_parameter(parameter[i].value);

    tmp = concatinate(p, q);
    free(p->range); free(p->value); free(p); p = tmp;
    free(q->range); free(q->value); free(q);
  }

  if (i == 1)
    return p;
  
  ranges = (int *)calloc(no_parameters, sizeof(int));
  
  for (i = 0; i < no_parameters; i++)
    *(ranges + i) = parameter[i].value;

  q = complement_design(no_parameters, ranges);

  tuple = (int *)calloc(p->no_pars, sizeof(int));
  for(i = 1; i < q->size; i++) {
    head = tuple;
    for(j = 0; j < no_parameters; j++) {
      v = read_value(q, i, j);
        for (k = 0; k < parameter[j].number; k++) {
          *head = v; head++;
        }
    }
    add_tuple(p, tuple);
  }
  free(ranges); free(tuple);
  return p;
}


Design *concatinate(Design *a, Design *b)
{
  int i, j;
  Design *sum;
  int *tuple;
  int size;
  
  sum = (Design *)malloc(sizeof(Design));
  
  sum->no_pars = a->no_pars + b->no_pars;
  if (a->size > b->size)
    size = a->size;
  else
    size = b->size;
  sum->size = 0;
  sum->value = NULL;
  
  sum->range = (int *)calloc(sum->no_pars, sizeof(int));
  for(i = 0; i < a->no_pars; i++) 
    *(sum->range + i) = *(a->range + i);
  for(i = 0; i < b->no_pars; i++) 
    *(sum->range + a->no_pars + i) = *(b->range + i);
  
  tuple  = (int *)calloc(sum->no_pars, sizeof(int));
  
  for(i = 0; i < size; i++) {
    for(j = 0; j < a->no_pars; j++)
      if (i < a->size)
        *(tuple + j) = read_value(a, i, j);
      else
        *(tuple + j) = -1;
    for(j = 0; j < b->no_pars; j++) 
      if (i < b->size)
        *(tuple + a->no_pars + j) = read_value(b, i, j);
      else
        *(tuple + a->no_pars + j) = -1;
    
    add_tuple(sum, tuple);
  }
  free(tuple);
  return sum;
}
