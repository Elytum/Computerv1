/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achazal <achazal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/01 08:16:17 by achazal           #+#    #+#             */
/*   Updated: 2015/04/01 08:16:18 by achazal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/computorv1.h"
#include <math.h>

double abs2(v)
{
  return ((v < 0) ? -v : v);
}

double				ft_sqrt(const double fg)
{
	double			n;
	double			lstx;

	n = fg / 2.0;
	lstx = 0.0;
	while (n != lstx)
	{
		lstx = n;
		n = (n + fg / n) / 2.0;
	}
	return (n);
}

// double				ft_pow(double b, double p)
// {
// 	// return (exp(p * log(b)));
// 	union powunion	u;
// 	double			r;
// 	int				e;

// 	u.d = a;
// 	u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
// 	u.x[0] = 0;
// 	if (a < 0 || b < 0)
// 		return (u.d);
// 	r = 1.0;
// 	e = b;
// 	while (e)
// 	{
// 		if (e & 1)
// 			r *= a;
// 		a *= a;
// 	e >>= 1;
// 	}
// 	return (r * u.d);
// }


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