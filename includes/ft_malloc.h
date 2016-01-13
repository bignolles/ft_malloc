#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define M_OK		0x00
# define M_NOK		0x01

# define TINY_PAGES_NB		512
# define SMALL_PAGES_NB		4096

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

typedef enum		blocksize_s
{
	TINY,
	SMALL,
	LARGE,
}					blocksize_t;

typedef struct		metadata_s
{
	void*		data_tiny;
	void*		data_tiny_end;
	void*		data_small;
	void*		data_small_end;
	void*		meta_tiny;
	void*		meta_tiny_end;
	void*		meta_small;
	void*		meta_small_end;
	void*		meta_large; // On a meme pas besoin de tenir des metadata sur les larges /!
}					metadata_t; // <- globale

int					datapages_init();	// <- initialise metadata_t
int					create_meta();		// |
int					create_data();		// |
void*				metadata_retrieve(void* usr_ptr);
int					metadata_add(void* usr_ptr, blocksize_t size);
int					metadata_remove(void* usr_ptr, blocksize_t size);

#endif
