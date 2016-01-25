#include <unistd.h>
#include <stdlib.h>
#include "libft/includes/libft.h"

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
		//small = malloc(4096);
		//large = malloc(1024 + 4096);
		if (tiny == NULL)
			return (1);
		//else if (small == NULL)
		//	return (2);
		//else if (large == NULL)
		//	return (3);
		//free(tiny);
		//free(small);
		//free(large);
		++i; 
	} 
	return (0); 
} 
