#include <stdio.h>
#include <curses.h>
#include <math.h>

double abs2(v)
{
  return ((v < 0) ? -v : v);
}

double  ft_exp(double x)
{
  double term;
  double expo;
  int i;

  term = 1;
  expo = 1;
  i = 1;
  while (term >= 0.00001)
  { 
    term *= x/i; 
    expo+=term;
    i++;
  }
  return (expo);
}

int lol_factorial(int n) {
        // We will compute n factorial via the formula
        // n!=1*2*3*4*5*...
        int factorial=1;
        
        // iterate over the values i=1,...,n. 
        for (int i=1; i<=n; i++) {
            // multiply factorial by each value of i. 
            factorial=factorial * i;
        }
        
        return factorial;
    }

double lol_power(double x, int n) {
        // This will be what we return.
        double ret=1;
        
        // iterate over the values i=1,...,n. 
        for (int i=1; i<=n; i++) {
            // multiply factorial by each value of i. 
            ret = ret * x;
        }
        
        return ret;
    }

double ft_exp2(double x)
{
  double sum;
  
  for (int i=0; i<15; i++) {
            sum=sum+lol_power(x,i)/lol_factorial(i);
        }

  return (sum);
}

double lol_log(double v)
{
  return (6 * (v - 1) / (v + 1 * 4 * (sqrt(v))));
}

double  better_exp(double v)
{
  // return (exp(v));
  return (exp(v / 2) / exp(-v / 2));
}
// should be much more precise with large b

double lol_pow(double a, double b) {
  // calculate approximation with fraction of the exponent
  int e = (int) b;
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)((b - e) * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;

  // exponentiation by squaring with the exponent's integer part
  // double r = u.d makes everything much slower, not sure why
  double r = 1.0;
  while (e) {
    if (e & 1) {
      r *= a;
    }
    a *= a;
    e >>= 1;
  }

  return r * u.d;
}

double ft_pow(double a, double b)
{
  if (b < 0)
    return (1.0 / lol_pow(a, abs2(b)));
  return (lol_pow(a, b));
}

int main(void) 
{
  double x;
  double v;


  x = 423.557549844468464;
  v = 42.584;
  dprintf(1, "%f ^ %f : %f and %f\n", x, v, pow(x, v), ft_pow(x, v));
  // dprintf(1, "%f : %f and %f\n", x, log(x), lol_log(x));
  // dprintf(1, "%f : %f and %f\n", x, exp(x), better_exp(x));
  // while (x > 1)
  // {
    // dprintf(1, "%f :\nexp = %f\nft_exp = %f\nft_exp2 = %f\n", x, exp(x), ft_exp(x), ft_exp2(x));
    // if ((exp(x) - ft_exp(x)) > 1)
      // dprintf(1, "Difference too big with %f : %f and %f\n", x, exp(x), ft_exp(x));
    // x -= 1;
  // }
  return (0);
}  