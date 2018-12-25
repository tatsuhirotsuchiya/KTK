/*
Tool for constructing pair-wise testing suites
 written by Tatsuhiro Tsuchiya at Osaka University (t-tutiya@ist.osaka-u.ac.jp)

Version 0.4 (March 27th, 2016)

This tool implements the algorithm proposed by: 
  
  Noritaka Kobayashi, Tatsuhiro Tsuchiya, and Tohru Kikuno,
  ``A New Method for Constructing Pair-Wise Covering Designs for Software Testing,''
  Information Processing Letters, Vol.81, No.2, pp.85-91, January 2002.

Usage
  For example, command "program 4x2 3x3 2x1" outputs a pairwise testing suite for
  the case of 2 4-valued, 3 3-valued, and 1 2-valued parameters.
  '-1' in the output represents the 'don't care' value.

License
  This tool is free software under the zlib license. 
 */

#include <stdio.h>
#include <stdlib.h>
#include "covering_array.h"

struct parameter_value {
  int value; // parameter value takes from 0  to value - 1 
  int number; // number of 'value'-valued parameters
};

int no_parameters;
struct parameter_value parameter[100];

void get_initial_data(int, char **);
Design *construct_design(void);

int main(int argc, char *argv[])
{
  int i;
  Design *p;
  
  get_initial_data(argc, argv);

  for (i = 0; i < no_parameters -1 ; i++)
    if(!(parameter[i].value > parameter[i+1].value)) {
      fprintf(stderr, "Parameter sizes must be in decreasing order!\n");
      exit(1);
    }

  p = construct_design(); 

  print_design(p);

  /* Error check */
  if (!check_coverage(p)) {
    fprintf(stderr, "The design is not a pairwise covering array!\n");
    return 1;
  }
  return 0;
}
