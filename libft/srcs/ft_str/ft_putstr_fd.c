/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:17:05 by jwillem-          #+#    #+#             */
/*   Updated: 2019/05/27 22:12:52 by gabshire         ###   ########.fr       */
.fr       */
=======
/*   Updated: 2019/05/27 20:47:46 by gabshire         ###   ########.fr       */
>>>>>>> fb9e556692d728112600df6146e828d5a9e9706a
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
