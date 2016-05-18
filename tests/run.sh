#!/bin/sh
export DYLD_LIBRARY_PATH='/nfs/2013/m/marene/projects/ft_malloc'
export DYLD_INSERT_LIBRARIES='/nfs/2013/m/marene/projects/ft_malloc/libft_malloc.so'
export DYLD_FORCE_FLAT_NAMESPACE=1
$@
