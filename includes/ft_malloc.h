/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 18:48:27 by marene            #+#    #+#             */
/*   Updated: 2016/04/07 17:10:25 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdint.h>
# include <stdlib.h>

# define M_MAGIC			0xdeadbeeb00b13

# define HEADER_CONTROL_STRICT
# ifdef HEADER_CONTROL_STRICT
#  define HEADER_CONTROL(x, y)	check_header(x, y)
# else
#  define HEADER_CONTROL(x, y)	(void)(x);(void)(y)
# endif

# define RICH_OUTPUT
# ifdef RICH_OUTPUT
#  define ORIGIN			__func__
# else
#  define ORIGIN			""
# endif

# define M_OK				0x00
# define M_NOK				0x01

# define MMAP_PROT			PROT_READ | PROT_WRITE
# define MMAP_FLAGS			MAP_ANON | MAP_PRIVATE

# define TINY_PAGES_NB		5//25
# define SMALL_PAGES_NB		24//257
# define LARGE_PAGES_NB		4

# define TINY_ATOMIC		16
# define SMALL_ATOMIC		997

# define TINY_MAX_SIZE		994
# define SMALL_MAX_SIZE		4096

# define CLI_DEFAULT		"\e[39m"
# define CLI_RED			"\e[31m"
# define CLI_BLUE			"\e[34m"
# define CLI_GREEN			"\e[32m"

# define DUMP_INC			(int)(2 * sizeof(void*))

/*
** # define RECORD_FILE_NAME	"./libft_malloc.record"
*/
# ifdef RECORD_FILE_NAME
#  define CALL_RECORD(x) record_allocations(x)
# else
#  define CALL_RECORD(x) (void)x
# endif

/*
** Comment RECORD_FILE_NAME define to disable recording of allocations
*/

typedef enum	e_blocksize
{
	TINY = 0,
	SMALL,
	LARGE,
}				t_blocksize;

typedef struct	s_metadata
{
	void		*data_tiny; // Debut reel de la zone tiny (adresse retournee par mmap)
	void		*data_tiny_end; // fin reelle de la zone tiny
	void		*data_small; // ditto
	void		*data_small_end; // ditto
	void		*datas[2]; // Debut effectif des  zones tiny et small (apres le header)
	void		*datas_end[2]; // Fin effective des zones tiny et small (correspondent a data_*_end dans l'implementation actuelle)
	size_t		datas_len[2]; // Longueurs effectives des zones tiny et small (taille du mmap - sizeof(t_header))
	void		**meta_large; // recap de tous les sets de pages large
	int			meta_large_len;
	int32_t		max_size[2];
	int			record_fd;
}				t_metadata;

t_metadata		g_malloc_data;

typedef struct	s_header
{
	unsigned long int	magic; //M_MAGIC ^ adresse du header
	void				*prev; //Pointeur sur le prochain groupe de pages du bloc (zone effective, apres header)
	void				*next; //Ditto pour la zone precedante
}				t_header;

typedef enum	e_direction
{
	SEG_NONE,
	SEG_PREV,
	SEG_NEXT,
}				t_direction;

int				pages_init(t_blocksize blk_size);
int				create_meta(void);
int				create_data(void);
int				metadata_init(t_blocksize blk_size);
size_t			get_metapagesize(t_blocksize size);
size_t			get_metapagelen(t_blocksize size);
void			*metadata_retrieve(void *usr_ptr, t_blocksize *blk_size);
int				metadata_add(void *usr_ptr, t_blocksize blk_size);
int				metadata_remove(void *usr_ptr, t_blocksize blk_size);
int				get_mult(int32_t nb);
void			show_alloc_mem(void);
void			display_allocs(int fd);
int32_t			defragment_memory(t_blocksize blk_size, void *meta_ptr);
void			*find_allocable_segment(size_t size, t_blocksize blk_size);
void			*header_change_segment(t_header **head, t_direction dir, const char *origin);
void			dump_alloc_mem(t_blocksize blk_size);
int				record_allocations_init();
void			record_allocations();

#endif
