/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 15:58:35 by marene            #+#    #+#             */
/*   Updated: 2016/01/20 16:05:38 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "unit_test.h"

int		main(void)
{
	if (unit_malloc() == UNIT_OK)
		printf("malloc() : OK\n");
	else
		printf("malloc() : KO\n");
	return (0);
}
