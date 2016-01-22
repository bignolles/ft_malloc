#include "includes/ft_malloc.h"
#include "libft/includes/libft.h"
#include <unistd.h>

int main() 
{ 
	int i; 
	char *addr; 
	char *addr2; 

	i = 0; 
	while (i < 1024) 
	{ 
//		addr = (char*)malloc(1024); 
		addr2 = (char*)malloc(1024); 
		addr2[0] = 42; 
		i++; 
	} 
	return (0); 
} 
