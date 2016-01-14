/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:47:16 by marene            #+#    #+#             */
/*   Updated: 2016/01/14 11:23:26 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "unit_tests.h"
#include "ft_malloc.h"

static void		launch_unit(char* test_name)
{
	char*	errmsg;

	printf("%s: ", test_name);
	if (ft_strcmp(test_name, TEST_METADATA) == 0)
	{
		tryint(UNIT_NOK, unit_metadata(&errmsg), errmsg);
		printf("OK");
	}
	else
	{
		printf("No such test");
	}
	printf("\n");
}

int				main(void)
{
	launch_unit(TEST_METADATA);
}
