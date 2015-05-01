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

double       ft_sqrt2(const double n)
{
  /*We are using n itself as initial approximation
   This can definitely be improved */
  double x = n;
  double y = 1;
  double e = 0.0000001; /* e decides the accuracy level*/

  while(x - y > e)
  {
    x = (x + y)/2;
    y = n/x;
  }
  return x;
}

double ft_pow(double a, double b)
{
  // calculate approximation with fraction of the exponent
  int e;
  union powunion  u;
  double r;

  e = b;
  if (b < 0)
    return (1.0 / ft_pow(a, -b));
  u.d = a;
  u.x[1] = ((b - e) * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;

  // exponentiation by squaring with the exponent's integer part
  // double r = u.d makes everything much slower, not sure why
  r = 1.0;
  while (e)
  {
    if (e & 1)
      r *= a;
    a *= a;
    e >>= 1;
  }
  return r * u.d;
}
