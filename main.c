

#include "hache.h"

int main(int argc, char **argv)
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
  //ft_quiet(f, argv);
  f = malloc(sizeof(t_flags));
  //sha_initi(f);
  f->never = 1; f->is_ne = 0;
  f->p = 0; f->st = 0;
  f->i = 0;
  f->orig_len = 0;
  f->file = NULL;
  f->fd = -20;
  f->q = 0; f->r = 0;
  f->alg = ft_err;
  //f->b_ind = 1;
  //ft_quiet(f, argv);
  parse(f, argv, op);

  //printf("\n");
}
