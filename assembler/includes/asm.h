/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwillem- <jwillem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 21:47:20 by jwillem-          #+#    #+#             */
/*   Updated: 2019/06/09 21:23:03 by jwillem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"

# define SECURE_MALLOC(a)	!(a) && memory_error()

typedef enum	e_er_type
{
	Lexical,
	Syntactic,
	Semantic
}				t_er_type;

typedef enum	e_case_type
{
	CMD_size_exceeded,
	Wrong_argument,
	Wrong_lchar,
	Odd_argument,
	Bad_CMD_declaration,
	Incorrect_int,
	No_colon_before,
	No_colon_after,
	No_comma,
	Uknown_instr,
	No_last_line
}				t_case_type;

typedef struct	s_error
{
	t_er_type		type;
	t_case_type		reason;
	char			*line;
	int				st;
	int				i;
	struct s_error	*next;
}				t_error;

/*
 * str имя метки, при следующем заходе значение меняется на распознанное число
 */

typedef    enum    e_type
{
	LABEL, // метка
	INSTRUCTION, //инструкция
	DIRECT, //директ
	INDIRECT, // индерект
	REGISTER //регистр
}                t_type;

typedef    enum    e_operation
{
	live,
	ld,
	st,
	add,
	sub,
	and,
	or,
	xor,
	zjmp,
	ldi,
	sti,
	ffork,
	lld,
	lldi,
	lfork,
	aff
}                t_operation;

typedef struct			s_tokens
{
	char 				*str;
	unsigned int		st;
	unsigned int		i;
	t_type				tp;
	t_operation			operation;
	unsigned char		razmer;
	struct 	s_tokens *next;
}						t_tokens;


/*
* fd - файловый дискриптор
* magic - магическое число
* parseng - результат работы парсера
* i - индекс в строке
* st - номер строки
*/

typedef struct			s_all
{
	int				fd;
	char			**split;
	unsigned int	i;
	unsigned int	st;
	char			*line;
	char			*pred_line;
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned int	prog_size;
	t_list			*parsing;
	t_tokens		*temp;
	t_error			*errors;
	t_list			*source;
}						t_all;

/*
 * работа с листами токинов
 */

t_tokens	*ft_newtokens(t_all *all, t_type tp, int instr);
void		ft_tokenspush(t_tokens **alst, t_tokens *new);
void		ft_tokensadd(t_tokens **alst, t_tokens *new);

void		ft_error(t_all *all, t_er_type type, t_case_type reason);
int			last_check(t_all *all, int f);
int			checkform(t_all *all);
void		parseng(t_all *all);
void		quick_pass(t_all *all);
t_op		operations(t_all *all, int *i);

void		print_errors(t_all *all, char *filename);
int			memory_error(void);

// void		assembler(t_all *all);
int			ft_atoi_base(const char *str, int base);

#endif
