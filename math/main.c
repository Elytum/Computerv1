#include <stdio.h>
#include <math.h>

double ft_sqrt( const double fg)
{ 
 double n = fg / 2.0;
 double lstX = 0.0; 
 while(n != lstX)  
 { 
 lstX = n;
 n = (n + fg/n) / 2.0; 
 }
 return n;
}

// should be much more precise with large b
static double ft_pow(double a, double b) {
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

static double ft_pow2(double a, double b) {
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;
  return u.d;
}

int main()
{
	double v1;
	double v2;
	double v;
	double i;

	v1 = 2.5;
	v2 = 4.4534;
	i = 0;
	while (i++ < 3000000000)
	{
		v = ft_pow2(v1, v2);
		v1 += 0.0001;
		v2 += 0.0001;
	}
	// dprintf(1, "%f vs %f vs %f\n", ft_pow(v1, v2), pow(v1, v2), ft_pow2(v1, v2));
	// v = 4574576468346847987749846876876874453468346848649864.546468846844355467876783276578657861354346547612435427468346845;
	// dprintf(1, "%f :\n%f vs\n%f\ndiff = %a\n", v, sqrt(v), ft_sqrt(v), ft_sqrt(v) - sqrt(v));
	// while (v > 1)
	// {
	// 	// ft = ft_sqrt(v);
	// 	real = sqrt(v);
	// 	// if (x > 2 || x < 2)
	// 	// 	dprintf(1, "v = %f, x = %f, ft = %f, real = %f\n", v, x, ft, real);
	// 	v /= 1.00001;
	// }
	return 0;
}