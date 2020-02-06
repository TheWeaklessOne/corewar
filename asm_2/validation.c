/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stross <stross@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:54:11 by stross            #+#    #+#             */
/*   Updated: 2020/01/15 18:41:25 by stross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*validator(int argc, char **argv)
{
	char	*str;

	if (argc != 2)
		error_usage();
	str = get_string(argv);
	return (str);
}