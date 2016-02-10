#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdint.h>
# include <stdlib.h>

# define M_OK				0x00
# define M_NOK				0x01

# define MMAP_PROT			PROT_READ | PROT_WRITE
# define MMAP_FLAGS			MAP_ANON | MAP_PRIVATE

# define TINY_PAGES_NB		25//PREVIOUSLY 260 -> PLZ RESTORE AFTER TESTS //512 NOTA: 311 pages -> valeur min pour que le bug n'apparaisse pas. fuuuuu
# define SMALL_PAGES_NB		257 //PREVIOUSLY 4096 SMALL_MAX_SIZE 4 * plus grnd que TINY_MAX_SIZE, donc 4 * plus de pages?
# define LARGE_PAGES_NB		2

# define TINY_ATOMIC		16
# define SMALL_ATOMIC		997 // <- Bidouiller le nombre de pages / les atomic pour que ces derniers soient des puissance de deux (je pense que ce sera plus propre)

# define TINY_MAX_SIZE		994 // PREVIOUSLY 1024 -> RESTORE AFTER TEST PLZ
# define SMALL_MAX_SIZE		4096

/**
 * \struct metadata_s
 * \brief Structure permettant le stockage des metadonnees relatives aux blocs de
 *        memoire ayant ete malloc \n
 *
 *        void* data_tiny -> Pointeur sur le debut de la premiere page de la region
 *        "tiny" \n
 *        void* data_small -> Idem, pour la region small (duh) \n
 *        void* meta_tiny -> pointeur sur le debut de la (les) page(s) de metadonnees
 *        relatives a la region "tiny" \n
 *        void* meta_small -> idem que meta_tiny, pour la region "small" \n
 *        void* meta_large -> C'est bon, t'as compris maintenant?
 */

// TODO: Ajouter une variable global metadata_t malloc_meta_g dans le fichier qui contiendra la definition de la fonction malloc(size_t size)

typedef enum	blocksize_s
{
	TINY = 0,
	SMALL,
	LARGE,
}				blocksize_t;

typedef struct	metadata_s
{
	void*		data_tiny;
	void*		data_tiny_end;
	void*		data_small;
	void*		datas[2];
	void*		datas_end[2];
	size_t		datas_len[2];
	void**		meta_tiny;
	void**		meta_tiny_end;
	void**		meta_small;
	void**		meta_small_end;
	void**		meta_large; // On a meme pas besoin de tenir des metadata sur les larges /!
	void		**meta_pages_start[2];
//	void		*meta_pages_end[2];
	size_t		meta_len[2];
}				metadata_t; // <- globale

metadata_t		malloc_data_g;

int				pages_init(blocksize_t blk_size);	// <- initialise metadata_t
int				create_meta(void);		// |
int				create_data(void);		// |
int				metadata_init(blocksize_t blk_size);
size_t			get_metapagesize(blocksize_t size);
size_t			get_metapagelen(blocksize_t size);
void*			metadata_retrieve(void* usr_ptr, blocksize_t* blk_size);
int				metadata_add(void* usr_ptr, blocksize_t blk_size);
int				metadata_remove(void* usr_ptr, blocksize_t blk_size);
void			show_alloc_mem(void);
int				ft_putnbr_recursive(int32_t nb, int mult);
int				get_mult(int32_t nb);
void			putaddr(unsigned long int n);
void			defragment_memory(blocksize_t blk_size);

void*			ft_malloc(size_t);

#endif
