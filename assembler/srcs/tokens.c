/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabshire <gabshire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:49:19 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/05 17:49:19 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_tokens	*ft_newtokens(t_all *all, unsigned char tp)
{
	t_tokens	*new;

	if (!(new = (t_tokens*)malloc(sizeof(t_tokens))))
		return (NULL);
	new->str = NULL;
	new->next = NULL;
	new->st = all->st;
	new->i = all->i;
	new->tp = tp;
	return (new);
}

void	ft_tokenspush(t_tokens **alst, t_tokens *new)
{
	t_tokens *list;

	if (new)
	{
		if (alst && *alst)
		{
			list = *alst;
			while (list)
			{
				if (list->next)
					list = list->next;
				else
				{
					list->next = new;
					break ;
				}
			}
		}
		else
			*alst = new;
	}
}

void	ft_tokensadd(t_tokens **alst, t_tokens *new)
{
	if (alst && new)
	{
		if (*alst)
			new->next = *alst;
		*alst = new;
	}
}