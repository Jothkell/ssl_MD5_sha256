d/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/13 21:08:19 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

uint32_t        leftRotate(uint32_t n, uint32_t d)
{
  return (n << d) | (n >> (32 - d));
}

uint32_t                        *ft_make_k(void)
{
  uint32_t                i;
  const uint32_t  b[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
			 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
			 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
			 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
			 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
			 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
			 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
			 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
			 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
			 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
			 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
  };
  uint32_t                *k;

  k = malloc(sizeof(uint32_t) * 64);
  i = 0;
  while (i < 64)
    {
      k[i] = b[i];
      i++;
    }
  return (k);
}

void            l_ind(char *hold, char *buf, t_flags *f)
{
  while ((f->ret % 64) != 0)
    {
      buf[f->ret] = *hold;
      hold++;
      f->ret++;
    }
}

void            b_ind(char *hold, char *buf, t_flags *f)
{
  int             j;
  int             k;

  j = (TWO_FIFTY(f->det)) ? (7) : (15);
  k = 0;
  while ((f->ret % 64) != 0 && (j != 7))
    {
      buf[f->ret] = 0;
      f->ret++;
      k = j;
      j--;
    }
  while (0 <= j)
    {
      buf[f->ret] = hold[j];
      f->ret++;
      j--;
    }
}

void            accumulate(t_flags *f)
{
  f->a_fin += f->a;
  f->b_fin += f->b;
  f->c_fin += f->c;
  f->d_fin += f->d;
  f->e_fin += f->e;
  f->f_fin += f->f;
  f->g_fin += f->g;
  f->h_fin += f->h;
  f->h0 += f->one;
  f->h1 += f->two;
  f->h2 += f->three;
  f->h3 += f->four;
  f->h4 += f->five;
  f->h5 += f->six;
  f->h6 += f->seven;
  f->h7 += f->eight;
}
