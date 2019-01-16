/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/16 14:14:19 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

int				optns(t_flags *f, char **argv)
{
	const char	*op[] = {"md5", "sha256", "sha224",
		"sha512", "sha384", NULL};
	const void	(*fun[]) (t_flags *f) = {(const void(*)(t_flags *))ft_md5,
		(const void(*)(t_flags *))sha_256, (const void(*)(t_flags *))sha_256,
		(const void(*)(t_flags *))sha_512,
		(const void(*)(t_flags *))sha_512, NULL};
	int			j;

	j = 0;
	while (j <= 4)
	{
		if (ft_strcmp(op[j], argv[f->i]) == 0)
		{
			f->algy = (char*)op[j];
			f->det = j;
			f->alg = (void (*)(t_flags *))fun[j];
			return (1);
		}
		j++;
	}
	return (0);
}

void			parse(t_flags *f, char **a, void (**op) (t_flags *f, char **a))
{
	while (a[f->i] != NULL)
	{
		f->hold = f->i;
		if (a[f->i][0] == '-')
			op[(a[f->i][1])](f, a);
		else if (!optns(f, a))
		{
			if (0 <= (f->fd = open(a[f->i], O_RDONLY)))
			{
				f->i = 0;
				f->name = a[f->hold];
				f->never = 0;
				f->alg(f);
			}
			else
				ft_printf("%s: No such file or directory\n", a[f->i]);
			f->i = f->hold;
			while (a[++f->i] != NULL)
				ft_printf("%s: No such file or directory\n", a[f->i]);
			return ;
		}
		f->i = f->hold + 1;
	}
	if (f->never && f->alg != ft_err && (f->is_ne = 1))
		ft_stdin(f, a);
}
