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

void    sha_initi(t_flags *f)
{
  //f->i = 0;
  //f->orig_len = 0;
  f->a_fin = (f->det == 2) ? (0xc1059ed8) : (0x6a09e667);
  f->b_fin = (f->det == 2) ? (0x367cd507) : (0xbb67ae85);
  f->c_fin = (f->det == 2) ? (0x3070dd17) : (0x3c6ef372);
  f->d_fin = (f->det == 2) ? (0xf70e5939) : (0xa54ff53a);
  f->e_fin = (f->det == 2) ? (0xffc00b31) : (0x510e527f);
  f->f_fin = (f->det == 2) ? (0x68581511) : (0x9b05688c);
  f->g_fin = (f->det == 2) ? (0x64f98fa7) : (0x1f83d9ab);
  f->h_fin = (f->det == 2) ? (0xbefa4fa4) : (0x5be0cd19);
  f->h0 = (f->det == 4) ? (0xcbbb9d5dc1059ed8) : (0x6a09e667f3bcc908);
  f->h1 = (f->det == 4) ? (0x629a292a367cd507) : (0xbb67ae8584caa73b);
  f->h2 = (f->det == 4) ? (0x9159015a3070dd17) : (0x3c6ef372fe94f82b);
  f->h3 = (f->det == 4) ? (0x152fecd8f70e5939) : (0xa54ff53a5f1d36f1);
  f->h4 = (f->det == 4) ? (0x67332667ffc00b31) : (0x510e527fade682d1);
  f->h5 = (f->det == 4) ? (0x8eb44a8768581511) : (0x9b05688c2b3e6c1f);
  f->h6 = (f->det == 4) ? (0xdb0c2e0d64f98fa7) : (0x1f83d9abfb41bd6b);
  f->h7 = (f->det == 4) ? (0x47b5481dbefa4fa4) : (0x5be0cd19137e2179);
  //f->file = NULL;
  //f->fd = -20;
  //f->alg = ft_err;
  //
}

int            sha_init_abc(t_flags *f)
{
  f->a = f->a_fin;
  f->b = f->b_fin;
  f->c = f->c_fin;
  f->d = f->d_fin;
  f->e = f->e_fin;
  f->f = f->f_fin;
  f->g = f->g_fin;
  f->h = f->h_fin;
  f->one = f->h0;
  f->two = f->h1;
  f->three = f->h2;
  f->four = f->h3;
  f->five = f->h4;
  f->six = f->h5;
  f->seven = f->h6;
  f->eight = f->h7;
  return (0);
}

uint64_t        *sha_make_k(uint64_t *k, t_flags *f)
{
  const uint64_t b[] = {
    0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b\
    538,
    0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706\
    fbe,
    0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71\
    235,
    0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9\
    c65,
    0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66d\
    fab,
    0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa\
    725,
    0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42\
    aed,
    0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c8514823\
    53b,
    0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5\
    218,
    0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141a\
    b53,
    0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e\
    373,
    0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a643\
    9ec,
    0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea266\
    19c,
    0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c89\
    8a6,
    0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9b\
    ebc,
    0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475\
817
  };
  int i;

  i = 0;
  sha_initi(f);
  while (i < 80)
    {
      k[i] = (TWO_FIFTY(f->det)) ? (b[i] >> 32) : (b[i]);
      i++;
    }
  return (k);
}

uint32_t                *z_ero(uint32_t *w, t_flags *f)
{
  int i = 0;
  int max = (TWO_FIFTY(f->det)) ? (64) : (160);

  //sha_initi(f);
  while(i < max)
    {
      w[i] = 0;
      i++;
    }
  return (w);
}
