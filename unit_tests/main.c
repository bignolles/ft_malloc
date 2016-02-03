/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 15:58:35 by marene            #+#    #+#             */
/*   Updated: 2016/02/03 11:50:52 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "unit_test.h"

int		main(void)
{
	srand(time(NULL));
	if (unit_malloc() == UNIT_OK)
		printf("malloc() : OK\n");
	else
		printf("malloc() : KO\n");
	if (unit_realloc() == UNIT_OK)
		printf("realloc() : OK\n");
	else
		printf("realloc() : KO\n");
	return (0);
}
