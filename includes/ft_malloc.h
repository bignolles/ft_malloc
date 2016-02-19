/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 18:48:27 by marene            #+#    #+#             */
/*   Updated: 2016/02/19 12:07:56 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdint.h>
# include <stdlib.h>

# define M_OK				0x00
# define M_NOK				0x01

# define MMAP_PROT			PROT_READ | PROT_WRITE
# define MMAP_FLAGS			MAP_ANON | MAP_PRIVATE

# define TINY_PAGES_NB		25
# define SMALL_PAGES_NB		257
# define LARGE_PAGES_NB		4

# define TINY_ATOMIC		16
# define SMALL_ATOMIC		997

# define TINY_MAX_SIZE		994
# define SMALL_MAX_SIZE		4096

# define CLI_DEFAULT		"\e[39m"
# define CLI_RED			"\e[31m"
# define CLI_BLUE			"\e[34m"
# define CLI_GREEN			"\e[32m"

# define DUMP_INC			(int)sizeof(void*)

typedef enum	e_blocksize
{
	TINY = 0,
	SMALL,
	LARGE,
}				t_blocksize;

typedef struct	s_metadata
{
	void		*data_tiny;
	void		*data_tiny_end;
	void		*data_small;
	void		*datas[2];
	void		*datas_end[2];
	size_t		datas_len[2];
	void		**meta_large;
	int			meta_large_len;
	int32_t		max_size[2];
}				t_metadata;

t_metadata		g_malloc_data;

int				pages_init(t_blocksize blk_size);
int				create_meta(void);
int				create_data(void);
int				metadata_init(t_blocksize blk_size);
size_t			get_metapagesize(t_blocksize size);
size_t			get_metapagelen(t_blocksize size);
void			*metadata_retrieve(void *usr_ptr, t_blocksize *blk_size);
int				metadata_add(void *usr_ptr, t_blocksize blk_size);
int				metadata_remove(void *usr_ptr, t_blocksize blk_size);
void			show_alloc_mem(void);
int				get_mult(int32_t nb);
void			putaddr(unsigned long int n);
int32_t			defragment_memory(t_blocksize blk_size);
void			dump_alloc_mem(t_blocksize blk_size);

#endif
