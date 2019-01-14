/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/13 22:21:11 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void		ft_64pad(char *buf, t_flags *f)
{
	char	*hold;

	buf = (f->file) ? (ft_strcpy(buf, f->file)) : (buf);
	f->orig_len += (f->ret * 8);
	hold = (char*)&f->orig_len;
	buf[f->ret++] = -128;
	while (f->ret != 112 && f->ret != 240)
	{
		buf[f->ret] = 0;
		f->ret++;
	}
	if (f->b_ind == 1)
		b_ind(hold, buf, f);
	else
		l_ind(hold, buf, f);
}

void		ft_pad(char *buf, t_flags *f)
{
	char	*hold;

	(f->fd == 0 && !f->q && !f->is_ne) ? (printf("%s", buf)) : (0);
	buf = (f->file) ? (ft_strcpy(buf, f->file)) : (buf);
	f->orig_len += (f->ret * 8);
	hold = (char*)&f->orig_len;
	buf[f->ret++] = -128;
	while (f->ret != 56 && f->ret != 120)
	{
		buf[f->ret] = 0;
		f->ret++;
		if (f->b_ind == 1)
			b_ind(hold, buf, f);
		else
			l_ind(hold, buf, f);
	}
}
