/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2018/12/10 12:35:55 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "hache.h"

int     smthing_thr(t_flags *f)
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

uint32_t leftRotate(uint32_t n, uint32_t d)
{
  return (n << d)|(n >> (32 - d)); //easy
}

void    ft_err(t_flags *f)
{
  ft_printf("usage: ft_ssl command [command opts] [command args]\n");
  //return (-1);
}
