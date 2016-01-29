#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/includes/libft.h"
#include "includes/ft_malloc.h"

extern metadata_t	malloc_data_g;
extern void			show_alloc_mem(void);

int main() 
{ 
	int		i; 
	char*	tiny; 
	char*	small;
	char*	large;

	i = 0; 
	while (i < 1024) 
	{ 
		tiny = malloc(1024); 
		if (tiny == NULL)
		{
//			printf("i : %d\n", i);
//			ft_putnbr_recursive(i, get_mult(i));
//			ft_putchar('\n');
			show_alloc_mem();
			return (1);
		}
		++i; 
	} 
//	show_alloc_mem();
	return (0); 
} 
