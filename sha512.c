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


void            sha_512(t_flags *f)
{
  uint64_t w[80];
  char buf[257];
  uint64_t k[80];


  f->w = z_ero(w, f);
  f->K = sha_make_k(k, f);
  while(128 == (f->ret = read(f->fd, buf, 128)))
    {
      sha_copy((char*)w, buf, f);
      sha512_hash(f);
      f->orig_len += 1024;
    }
  if (f->ret > 0)
    ft_pad(buf, f);

  while(f->i < f->ret)
    {
      sha_copy((char*)w, &buf[f->i]);
      printW(w);
      printSW(w);
      f->i += 64;
      sha256_hash(f);
    }
  print256(sha_append(f));
}
