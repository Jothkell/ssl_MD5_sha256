/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2018/12/10 12:35:55 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

uint32_t leftRotate(uint32_t n, uint32_t d)
{
  return (n << d)|(n >> (32 - d)); //easy
}

uint32_t *ft_make_k(void)
{
  uint32_t i;
  uint32_t b[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		  0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		  0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		  0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		  0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		  0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		  0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		  0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		  0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		  0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		  0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		  0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		  0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		  0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		  0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		  0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391

  };
  uint32_t *k;

  k = malloc(sizeof(uint32_t) * 64);
  i = 0;
  while(i < 64)
    {
      k[i] = b[i];
      i++;
    }
  return (k);
}

void print_binary_variable(uint64_t variable, int size)
{
  int i;
  char hold;

  i = size;
  while (--i >= 0)
    {
      hold = 1;
      (variable & (hold << i)) ? (write(1, "1", 1)) : (write(1, "0", 1));
      (i % 4 == 0) ? (write(1, " ", 1)) : (0);
    }
}

void print_binary_string(char *message, int len)
{
  int i;

  i = -1;
  while (++i < len)
    {
      print_binary_variable(message[i], 8);
      printf("%d   \n", i);
    }
}
void	l_ind(char *hold, char *buf, t_flags *f)
{
  while((f->ret % 64) != 0)
    {
      buf[f->ret] = *hold;
      hold++;
      f->ret++;
    }
}

void	b_ind(char *hold, char *buf, t_flags *f)
{
  int j = (TWO_FIFTY(f->det)) ? (7) : (15);
  int k = 0;

  while ((f->ret % 64) != 0 && (j != 7))
    {
      buf[f->ret] = 0;
      //printf("%hhx %d\n", buf[f->ret], f->ret);
      f->ret++;
      k = j;//
      j--;
    }
  while (0 <= j)
    {
      buf[f->ret] = hold[j];
      f->ret++;
      j--;
    }
}

void	accumulate(t_flags *f)
{
  f->a_fin += f->a;
  f->b_fin += f->b;
  f->c_fin += f->c;
  f->d_fin += f->d;
  f->e_fin += f->e;
  f->f_fin += f->f;
  f->g_fin += f->g;
  f->h_fin += f->h;

  f->h0 += f->one;
  f->h1 += f->two;
  f->h2 += f->three;
  f->h3 += f->four;
  f->h4 += f->five;
  f->h5 += f->six;
  f->h6 += f->seven;
  f->h7 += f->eight;
}

void    ft_64pad(char *buf, t_flags *f)
{
  char *hold;
  int debug = 0;

  buf = (f->file) ? (ft_strcpy(buf, f->file)) : (buf);
  f->orig_len += (f->ret * 8);
  hold = (char*)&f->orig_len;
  buf[f->ret++] = -128;
  while (f->ret != 112 && f->ret != 240)
    {
      buf[f->ret] = 0;
      f->ret++;
      debug++;
    }
  if (f->b_ind == 1)
    b_ind(hold, buf, f);
  else
    l_ind(hold, buf, f);
  //print_binary_string((char*)buf, f->ret);

}

void	ft_pad(char *buf, t_flags *f)
{
  char *hold;
  int debug = 0;

  (f->fd == 0 && !f->q && !f->is_ne) ? (printf("%s", buf)) : (0);
  buf = (f->file) ? (ft_strcpy(buf, f->file)) : (buf);
  f->orig_len += (f->ret * 8);
  hold = (char*)&f->orig_len;
  buf[f->ret++] = -128;
  while (f->ret != 56 && f->ret != 120)
    {
      buf[f->ret] = 0;
      f->ret++;
      debug++;
    }
  if (f->b_ind == 1)
    b_ind(hold, buf, f);
  else
    l_ind(hold, buf, f);
  //print_binary_string((char*)buf, f->ret);

}

uint32_t        *ft_make_s(void)
{
  uint32_t b[] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
		  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
		  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
		  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21

  };
  uint32_t *s;
  uint32_t i;

  i = 0;
  s = malloc(sizeof(uint32_t) * 64);
  while (i < 64)
    {
      s[i] = b[i];
      i++;
    }
  return (s);

}

char *append(t_flags *f)
{
  uint32_t *hold;
  int i;

  i = 0;
  hold = malloc(sizeof(uint32_t) * 4);
  hold[0] = f->a_fin;
  hold[1] = f->b_fin;
  hold[2] = f->c_fin;
  hold[3] = f->d_fin;
  return ((char*)hold);
}

void    md5_hash(t_flags *f)
{
  uint32_t i;
  uint32_t F;
  uint32_t g;

  i = 0;
  f->a = f->a_fin;
  f->b = f->b_fin;
  f->c = f->c_fin;
  f->d = f->d_fin;
  while (i < 64)
    {
      //printf("%x %x %x %x\n", f->a, f->b, f->c, f->d);
      F = (i <= 15) ? ((f->b & f->c) | ((~f->b) & f->d)) : (F);
      g = (i <= 15) ? (i) : (g);
      F = (i >= 16 && i <= 31) ? ((f->d & f->b) | ((~f->d) & f->c)) : (F);
      g = (i >= 16 && i <= 31) ? ((5 * i + 1) % 16) : (g);
      F = (i >= 32 && i <= 47) ? (f->b ^ f->c ^ f->d) : (F);
      g = (i >= 32 && i <= 47) ? ((3 * i + 5) % 16) : (g);
      F = (i >= 48 && i <= 63) ? (f->c ^ (f->b | (~f->d))) : (F);
      g = (i >= 48 && i <= 63) ? ((7 * i) % 16) : (g);
      F = F + f->a + f->K[i] + f->M[g];
      f->a = f->d;
      f->d = f->c;
      f->c = f->b;
      f->b = f->b + leftRotate(F, f->s[i]);
      i++;
    }

}

void	initi(t_flags *f)
{
  //f->i = 0;
  f->orig_len = 0;
  f->a_fin = 0x67452301;
  f->b_fin = 0xefcdab89;
  f->c_fin = 0x98badcfe;
  f->d_fin = 0x10325476;
  f->a = 0x67452301;
  f->b = 0xefcdab89;
  f->c = 0x98badcfe;
  f->d = 0x10325476;
}

void        ft_md5(t_flags *f)
{
  char buf[130];
  char *catch;
  uint64_t k[80];

  initi(f);
  f->s = ft_make_s();
  f->K = ft_make_k();
  f->b_ind = 0;
  f->fd = (f->st) ? (uint32_t)open("./del", O_RDONLY) : (f->fd);
  while(64 == (f->ret = read(f->fd, buf, 64)))
    {
      //printf("%x %x %x %x\n", f->a_fin, f->b_fin, f->c_fin, f->d_fin);
      (f->fd == 0 && !f->q) ? (printf("%s", buf)) : (0);
  f->M = (uint32_t*)buf;
  md5_hash(f);
  f->a_fin += f->a;
  f->b_fin += f->b;
  f->c_fin += f->c;
  f->d_fin += f->d;
  f->orig_len += 512;
    }

  int debug = ft_strlen(buf);
  if (f->ret > 0)
    ft_pad(buf, f);
  while (f->i < f->ret)
    {
      f->M = (uint32_t*)&buf[f->i];
      md5_hash(f);
      f->a_fin += f->a;
      f->b_fin += f->b;
      f->c_fin += f->c;
      f->d_fin += f->d;
      f->i += 64;
      //f->ret -= 64;
    }
  catch = append(f);
  ft_putmd5(catch, f);
}

void	ft_putmd5(char *catch, t_flags *f)
{
  int i;

  i = 0;
  
  if(f->st)
    {
    (f->r) ? (0) : (printf("MD5 (\"%s\") = ", f->name));
    }
  else if (!f->p && !f->never)
    {
    (f->r) ? (0) : (printf("MD5 (%s) = ", f->name));
    }

  while (i < 16)
  {
    printf("%02hhx", (unsigned char)catch[i]);
    i++;
  }
  
  if(f->st)
    (f->r) ? (printf(" \"%s\"", f->name)) : (0);
  else if (!f->p)
    (f->r) ? (printf(" %s", f->name)) : (0);
  printf("\n");
}


void	ft_err(t_flags *f)
{
  printf("usage: ft_ssl command [command opts] [command args]\n");
  //return (-1);
}

int     optns(t_flags *f, char **argv)
{
  char *op[] = {"md5", "sha256", "sha224", "sha512", "sha384", NULL};
  void (*fun[]) (t_flags *f) = {ft_md5, sha_256, sha_256, sha_512, sha_512,  NULL};
  int j;

  j = 0;      
  while(j <= 4)
        {
          if (ft_strcmp(op[j], argv[f->i]) == 0)
            {
	      f->det = j;
	      f->alg = fun[j];
	      return (1);
            }
          j++;
        }
 
  //printf("Error: '%s' is an invalid command.\n", argv[1]);
  return (0);
}

void	ft_stdin(t_flags *f, char **argv)
{
  f->fd = 0;
  f->never = 0;
  f->i = 0;
  f->p = 1;
  f->alg(f);
  f->p = 0;
}

void	ft_flags(t_flags *f, char **argv)
{
  f->r = (argv[f->i][1] == 'r') ? (1) : (f->r);
  f->q = (argv[f->i][1] == 'q') ? (1) : (f->q);
}

void	ft_writer(t_flags *f, char **argv)
{

  int i;

  i = 0;
  while (argv[f->i][i] != '\0')
    {
      write(f->fd, &argv[f->i][i], 1);
      i++;
    }

}

void	ft_strin(t_flags *f, char **argv)
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

void	parse(t_flags *f, char **argv, void (**op) (t_flags *f, char **argv))
{
  f->i = 1;
  while(argv[f->i] != NULL)
    {
      f->hold = f->i;
      if (argv[f->i][0] == '-')
	op[(argv[f->i][1])](f, argv);
      else if (!optns(f, argv))
	{
	  if(1 != (f->fd = open(argv[f->i], O_RDONLY)) && !(f->i = 0))
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


void	ass_op(void (**op) (t_flags *f, char **argv))
{
  op['p'] = ft_stdin;
  op['q'] = ft_flags;
  op['r'] = ft_flags;
  op['s'] = ft_strin;//init rest to error handling function, for invalid flag
}

void	ft_quiet(t_flags *f, char **argv)
{
  int i = 0;
  while (argv[i] != NULL)
    {
      f->q = (argv[i][0] == '-' && argv[i][1] == 'q') ? (1) : (f->q);
      i++;
    }
}

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
