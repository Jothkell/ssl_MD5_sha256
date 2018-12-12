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
	uint8_t		fd;
	int		ret;
	char *file;
	uint32_t *M;
	uint32_t *s;
	uint32_t *K;
  	uint64_t orig_len;

	uint32_t a_fin;
	uint32_t b_fin;
	uint32_t c_fin;
	uint32_t d_fin;
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;
};


void    inner_rounds(t_flags *f);
void    ft_putmd5(char *catch);
