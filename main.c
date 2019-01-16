/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/15 21:52:22 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

void			help_main(t_flags *f)
{
	f = malloc(sizeof(t_flags));
	f->never = 1;
	f->is_ne = 0;
	f->p = 0;
	f->st = 0;
	f->i = 0;
	f->orig_len = 0;
	f->file = NULL;
	f->fd = -20;
	f->q = 0;
	f->r = 0;
	f->alg = ft_err;
}

int				main(int argc, char **argv)
{
	t_flags		*f;
	char		*catch;
	int			i;
	uint32_t	*hold;
	void		(*op[127]) (t_flags *f, char **argv);

	ass_op(op);
	argv[argc] = NULL;
	i = 0;
	if (argc == 1)
	{
		ft_err(f);
		return (1);
	}
	help_main(f);
	parse(f, argv, op);
}