/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarberi <mbarberi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:50 by mbarberi          #+#    #+#             */
/*   Updated: 2023/02/03 18:21:54 by mbarberi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The isupper(3) function tests for any upper-case letters.
 * @param c The character to test.
 * @return Zero if the character tests false, non-zero if the character
 * tests true.
 */
static int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

/**
 * @brief The tolower(3) function converts an upper-case letter to the
 * corresponding lower-case letter.
 * @param c The character to convert.
 * @return The corresponding lower-case letter if there is one; otherwise,
 * the argument is returned unchanged.
 */
int	ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c + 32);
	else
		return (c);
}
