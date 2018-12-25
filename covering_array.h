typedef struct {
  int no_pars;
  int size;
  int *range;
  int *value;
} Design;

/* operators.c */
int check_coverage(Design *);
void set_dontcare_value(Design *);
void truncate_design(Design *, int);
void add_tuple(Design *, int *);
void set_value(Design *, int , int , int );
int read_value(Design *, int , int );
void print_design(Design *);
int smallest_prime_power(int );
int greatest_prime_power(int );
