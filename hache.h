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
  uint64_t	s0;
  uint64_t	s1;
  int fd2;
  char *name;
  void (*alg) (t_flags *f);
	int       	fd;
	int		ret;
	char *file;
  char *algy;
  int hold;
  uint32_t *K;
  uint8_t is_ne;
  uint8_t never;
  uint8_t p;
  uint8_t q;
  uint8_t r;
  uint8_t st;
  //uint8_t s;
  uint8_t det;
	uint32_t *M;
  uint32_t *s;
	uint64_t *k;
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
  uint64_t *W;
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
  uint32_t ch;
  uint32_t nine;
  uint32_t temp1;
  uint32_t maj;
  uint32_t temp2;
  uint32_t *w;
  uint32_t b_ind;


};

void    ass_op(void (**op) (t_flags *f, char **argv));
void    parse(t_flags *f, char **argv, void (**op) (t_flags *f, char **argv));
void        ft_md5(t_flags *f);
char *append(t_flags *f);
uint32_t        *ft_make_s(void);
uint32_t *ft_make_k(void);
uint64_t        *sha_make_k(uint64_t *k, t_flags *f);
void    initi(t_flags *f);
uint32_t leftRotate(uint32_t n, uint32_t d);
void    ft_strin(t_flags *f, char **argv);
void    ft_writer(t_flags *f, char **argv);
void    ft_flags(t_flags *f, char **argv);
void    ft_stdin(t_flags *f, char **argv);
void    ft_quiet(t_flags *f, char **argv);
void     ft_err(t_flags *f);
int     smthing_thr(t_flags *f);
uint64_t rR64(uint64_t w, uint64_t r);
void    ft_64pad(char *buf, t_flags *f);
void            sha_512(t_flags *f);
int            sha_init_abc(t_flags *f);
int            sub_hash(t_flags *f);
uint32_t rR(uint32_t w, uint32_t r);
uint32_t                *z_ero(uint32_t *w, t_flags *f);
uint64_t        *sha_make_k(uint64_t *k, t_flags *f);
void	accumulate(t_flags *f);
void    sha_initi(t_flags *f);
void    md5_hash(t_flags *f);
void    ft_putmd5(char *catch, t_flags *f); 
void    ft_pad(char *buf, t_flags *f);
void            sha_256(t_flags *f);
void    sha_copy(char *w, char *buf, t_flags *f);
void            printSW(uint32_t *w);
void            printW(uint32_t *w);
char *sha_append(t_flags *f);
void    print256(char *p, t_flags *f);
