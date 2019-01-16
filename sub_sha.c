/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_sha.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2018/12/10 12:35:55 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"


int            sub_hash(t_flags *f)
{
  f->h = f->g;
  f->g = f->f;
  f->f = f->e;
  f->e = f->d + f->temp1;
  f->d = f->c;
  f->c = f->b;
  f->b = f->a;
  f->a = f->temp1 + f->temp2;
  f->eight = f->seven;
  f->seven = f->six;
  f->six = f->five;
  f->five = f->four + f->t1;
  f->four = f->three;
  f->three = f->two;
  f->two = f->one;
  f->one = f->t1 + f->t2;
  return (1);
}

uint32_t                *z_ero(uint32_t *w, t_flags *f)
{
  int i = 0;
  int max = (TWO_FIFTY(f->det)) ? (64) : (160);

  //sha_initi(f);
  while(i < max)
    {
      w[i] = 0;
      i++;
    }
  return (w);
}

void    sha_copy(char *w, char *buf, t_flags *f)
{
  int i = 0;
  int j = (TWO_FIFTY(f->det)) ? (3) : (7);
  int ja = 0;
  int max = (TWO_FIFTY(f->det)) ? (64) : (128);
  int size = (TWO_FIFTY(f->det)) ? (4) : (8);
  int k = 0;
  uint64_t *debug;
  debug = (uint64_t*)w;

  while (i < max)
    {
      w[i] = buf[j];
      i++;
      if ((i % size) == 0)
        {
          //printf("\n\n%llx %d\n\n", debug[k], k);
          k++;
          j += (size * 2);
        }
      j--;
    }

}


uint32_t rR(uint32_t w, uint32_t r)
{
  return(((w >> r) | (w << (32 - r))));
}


void    accumulate(t_flags *f)
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

