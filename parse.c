/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2019/01/15 23:51:08 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

int				optns(t_flags *f, char **argv)
{
	const char	*op[] = {"md5", "sha256", "sha224",
		"sha512", "sha384", NULL};
	const void	(*fun[]) (t_flags *f) = {ft_md5, sha_256, sha_256, sha_512,
		sha_512, NULL};
	int			j;

	j = 0;
	while (j <= 4)
	{
		if (ft_strcmp(op[j], argv[f->i]) == 0)
		{
			f->algy = op[j];
			f->det = j;
			f->alg = fun[j];
			return (1);
		}
		j++;
	}
	return (0);
}

void			parse(t_flags *f, char **argv, void (**op) (t_flags *f, char **argv))
{
	while(argv[f->i] != NULL)
	{
		f->hold = f->i;
		if (argv[f->i][0] == '-')
			op[(argv[f->i][1])](f, argv);
		else if (!optns(f, argv))
		{
			if (0 <= (f->fd = open(argv[f->i], O_RDONLY)) && !(f->i = 0))
			{		
				f->name = argv[f->hold];
				f->never = 0;
				f->alg(f);
			}
			else
				ft_printf("%s: No such file or directory\n", argv[f->i]);
			f->i = f->hold;
			while(argv[++f->i] != NULL)
				ft_printf("%s: No such file or directory\n", argv[f->i]);
			return ;
		}
		f->i = f->hold + 1;
	}
	if (f->never && f->alg != ft_err && (f->is_ne = 1))
		ft_stdin(f, argv);
}
