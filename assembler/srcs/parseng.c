/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseng.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 18:48:58 by gabshire          #+#    #+#             */
/*   Updated: 2019/06/11 04:20:36 by gabshire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*tablica(int c)
{
	int		i;
	char	*str;

	str = ft_memalloc(4);
	i = 3;
	while(c)
	{
		str[--i] = c % 2;
		c /= 2;
	}
	return (str);
}

int		miniatoi(t_all *all)
{
	unsigned	i;
	int 		s;
	int 		f;
	int 		l;

	s = 0;
	l = 0;
	i = all->i;
	f = all->line[i] == '-' ? 1 : 0;
	f ? ++i : 0;
	while(all->line[i] && all->line[i] >= '0' && all->line[i] <= '9')
	{
		s = s * 10 + all->line[i] - '0';
		++i;
		l = 1;
	}
	!l && f ? ft_error(all, Lexical, Incorrect_int) : 0;
	all->i = i;
	return (s);
}

int scan_met(t_all *all)
{
	unsigned		j;

	j = 0;
	while(LABEL_CHARS[j])
	{
		if (all->line[all->i] != LABEL_CHARS[j])
			++j;
		else
			return (1);
	}
	return (0);
}

void    checkmet(t_all *all, t_type	tp, char size)
{
	unsigned		j;
	unsigned 		i;
	t_tokens		*token;
	int 			f;

	f = tp == LABEL ? 0 : 1; //если не метка то f == 1
	i = all->i;
	if (f && all->line[all->i] != LABEL_CHAR)
		ft_error(all, Syntactic, No_colon_before);
	else if ((f && all->line[all->i] == LABEL_CHAR))
	{
		++all->i;
		i = all->i;
	}
	while(all->line[all->i])
	{
		j = scan_met(all); //j == 0 запрщенный символ
		if (!j)
		{
			if (!f && all->line[all->i] == LABEL_CHAR)
				++all->i;
			else if ((all->line[all->i] == SEPARATOR_CHAR
			|| all->line[all->i] == ALT_COMMENT_CHAR
			|| all->line[all->i] == COMMENT_CHAR) && f)
				break;
			else ft_error(all, Lexical, Wrong_lchar);
			break ;
		}
		++all->i;
	}
	f = !f && all->line[all->i - 1] == LABEL_CHAR ? all->i - i - 1 : all->i - i;
	token = ft_newtokens(all, tp, -1, size);
	token->str = ft_strsub(all->line, i, f);
	ft_tokenspush(&all->temp, token);
}

void 	sep_char(t_all *all, int k)
{
	if (k > 0)
	{
		quick_pass(all);
		all->line[all->i] != SEPARATOR_CHAR ? ft_error(all, Syntactic, No_comma) : ++all->i;
		quick_pass(all);
	}
}

int 	ft_reg(t_all *all, int *k, char size)
{
	int			s;
	unsigned	i;
	t_tokens	*token;

	quick_pass(all);
	if (all->line[all->i] != 'r')
		return (0);
	++all->i;
	i = all->i;
	s = miniatoi(all);
	if (all->i - i > 2 || i - all->i == 0 || s == 0)
		ft_error(all, Lexical, Incorrect_int);
	--k[0];
	token = ft_newtokens(all, REGISTER, -1, size);
	token->str = ft_strsub(all->line, i, all->i - i);
	sep_char(all, k[0]);
	ft_tokenspush(&all->temp, token);
	return (1);
}

int vn_met(t_all *all, t_type tp, int k, char size)
{
	checkmet(all, tp, size);
	sep_char(all, k);
	return (1);
}

int ft_dir(t_all *all, int *k, t_operation op)
{
	unsigned	i;
	t_tokens	*token;
	char		size;

	quick_pass(all);
	size = op == zjmp || op == ldi || op == sti || op == ffork || op == lldi || op == lfork ? 2 : 4;
	if (all->line[all->i] != DIRECT_CHAR)
		return (0);
	if (all->line[all->i + 1] == LABEL_CHAR)
	{
		++all->i;
		return (vn_met(all, DIRLABEL, k[0], size));
	}
	++all->i;
	i = all->i;
	miniatoi(all);
	if (i - all->i == 0)
		return (0);
	--k[0];
	token = ft_newtokens(all, DIRECT, -1, size);
	token->str = ft_strsub(all->line, i, all->i - i);
	sep_char(all, k[0]);
	ft_tokenspush(&all->temp, token);
	return (1);
}

int ft_idir(t_all *all, int *k, char size)
{
	unsigned i;
	t_tokens *token;

	quick_pass(all);
	if (all->line[all->i] == LABEL_CHAR)
		return (vn_met(all, INDIRLABEL, k[0], size));
	i = all->i;
	miniatoi(all);
	if (i - all->i == 0)
		return (0);
	--k[0];
	token = ft_newtokens(all, INDIRECT, -1, size);
	token->str = ft_strsub(all->line, i, all->i - i);
	sep_char(all, k[0]);
	ft_tokenspush(&all->temp, token);
	return (1);
}

void		ft_parseng(t_all *all, t_op a, t_operation op)
{
	char		*v;
	unsigned	j;
	int 		f;
	int			k;

	j = 0;
	k = a.arg_q - 1;
	all->i += ft_strlen((char *)a.cmd);
	while (j < 3)
	{
		all->line[all->i] == SEPARATOR_CHAR ? ++all->i : 0;
		f = 0;
		if (!a.arg_type[j])
			++j;
		else
			{
			v = tablica(a.arg_type[j]);
			quick_pass(all);
			v[0] == 1 ? f = ft_idir(all, &k, IND_SIZE) : 0;
			!f && v[1] == 1 ? f = ft_dir(all, &k, op) : 0;
			!f && v[2] == 1 ? f = ft_reg(all, &k, T_REG) : 0;
			free(v);
			!f ? ft_error(all, Syntactic, Wrong_argument) : ++j;
		}
	}
	last_check(all, 0) ? ft_error(all, Syntactic, Odd_argument) : 0;
}

void			tokens(t_all *all)
{
	t_op		a;
	t_tokens	*token;
	int			i;
	char 		size;

	quick_pass(all);
	i = -1;
	a = operations(all, &i);
	if (!a.cmd[0])
	{
		checkmet(all, LABEL, 0);
		i = -1;
		quick_pass(all);
		if (!all->line[all->i])
		{
			ft_lstpush(&all->parsing, ft_lstnew_ptr(all->temp));
			all->temp = NULL;
			return ;
		}
		a = operations(all, &i);
	}
	!a.cmd[0] ? ft_error(all, Syntactic, Uknown_instr) : 0;
	size = i == live || i == zjmp || i == ffork || i == lfork || i == aff ? 1 : 2;
	token = ft_newtokens(all, INSTRUCTION, i, size);
	token->str = ft_strsub((char *)a.cmd, 0, ft_strlen((char *)a.cmd));
	ft_tokenspush(&all->temp, token);
	ft_parseng(all, a, i);
}

void	parseng(t_all *all)
{
	while (checkform(all))
	{
		if (all->line)
		{
			quick_pass(all);
			tokens(all);
			all->temp ? ft_lstpush(&all->parsing, ft_lstnew_ptr(all->temp)) : 0;
			all->temp = NULL;
			free(all->line);
			all->line = NULL;
		}
	}
	all->i = 0;
	if (!all->parsing /*|| last_check(all, 1)*/)
		ft_error(all, Syntactic, No_last_line);
}