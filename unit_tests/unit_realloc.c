/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_realloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 13:09:49 by marene            #+#    #+#             */
/*   Updated: 2016/02/03 12:06:12 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "unit_test.h"
#include "ft_malloc.h"

static int		test_integrity(int seed, int max, int* array)
{
	int		i = 0;

	if (array == NULL)
	{
		ft_putendl("integrity test failed : NULL pointer");
		return (UNIT_NOK);
	}
	while (i < max)
	{
		if (array[i] != seed * i + seed)
		{
			ft_putstr("integrity test failed : ");
			ft_putnbr_recursive(array[i], get_mult(array[i]));
			ft_putstr(" vs ");
			ft_putnbr_recursive(seed * i + seed, get_mult(seed * i + seed));
			ft_putstr("[");
			ft_putnbr_recursive(max, get_mult(max));
			ft_putendl("]");
			return (UNIT_NOK);
		}
		array[i] = seed * i + seed;
		++i;
	}
	return (UNIT_OK);
}

static int		realloc_test_shrink()
{
	int		seed = (rand() % MAX_SEED) + 1;
	int		len = SMALL_MAX_SIZE + 1;
	int*	ptr = malloc(sizeof(int) * len);
	int		i = 0;

	ft_putendl("realloc_test_shrink()");
	while (i < len)
	{
		ptr[i] = seed * i + seed;
		++i;
	}
	while (--len != 0)
	{
		ptr = realloc(ptr, sizeof(int) * len);
		if (test_integrity(seed, len - 1, ptr) == UNIT_NOK)
			return (UNIT_NOK);
	}
	return (UNIT_OK);
}

static int		realloc_test_enlarge()
{
	int		seed = (rand() % MAX_SEED) + 1;
	int		len = 1;
	int*	ptr = malloc(sizeof(int) * len);
	int		i = 0;

	ft_putendl("realloc_test_enlarge()");
	while (i < len)
	{
		ptr[i] = seed * i + seed;
		++i;
	}
	while (++len <= SMALL_MAX_SIZE + 1)
	{
		ptr = realloc(ptr, sizeof(int) * len);
		if (test_integrity(seed, len - 1, ptr) == UNIT_NOK)
			return (UNIT_NOK);
		ptr[len - 1] = seed * (len - 1) + seed;
	}
	return (UNIT_OK);
}

int				unit_realloc(void)
{
	
	if (realloc_test_enlarge() == UNIT_OK && realloc_test_shrink() == UNIT_OK)
		return (UNIT_OK);
	else
		return (UNIT_NOK);
}
