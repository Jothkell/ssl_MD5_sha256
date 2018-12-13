/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hache.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:00:15 by jkellehe          #+#    #+#             */
/*   Updated: 2018/12/10 15:14:49 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"


typedef struct s_ap			t_flags;

struct			s_ap
{
	uint32_t       	fd;
	int		ret;
	char *file;
	uint32_t *M;
	uint32_t *s;
	uint32_t *K;
  	uint64_t orig_len;
 	uint8_t i;
	uint32_t a_fin;
	uint32_t b_fin;
	uint32_t c_fin;
	uint32_t d_fin;
  	uint32_t e_fin;
  	uint32_t f_fin;
  	uint32_t g_fin;
  	uint32_t h_fin;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
  	uint32_t e;
  	uint32_t f;
  	uint32_t g;
  	uint32_t h;
  uint32_t ch;
  uint32_t temp1;
  uint32_t maj;
  uint32_t temp2;
  uint32_t *w;
};


void    md5_hash(t_flags *f);
void    ft_putmd5(char *catch, t_flags *f); 
void    ft_pad(char *buf, t_flags *f);
void            sha_256(t_flags *f);
