/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2018/12/10 12:35:55 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void            sha512_hash(t_flags *f)
{
  int i;
  uint64_t s0;
  uint64_t s1;

  i = 16;
  while (i < 80)
    {
      s0 = (rR(f->W[(i - 15)], 1) ^ rR(f->W[(i - 15)], 8) ^ (f->W[(i - 15)] >> 7));
      s1 = (rR(f->W[(i - 2)], 19) ^ rR(f->W[(i - 2)], 61) ^ (f->W[(i - 2)] >> 6));
      f->W[i] = f->W[(i - 16)] + s0 + f->W[(i - 7)] + s1;
      i++;
    }
  i = 0;
  sha_init_abc(f);//
  while (i < 80)
    {
      s1 = (rR(f->five, 14) ^ rR(f->five, 18) ^ rR(f->five, 41));
      f->ch = ((f->five & f->six) ^ ((~f->five) & f->seven));
      f->t1 = f->eight + s1 + f->cha + f->k[i] + f->W[i];
      s0 = (rR(f->one, 28) ^ rR(f->one, 34) ^ rR(f->one, 39));
      f->mj = ((f->one & f->two) ^ (f->one & f->three) ^ (f->two & f->three));
      f->t2 = s0 + f->maj;
      sub_hash(f);//
      i++;
    }
  accumulate(f);
  printf("%llu %llu %llu %llu %llu %llu %llu %llu\n", f->h0, f->h1, f->h2, f->h3, f->h4, f->h5, f->h6, f->h7);
}

void            sha_512(t_flags *f)
{
  uint64_t w[80];
  char buf[257];
  uint64_t k[80];


  f->W = (uint64_t*)z_ero((uint32_t*)w, f);
  f->k = sha_make_k(k, f);
  while(128 == (f->ret = read(f->fd, buf, 128)))
    {
      sha_copy((char*)w, buf, f);
      sha512_hash(f);
      f->orig_len += 1024;
    }
  if (f->ret > 0)
    ft_pad(buf, f);

  while(f->i < f->ret)
    {
      sha_copy((char*)w, &buf[f->i], f);
      printW((uint32_t*)w);
      printSW((uint32_t*)w);
      f->i += 64;
      sha512_hash(f);
    }
  print256(sha_append(f));
}
