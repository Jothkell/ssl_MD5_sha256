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
  //printW((uint32_t*)f->W);
  while (i < 80)
    {
      s0 = (rR64(f->W[(i - 15)], 1) ^ rR64(f->W[(i - 15)], 8) ^ (f->W[(i - 15)] >> 7));
      s1 = (rR64(f->W[(i - 2)], 19) ^ rR64(f->W[(i - 2)], 61) ^ (f->W[(i - 2)] >> 6));
      f->W[i] = f->W[(i - 16)] + s0 + f->W[(i - 7)] + s1;
      i++;
    }
  //printSW((uint32_t*)f->W);
  i = 0;
  //printf("\n%llu %llu %llu %llu\n%llu %llu %llu %llu\n\n", f->h0, f->h1, f->h2, f->h3, f->h4, f->h5, f->h6, f->h7);
  sha_init_abc(f);//
  //printf("\n%llu %llu %llu %llu\n%llu %llu %llu %llu\n\n", f->h0, f->h1, f->h2, f->h3, f->h4, f->h5, f->h6, f->h7);
  while (i < 80)
    {
      s1 = (rR64(f->five, 14) ^ rR64(f->five, 18) ^ rR64(f->five, 41));
      f->cha = ((f->five & f->six) ^ ((~f->five) & f->seven));
      f->t1 = f->eight + s1 + f->cha + f->k[i] + f->W[i];
      s0 = (rR64(f->one, 28) ^ rR64(f->one, 34) ^ rR64(f->one, 39));
      f->mj = ((f->one & f->two) ^ (f->one & f->three) ^ (f->two & f->three));
      f->t2 = s0 + f->mj;
      sub_hash(f);//
      //printf("\n%llu %llu %llu %llu\n%llu %llu %llu %llu\n\n", f->one, f->two, f->three, f->four, f->five, f->six, f->seven, f->eight);
      i++;
    }
  accumulate(f);
  //printf("\n%llu %llu %llu %llu\n%llu %llu %llu %llu\n\n", f->h0, f->h1, f->h2, f->h3, f->h4, f->h5, f->h6, f->h7);
}

int	smthing_thr(t_flags *f)
{
  int i;
  int size;

  size = (TWO_FIFTY(f->det)) ? (64) : (128);
  i = 0;
  while (f->file[i] != '\0')
    {
      i++;
      if (i == size)
	return (i);
    }
    return (i);
}

void            sha_512(t_flags *f)
{
  uint64_t w[80];
  char buf[257];
  uint64_t k[80];

  f->b_ind = 1;
  f->W = (uint64_t*)z_ero((uint32_t*)w, f);
  f->k = sha_make_k(k, f);
  while(128 == (f->ret = read(f->fd, buf, 128)) || (f->file && ((f->ret = smthing_thr(f)) == 128)))
    {
      sha_copy((char*)w, buf, f);
      //printW((uint32_t*)w);
      sha512_hash(f);
      f->orig_len += 1024;
      f->file += (f->file) ? (128) : (0);
    }
  if (f->ret > 0)// || (f->file && f->ret))
    ft_64pad(buf, f);

  while(f->i < f->ret)
    {
      sha_copy((char*)w, &buf[f->i], f);
      //printW((uint32_t*)w);
      //printSW((uint32_t*)w);
      f->i += 128;
      sha512_hash(f);
    }
  print256(sha_append(f), f);
}
//16 bits short of 128 or 256 == 112 or 240
