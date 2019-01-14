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

void    md5_hash(t_flags *f)
{
  uint32_t        i;
  uint32_t        F;
  uint32_t        g;

  i = 0;
  f->a = f->a_fin;
  f->b = f->b_fin;
  f->c = f->c_fin;
  f->d = f->d_fin;
  while (i < 64)
    {
      //printf("%x %x %x %x\n", f->a, f->b, f->c, f->d);
      F = (i <= 15) ? ((f->b & f->c) | ((~f->b) & f->d)) : (F);
      g = (i <= 15) ? (i) : (g);
      F = (i >= 16 && i <= 31) ? ((f->d & f->b) | ((~f->d) & f->c)) : (F);
      g = (i >= 16 && i <= 31) ? ((5 * i + 1) % 16) : (g);
      F = (i >= 32 && i <= 47) ? (f->b ^ f->c ^ f->d) : (F);
      g = (i >= 32 && i <= 47) ? ((3 * i + 5) % 16) : (g);
      F = (i >= 48 && i <= 63) ? (f->c ^ (f->b | (~f->d))) : (F);
      g = (i >= 48 && i <= 63) ? ((7 * i) % 16) : (g);
      F = F + f->a + f->K[i] + f->M[g];
      f->a = f->d;
      f->d = f->c;
      f->c = f->b;
      f->b = f->b + leftRotate(F, f->s[i]);
      i++;
    }

}

void    ft_putmd5(char *catch, t_flags *f)
{
  int             i;

  i = 0;

  if(f->st)
    {
      (f->r) ? (0) : (printf("MD5 (\"%s\") = ", f->name));
    }
  else if (!f->p && !f->never)
    {
      (f->r) ? (0) : (printf("MD5 (%s) = ", f->name));
    }

  while (i < 16)
    {
      printf("%02hhx", (unsigned char)catch[i]);
      i++;
    }
  if(f->st)
    (f->r) ? (printf(" \"%s\"", f->name)) : (0);
  else if (!f->p)
    (f->r) ? (printf(" %s", f->name)) : (0);
  printf("\n");
}

void    ft_md5(t_flags *f)
{
  char buf[130];
  char *catch;
  uint64_t k[80];

  initi(f);
  f->s = ft_make_s();
  f->K = ft_make_k();
  f->b_ind = 0;
  f->fd = (f->st) ? (uint32_t)open("./del", O_RDONLY) : (f->fd);
  while(64 == (f->ret = read(f->fd, buf, 64)) || (buf[f->ret] = '\0'))
    {
      buf[f->ret] = '\0';
      //printf("%x %x %x %x\n", f->a_fin, f->b_fin, f->c_fin, f->d_fin);
      (f->fd == 0 && !f->q) ? (printf("%s", buf)) : (0);
      f->M = (uint32_t*)buf;
      md5_hash(f);
      f->a_fin += f->a;
      f->b_fin += f->b;
      f->c_fin += f->c;
      f->d_fin += f->d;
      f->orig_len += 512;
    }
  int debug = ft_strlen(buf);
  if (f->ret > 0)
    ft_pad(buf, f);
  while (f->i < f->ret)
    {
      f->M = (uint32_t*)&buf[f->i];
      md5_hash(f);
      f->a_fin += f->a;
      f->b_fin += f->b;
      f->c_fin += f->c;
      f->d_fin += f->d;
      f->i += 64;
      //f->ret -= 64;
    }
  catch = append(f);
  ft_putmd5(catch, f);
}
