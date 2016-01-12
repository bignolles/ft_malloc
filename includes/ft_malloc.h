#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define TINY		0x01
# define SMALL		0x02
# define LARGE		0x04

/*
 * struct metadata_s
 * Structure permettant le stockage des metadonnees relatives aux blocs de
 * memoire ayant ete malloc
 *
 * void* data_tiny -> Pointeur sur le debut de la premiere page de la region
 *     "tiny"
 * void* data_small -> Idem, pour la region small (duh)
 * void* meta_tiny -> pointeur sur le debut de la (les) page(s) de metadonnees
 *     relatives a la region "tiny"
 * void* meta_small -> idem que meta_tiny, pour la region "small"
 * void* meta_large -> C'est bon, t'as compris maintenant?
 */

typedef struct		metadata_s
{
	void*		data_tiny;
	void*		data_small;
	void*		meta_tiny;
	void*		meta_small;
	void*		meta_large;
}					metadata_t;

#endif
