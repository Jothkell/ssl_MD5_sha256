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

void            sub_hash(t_flags *f)
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
}

void            sha256_hash(t_flags *f)
{
  int i;
  uint32_t s0;
  uint32_t s1;

  i = 16;
  while (i < 64)
    {
      s0 = (rR(f->w[(i - 15)], 7) ^ rR(f->w[(i - 15)], 18) ^ (f->w[(i - 15)] >> 3));
      s1 = (rR(f->w[(i - 2)], 17) ^ rR(f->w[(i - 2)], 19) ^ (f->w[(i - 2)] >> 10));
      f->w[i] = f->w[(i - 16)] + s0 + f->w[(i - 7)] + s1;
      i++;
    }
  i = 0;
  sha_init_abc(f);
  while (i < 64)
    {
      s1 = (rR(f->e, 6) ^ rR(f->e, 11) ^ rR(f->e, 25));
      f->ch = ((f->e & f->f) ^ ((~f->e) & f->g));
      f->temp1 = f->h + s1 + f->ch + f->k[i] + f->w[i];
      s0 = (rR(f->a, 2) ^ rR(f->a, 13) ^ rR(f->a, 22));
      f->maj = ((f->a & f->b) ^ (f->a & f->c) ^ (f->b & f->c));
      f->temp2 = s0 + f->maj;
      sub_hash(f);
      i++;
    }
  accumulate(f);
  //printf("%u %u %u %u %u %u %u %u\n", f->a_fin, f->b_fin, f->c_fin, f->d_fin, f->e_fin, f->f_fin, f->g_fin, f->h_fin);
}

void    print256(char *p, t_flags *f)
{
  int i;
  unsigned int *hold;
  int end;

  i = (TWO_FIFTY(f->det)) ? (31) : (63);
  //i = (f->det == 2) ? (27) : (i);
  end = (f->det == 2) ? (4) : (0);
  end = (f->det == 4) ? (16) : (end);
  while (i >= end)
    {
      printf("%02hhx", p[i]);
      i--;
    }

  printf("\n");

}

void            sha_256(t_flags *f)
{
  uint32_t w[64];
  char buf[130];
  uint64_t k[80];

  f->b_ind = 1;
  f->w = z_ero(w, f);
  f->k = sha_make_k(k, f);
  f->fd = (f->st) ? (uint32_t)open("./del", O_RDONLY) : (f->fd);
  while(64 == (f->ret = read(f->fd, buf, 64))
        || (f->file && ((f->ret = smthing_thr(f)) == 64)))
    {
      sha_copy((char*)w, buf, f);
      sha256_hash(f);
      f->orig_len += 512;
    }
  if (f->ret > 0 || (f->file && f->ret))
    ft_pad(buf, f);

  while(f->i < f->ret)
    {
      sha_copy((char*)w, &buf[f->i], f);
      //printW256(w);
      //printSW256(w);
      f->i += 64;
      sha256_hash(f);
    }
  print256(sha_append(f), f);
}
