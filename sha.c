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

void    sha_initi(t_flags *f)
{
  f->i = 0;
  f->orig_len = 0;
  f->a_fin = 0x6a09e667;
  f->b_fin = 0xbb67ae85;
  f->c_fin = 0x3c6ef372;
  f->d_fin = 0xa54ff53a;
  f->e_fin = 0x510e527f;
  f->f_fin = 0x9b05688c;
  f->g_fin = 0x1f83d9ab;
  f->h_fin = 0x5be0cd19;
}


uint32_t	*sha_make_k(uint32_t *k)
{
  uint32_t b[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
  };
  int i;

  i = 0;
  while (i < 64)
    {
      k[i] = b[i];
      i++;
    }
  return (k);
}

void		zero(uint32_t *w)
{
  int i = 0;

  while(i < 64)
    {
      w[i] = 0;
      i++;
    }
}

void	sha_copy(uint32_t *w, char *buf)
{
  int i = 0;
  int j = 3;
  int run = 1;

  while (run)
    {
      w[i] = buf[j];
      i++;
      j--;
      if (j == 0)
	j = 7;
      else if (j == 4)
	j = 11;
      else if (j == 8)
	j = 15;
      else if (j == 12)
	run = 0;
    }
}

uint32_t rR(uint32_t w, uint32_t r)
{
  return(((w >> r) | (w << (32 - r))));
}

void	sha_expand(uint32_t *w)
{
  int i = 16;
  uint32_t s0;
  uint32_t s1;

  while (i < 64)
    {
      
      s0 = (rR(w[(i - 15)], 7) ^ rR(w[(i - 15)], 18) ^ rR(w[(i - 15)], 3));
      s1 = (rR(w[(i - 2)], 17) ^ rR(w[(i - 2)], 19) ^ rR(w[(i - 2)], 10));
      w[i] = w[(i - 16)] + s0 + w[(i - 7)] + s1;
      i++;
    }
}

void		sha_init_abc(t_flags *f)
{
  f->a = f->a_fin;
  f->b = f->b_fin;
  f->c = f->c_fin;
  f->d = f->d_fin;
  f->e = f->e_fin;
  f->f = f->f_fin;
  f->g = f->g_fin;
  f->h = f->h_fin;
}

void		sha256_hash(t_flags *f)
{
  int i;
  uint32_t s0;
  uint32_t s1;

  i = 0;
  sha_init_abc(f);
  while (i < 64)
    {
      s1 = (rR(f->e, 6) ^ rR(f->e, 11) ^ rR(f->e, 25));
      f->ch = ((f->e & f->f) ^ ((~f->e) & f->g));
      f->temp1 = f->h + s1 + f->ch + f->K[i] + f->w[i];
      s0 = (rR(f->a, 2) ^ rR(f->a, 13) ^ rR(f->a, 22));
      f->maj = ((f->a & f->b) ^ (f->a & f->c) ^ (f->b & f->c));
      f->temp2 = s0 + f->maj;
      f->h = f->g;
      f->g = f->f;
      f->f = f->e;
      f->e = f->d + f->temp1;
      f->d = f->c;
      f->c = f->b;
      f->b = f->a;
      f->a = f->temp1 + f->temp2;
      i++;
    }
}

char *sha_append(t_flags *f)
{
  uint32_t *ret;
  
  ret = malloc(sizeof(uint32_t) * 8);
  ret[0] = f->h_fin;
  ret[1] = f->g_fin;
  ret[2] = f->f_fin;
  ret[3] = f->e_fin;
  ret[4] = f->d_fin;
  ret[5] = f->c_fin;
  ret[6] = f->b_fin;
  ret[7] = f->a_fin;
  return ((char*)ret);
}

void	print256(char *p)
{
  int i;

  i = 0;
  
  while (i < 32)
    {
      printf("%02hhx", p[i]);
      i++;
    }

}

void		sha_256(t_flags *f)
{
  uint32_t w[64];
  char buf[130];
  uint32_t k[64]; 


  zero(w);
  sha_make_k(k);
  f->K = k;
  f->w = w;
  while(64 == (f->ret = read(f->fd, buf, 64)))
    {
      sha_copy(w, buf);
      sha_expand(w);
      sha256_hash(f);
      f->a_fin += f->a;
      f->b_fin += f->b;
      f->c_fin += f->c;
      f->d_fin += f->d;
      f->e_fin += f->e;
      f->f_fin += f->f;
      f->g_fin += f->g;
      f->h_fin += f->h;
    }
  if (f->ret > 0) 
    ft_pad(buf, f);
  sha_copy(w, buf);
  sha_expand(w);
  sha256_hash(f);
  f->a_fin += f->a;
  f->b_fin += f->b;
  f->c_fin += f->c;
  f->d_fin += f->d;
  f->e_fin += f->e;
  f->f_fin += f->f;
  f->g_fin += f->g;
  f->h_fin += f->h;
  print256(sha_append(f));
}
