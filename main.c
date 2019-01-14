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

void    ft_stdin(t_flags *f, char **argv)
{
  f->fd = 0;
  f->never = 0;
  f->i = 0;
  f->p = 1;
  f->alg(f);
  f->p = 0;
}

void    ft_writer(t_flags *f, char **argv)
{
  int     i;

  i = 0;
  while (argv[f->i][i] != '\0')
    {
      write(f->fd, &argv[f->i][i], 1);
      i++;
    }
}

void    ft_strin(t_flags *f, char **argv)
{
  //char *hey = "dude";
  remove("./del");
  f->never = 0;
  f->st = 1;
  f->i++;
  f->name = argv[f->i];
  f->st = 1;
  f->fd = (uint32_t)open("./del", O_RDWR | O_CREAT, 00777);
  ft_writer(f, argv);
  //f->fd = fopen(argv[f->i], "r");
  //f->fd = (uint32_t)open(argv[f->i], O_RDONLY);
  f->i = 0;
  f->alg(f);
  f->file = NULL;
  f->st = 0;
  f->hold++;
  close(f->fd);
  remove("./del");
}

void    parse(t_flags *f, char **argv, void (**op) (t_flags *f, char **argv))
{
  f->i = 1;
  while (argv[f->i] != NULL)
    {
      f->hold = f->i;
      if (argv[f->i][0] == '-')
	op[(argv[f->i][1])](f, argv);
      else if (!optns(f, argv))
	{
	  if (1 != (f->fd = open(argv[f->i], O_RDONLY)) && !(f->i = 0))
	    {
	      f->name = argv[f->hold];
	      f->never = 0;
	      f->alg(f);
	    }
	  else
	    printf("%s: No such file or directory\n", argv[f->i]);
	  f->i = f->hold;
	  while(argv[++f->i] != NULL)
	    {
	      printf("%s: No such file or directory\n", argv[f->i]);
	    }
	  return ;
	}
      f->i = f->hold;
      f->i++;
    }
  if (f->never && f->alg != ft_err && (f->is_ne = 1))
    ft_stdin(f, argv);
}

int             main(int argc, char **argv)
{
  t_flags *f;
  char *catch;
  int i;
  uint32_t *hold;
  void (*op[127]) (t_flags *f, char **argv);

  ass_op(op);
  argv[argc] = NULL;
  i = 0;
  if (argc == 1)
    {
      ft_err(f);
      return(1);
    }
  f = malloc(sizeof(t_flags));
  //sha_initi(f);
  f->never = 1;
  f->p = 0; f->st = 0;
  f->i = 0;
  f->orig_len = 0;
  f->file = NULL;
  f->fd = -20;
  f->q = 0; f->r = 0;
  f->alg = ft_err;
  //f->b_ind = 1;
  parse(f, argv, op);

  //printf("\n");
}
