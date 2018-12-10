/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkellehe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 17:14:19 by jkellehe          #+#    #+#             */
/*   Updated: 2018/12/09 22:56:30 by jkellehe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hache.h"

//replace all number types with uintXX_t alternative, to reduce bit ambiguity

int leftRotate(int n, unsigned int d) 
{ 
	return (n << d)|(n >> (32 - d)); //easy
}

int	*ft_make_s(void)
{
	int b[] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
			   5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
			   4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
			   6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21

	};
	int *s;
	int i;

	i = 0;
	s = malloc(sizeof(int) * 64);
	while (i < 64)
	{
		s[i] = b[i];
		i++;
	}
	return (s);

}

unsigned int *ft_make_k(void)
{
	int i;
	int b[] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
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
	unsigned int *k;

	k = malloc(sizeof(unsigned int) * 64);
	i = 0;
	while(i < 64)
	{
		k[i] = b[i];
		i++;
	}
	return (k);
}

uint64_t	ft_buttlen(char *file)
{
	uint64_t ret;
	uint64_t i;

	i = 0;
	while (file[i] != '\0')
	{
		i++;
		ret+=8;
	}
	return (ret);
}

void  ft_pad(t_flags *f)
{
    char c = 0x80;//to pad one bit 1000 0000
    char *hold;
	int len;
	char *six_four;

	hold = f->file;
	f->file = ft_strjoin(f->file, &c);
	f->orig_len = ft_buttlen(f->file);
	if (f->orig_len % 512 == 0)
		return ;
	len = f->orig_len % 512;
	c = 0;
	while (len != 448)
	{
		hold = f->file;
		f->file = ft_strjoin(f->file, &c);
		free(hold);
		len += 8;
	}
	six_four = (char*)&f->orig_len; //access 64 bits 8 bits at a time
	len = 0;
	while (len < 8) //add 8 byte representation of the orig_len
	{
        hold = f->file;
        f->file = ft_strjoin(f->file, &six_four[len]);
		free(hold);
		len++;
	}
}

char	*append(t_flags *f)
{
	char *hold;
	char *ret;

	ret = (char*)&f->a;
	hold = ret;
	ret = ft_strjoin(ret, (char*)&f->b);
	free(hold);
	hold = ret;
	ret = ft_strjoin(ret, (char*)&f->c);
	free(hold);
	hold = ret;
	ret = ft_strjoin(ret, (char*)&f->d);
	free(hold);
	return (ret);
}

char *ft_md5(t_flags *f)
{
	unsigned int *k;
	int pos;
	char digest;

	pos = 0;
	f->s = ft_make_s();
	f->K = ft_make_k();

	f->a_fin = 0x67452301; f->b_fin = 0xefcdab89; f->c_fin = 0x98badcfe; f->d_fin = 0x10325476;
	ft_pad(f);//pads up the file
	f->five_twelve = (uint64_t*)f->file;
	while((pos * 64) < f->orig_len) //for every 512 chunk, i is in 64 byte increments, orig_len is in bytes
	{
		f->M = (char*)&f->five_twelve[pos];
		inner_rounds(f);//does 64 rounds 
		f->a_fin += f->a;
		f->b_fin += f->b;
		f->c_fin += f->c;
		f->d_fin += f->d;
		pos++;
	}
	digest = append(f);
}

int main(int argc, char **argv)
{

	char buf[2];
	char *hold;//0 for dest, 1 for hold
	int ret;
	t_flags *f;

	if(argc != 1)
	{
		return(0);
	}

    f = ft_memalloc(sizeof(t_flags));
    hold = NULL;
	f->fd = open(argv[1], O_RDONLY);
	while ((ret = read(f->fd, buf, 1)))
	{
		hold = f->file;
		f->file = ft_strjoin(f->file, buf);
		free(hold);
	}

	hold = ft_md5(flags);//replace with function pointer
	printf("%d\n", hold);
}
