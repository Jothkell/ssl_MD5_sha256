/* ************************************************************************** */
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

void    ass_op(void (**op) (t_flags *f, char **argv))
{
  op['p'] = ft_stdin;
  op['q'] = ft_flags;
  op['r'] = ft_flags;
  op['s'] = ft_strin;//init rest to error handling function, for invalid flag
}

uint32_t                *ft_make_s(void)
{
  uint32_t b[] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
		  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
		  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
		  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
  };
  uint32_t *s;
  uint32_t i;

  i = 0;
  s = malloc(sizeof(uint32_t) * 64);
  while (i < 64)
    {
      s[i] = b[i];
      i++;
    }
  return (s);
}

char *append(t_flags *f)
{
  uint32_t        *hold;
  int     i;

  i = 0;
  hold = malloc(sizeof(uint32_t) * 4);
  hold[0] = f->a_fin;
  hold[1] = f->b_fin;
  hold[2] = f->c_fin;
  hold[3] = f->d_fin;
  return ((char*)hold);
}

void    initi(t_flags *f)
{
  //f->i = 0;
  f->orig_len = 0;
  f->a_fin = 0x67452301;
  f->b_fin = 0xefcdab89;
  f->c_fin = 0x98badcfe;
  f->d_fin = 0x10325476;
  f->a = 0x67452301;
  f->b = 0xefcdab89;
  f->c = 0x98badcfe;
  f->d = 0x10325476;
}
