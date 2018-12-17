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

# define TWO_FIFTY(c) (c != 3 && c != 4)

typedef struct s_ap			t_flags;

struct			s_ap
{
  void (*alg) (t_flags *f);
	uint32_t       	fd;
	int		ret;
	char *file;
  uint8_t p;
  uint8_t q;
  uint8_t r;
  //uint8_t s;
  uint8_t det;
	uint32_t *M;
	uint32_t *s;
	uint64_t *K;
  //uint32_t *k;
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
  uint64_t W;
  uint64_t h0;
  uint64_t h1;
  uint64_t h2;
  uint64_t h3;
  uint64_t h4;
  uint64_t h5;
  uint64_t h6;
  uint64_t h7;
  uint64_t one; //a
  uint64_t two; //b
  uint64_t three; //c
  uint64_t four; //d
  uint64_t five; //e
  uint64_t six; //f
  uint64_t seven; //g
  uint64_t eight; //h
  uint64_t cha;
  uint64_t t1;
  uint64_t t2;
  uint64_t mj;
  uint32_t nine;
  uint32_t temp1;
  uint32_t maj;
  uint32_t temp2;
  uint32_t *w;
  uint32_t b_ind;


};

void	accumulate(t_flags *f);
void    sha_initi(t_flags *f);
void    md5_hash(t_flags *f);
void    ft_putmd5(char *catch, t_flags *f); 
void    ft_pad(char *buf, t_flags *f);
void            sha_256(t_flags *f);
