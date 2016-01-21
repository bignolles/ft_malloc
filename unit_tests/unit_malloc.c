/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:06:32 by marene            #+#    #+#             */
/*   Updated: 2016/01/21 11:54:08 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "unit_test.h"
#include "libft.h" // On sait jamais...

int		unit_malloc(void)
{
	int*	intPtr;
	int		max = 4;
	int		i;

	intPtr = malloc(sizeof(int) * max);
	if (intPtr != NULL)
	{
		i = 0;
		while (i < max)
		{
			intPtr[i] = max * i;
			++i;
		}
		i = 0;
		while (i < max)
		{
			printf("%p [%d]\t%d\n", intPtr, i, intPtr[i]);
			++i;
		}
		return (UNIT_OK);
	}
	return (UNIT_NOK);
}
