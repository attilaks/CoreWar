/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eror.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:55:57 by gabshire          #+#    #+#             */
/*   Updated: 2019/05/30 20:30:42 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "op.h"

void	ft_error(int er)
{
	er == 0 ? ft_printf("clean file\n") : 0;
	er == 1 ? ft_printf("syntax error\n") : 0;
	exit(1);
}