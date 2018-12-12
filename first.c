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

//replace all number types with uintXX_t alternative, to reduce bit ambiguity

uint32_t leftRotate(uint32_t n, uint32_t d) 
{ 
	return (n << d)|(n >> (32 - d)); //easy
}

uint32_t	*ft_make_s(void)
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

uint64_t	ft_buttlen(t_flags *f)
{
	uint64_t ret;
	uint64_t i;

	i = 0;
	ret = 0;
	while (f->file[i] != '\0')
	{
		i++;
		ret+=8;
		if (((i + 1) % 64) == 0)
			f->chunks++;
	}
	return (ret);
}

char  *bt_cjoin(char const *s1, char s2, t_flags *f)
{
    uint32_t     i;
    uint32_t     j;
    char    *res;

    i = 0;
    j = 0;
    if (!s1)
        return (NULL);
    if (!(res = (char*)malloc(sizeof(s1) + sizeof(char) + 1)))
        return (NULL);
    while (i < (f->curr_len / 8))
    {
        res[i] = s1[i];
        i++;
    }
    res[i] = s2;
    res[(i + 1)] = '\0';
    return (res);
}

char    *bt_strjoin(char const *s1, char const *s2, t_flags *f)
{
    uint32_t     i;
    uint32_t     j;
    char    *res;

    i = 0;
    j = 0;
    if (!s1 || !s2)
        return (NULL);
    if (!(res = (char*)malloc(sizeof(s1) + sizeof(s2) + 1)))
        return (NULL);
    while (s1[i] != '\0')
    {
        res[i] = s1[i];
        i++;
    }
    while (s2[j] != '\0')
    {
        res[i] = s2[j];
        i++;
        j++;
    }
    res[i] = '\0';
    return (res);
}

void  ft_pad(t_flags *f)
{
    char c[] = {0x80, 0x0};//to pad one bit 1000 0000
    char *hold;
	uint32_t len;
	char *six_four;

	hold = f->file;
    f->orig_len = ft_buttlen(f);//in bits
	f->curr_len = f->orig_len;
	f->file = bt_cjoin(f->file, c[0], f);
	if (f->orig_len % 512 == 0)
		return ;
	len = f->orig_len % 512;//the remainder in bits
	f->curr_len = f->orig_len + 8;
	c[0] = 0;
	while (len != 448)
	{
		hold = f->file;
		f->file = bt_cjoin(f->file, c[0], f);
		//free(hold);
		f->curr_len += 8;
		len += 8;
	}
	six_four = (char*)&f->orig_len; //access 64 bits 8 bits at a time
	len = 0;
	while (len < 8) //add 8 byte representation of the orig_len
	{
        hold = f->file;
        f->file = bt_cjoin(f->file, six_four[len], f);
		//free(hold);
		f->curr_len += 8;
		len++;
	}

}

uint32_t	*append(t_flags *f)
{
	char *hold;
	uint32_t *ret;
	uint32_t i = 0;

	ret = malloc(sizeof(uint32_t) * 4);
	ret[0] = f->a_fin;
	ret[1] = f->b_fin;
	ret[2] = f->c_fin;
	ret[3] = f->d_fin;
	return (ret);
}

void	inner_rounds(t_flags *f)
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
		F = (i >= 0 && i <= 15) ? ((f->b & f->c) | ((~f->b) & f->d)) : (F);
		g = (i >= 0 && i <= 15) ? (i) : (g);
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

uint32_t *reverse(char *digest)
{
	int i;
	uint32_t j;
	char *res;

	j = 3;
	i = 0;
	res = malloc(sizeof(char) * 16);
	while(i < 16)
	{
		res[i] = digest[j];
		j--;
		j = (j==-1) ? (7) : (j);
		j = (j==3) ? (11) : (j);
		j = (j==7) ? (15) : (j);
		i++;
	}
	return ((uint32_t*)res);
}

uint32_t	*ft_md5(t_flags *f)
{
	uint32_t *k;
	uint32_t pos;
	char *digest;
	uint32_t *catch;

	pos = 0;
	f->s = ft_make_s();
	f->K = ft_make_k();

	ft_pad(f);//pads up the file
	f->chunky = (uint64_t*)f->file;
	while(pos < f->chunks) //for every 512 chunk, i is in 64 byte increments, orig_len is in bytes
	{
		f->M = (uint32_t*)&f->chunky[(pos * 8)]; //pos * 8 = position in bytes
		inner_rounds(f);//does 64 rounds 
		f->a_fin += f->a;
		f->b_fin += f->b;
		f->c_fin += f->c;
		f->d_fin += f->d;
		pos++; //position in chunks
	}
	//digest 
	catch = append(f);
	//catch = reverse((char*)catch);
	return (catch);
}

int main (int argc, char **argv)
{

	char *buf;
	char *hold;//0 for dest, 1 for hold
	int ret;
	t_flags *f;
	uint32_t *res;

	if(argc != 2)
	{
		return(0);
	}

    f = ft_memalloc(sizeof(t_flags));
	f->file = ft_memalloc(sizeof(char));
    hold = NULL;
	f->fd = open(argv[1], O_RDONLY);
	while (0 < (ret = get_next_line(f->fd, &buf)))
	{
		hold = f->file;
		f->file = ft_strjoin(f->file, buf);
		//free(hold);
	}

	res = ft_md5(f);//replace with function pointer
	printf("%x%x%x%x\n", res[0], res[1], res[2], res[3]);
}
