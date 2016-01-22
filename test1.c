#include <unistd.h>
#include <stdlib.h>

int main() 
{ 
	int i; 
	char *addr2; 

	i = 0; 
	while (i < 1024) 
	{ 
		addr2 = (char*)malloc(1024); 
		if (addr2 == NULL)
			return (1);
		++i; 
	} 
	return (0); 
} 
