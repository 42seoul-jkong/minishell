/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 01:52:04 by jkong             #+#    #+#             */
/*   Updated: 2022/06/24 11:32:54 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "safe_mem.h"
#include "libft.h"

static const t_state_info			g_parser_state_0[] = {
	{TK_WORD, 8},
	{TK_LESS, 10},
	{TK_GREATER, 11},
	{TK_LESS_LESS, 12},
	{TK_GREATER_GREATER, 13},
	{TK_PAREN_L, 7},
	{TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	{TK_NT_REDIRECTION, 9},
	{TK_NT_SIMPLE_COMMAND, 4},
	{TK_NT_COMMAND, 3},
	{TK_NT_SUBSHELL, 5},
	{TK_NT_LIST, 1},
	{TK_NT_PIPELINE, 2},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_1[] = {
	{TK_OR_OR, 14},
	{TK_AND_AND, 15},
	{TK_EOF, PARSER_ACCEPT},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_2[] = {
	{TK_PAREN_R, -15},
	{TK_OR_OR, -15},
	{TK_AND_AND, -15},
	{TK_EOF, -15},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_3[] = {
	{TK_PAREN_R, -18},
	{TK_OR_OR, -18},
	{TK_AND_AND, -18},
	{TK_OR, 16},
	{TK_EOF, -18},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_4[] = {
	{TK_WORD, 8},
	{TK_LESS, 10},
	{TK_GREATER, 11},
	{TK_LESS_LESS, 12},
	{TK_GREATER_GREATER, 13},
	{TK_PAREN_R, -11},
	{TK_OR_OR, -11},
	{TK_AND_AND, -11},
	{TK_OR, -11},
	{TK_EOF, -11},
	{TK_NT_SIMPLE_COMMAND_ELEMENT, 17},
	{TK_NT_REDIRECTION, 9},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_5[] = {
	{TK_LESS, 10},
	{TK_GREATER, 11},
	{TK_LESS_LESS, 12},
	{TK_GREATER_GREATER, 13},
	{TK_PAREN_R, -12},
	{TK_OR_OR, -12},
	{TK_AND_AND, -12},
	{TK_OR, -12},
	{TK_EOF, -12},
	{TK_NT_REDIRECTION, 19},
	{TK_NT_REDIRECTION_LIST, 18},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_6[] = {
	{TK_WORD, -7},
	{TK_LESS, -7},
	{TK_GREATER, -7},
	{TK_LESS_LESS, -7},
	{TK_GREATER_GREATER, -7},
	{TK_PAREN_R, -7},
	{TK_OR_OR, -7},
	{TK_AND_AND, -7},
	{TK_OR, -7},
	{TK_EOF, -7},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_7[] = {
	{TK_WORD, 8},
	{TK_LESS, 10},
	{TK_GREATER, 11},
	{TK_LESS_LESS, 12},
	{TK_GREATER_GREATER, 13},
	{TK_PAREN_L, 7},
	{TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	{TK_NT_REDIRECTION, 9},
	{TK_NT_SIMPLE_COMMAND, 4},
	{TK_NT_COMMAND, 3},
	{TK_NT_SUBSHELL, 5},
	{TK_NT_LIST, 20},
	{TK_NT_PIPELINE, 2},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_8[] = {
	{TK_WORD, -1},
	{TK_LESS, -1},
	{TK_GREATER, -1},
	{TK_LESS_LESS, -1},
	{TK_GREATER_GREATER, -1},
	{TK_PAREN_R, -1},
	{TK_OR_OR, -1},
	{TK_AND_AND, -1},
	{TK_OR, -1},
	{TK_EOF, -1},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_9[] = {
	{TK_WORD, -2},
	{TK_LESS, -2},
	{TK_GREATER, -2},
	{TK_LESS_LESS, -2},
	{TK_GREATER_GREATER, -2},
	{TK_PAREN_R, -2},
	{TK_OR_OR, -2},
	{TK_AND_AND, -2},
	{TK_OR, -2},
	{TK_EOF, -2},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_10[] = {
	{TK_WORD, 21},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_11[] = {
	{TK_WORD, 22},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_12[] = {
	{TK_WORD, 23},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_13[] = {
	{TK_WORD, 24},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_14[] = {
	{TK_WORD, 8},
	{TK_LESS, 10},
	{TK_GREATER, 11},
	{TK_LESS_LESS, 12},
	{TK_GREATER_GREATER, 13},
	{TK_PAREN_L, 7},
	{TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	{TK_NT_REDIRECTION, 9},
	{TK_NT_SIMPLE_COMMAND, 4},
	{TK_NT_COMMAND, 3},
	{TK_NT_SUBSHELL, 5},
	{TK_NT_PIPELINE, 25},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_15[] = {
	{TK_WORD, 8},
	{TK_LESS, 10},
	{TK_GREATER, 11},
	{TK_LESS_LESS, 12},
	{TK_GREATER_GREATER, 13},
	{TK_PAREN_L, 7},
	{TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	{TK_NT_REDIRECTION, 9},
	{TK_NT_SIMPLE_COMMAND, 4},
	{TK_NT_COMMAND, 3},
	{TK_NT_SUBSHELL, 5},
	{TK_NT_PIPELINE, 26},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_16[] = {
	{TK_WORD, 8},
	{TK_LESS, 10},
	{TK_GREATER, 11},
	{TK_LESS_LESS, 12},
	{TK_GREATER_GREATER, 13},
	{TK_PAREN_L, 7},
	{TK_NT_SIMPLE_COMMAND_ELEMENT, 6},
	{TK_NT_REDIRECTION, 9},
	{TK_NT_SIMPLE_COMMAND, 4},
	{TK_NT_COMMAND, 3},
	{TK_NT_SUBSHELL, 5},
	{TK_NT_PIPELINE, 27},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_17[] = {
	{TK_WORD, -8},
	{TK_LESS, -8},
	{TK_GREATER, -8},
	{TK_LESS_LESS, -8},
	{TK_GREATER_GREATER, -8},
	{TK_PAREN_R, -8},
	{TK_OR_OR, -8},
	{TK_AND_AND, -8},
	{TK_OR, -8},
	{TK_EOF, -8},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_18[] = {
	{TK_LESS, 10},
	{TK_GREATER, 11},
	{TK_LESS_LESS, 12},
	{TK_GREATER_GREATER, 13},
	{TK_PAREN_R, -13},
	{TK_OR_OR, -13},
	{TK_AND_AND, -13},
	{TK_OR, -13},
	{TK_EOF, -13},
	{TK_NT_REDIRECTION, 28},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_19[] = {
	{TK_LESS, -9},
	{TK_GREATER, -9},
	{TK_LESS_LESS, -9},
	{TK_GREATER_GREATER, -9},
	{TK_PAREN_R, -9},
	{TK_OR_OR, -9},
	{TK_AND_AND, -9},
	{TK_OR, -9},
	{TK_EOF, -9},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_20[] = {
	{TK_PAREN_R, 29},
	{TK_OR_OR, 14},
	{TK_AND_AND, 15},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_21[] = {
	{TK_WORD, -3},
	{TK_LESS, -3},
	{TK_GREATER, -3},
	{TK_LESS_LESS, -3},
	{TK_GREATER_GREATER, -3},
	{TK_PAREN_R, -3},
	{TK_OR_OR, -3},
	{TK_AND_AND, -3},
	{TK_OR, -3},
	{TK_EOF, -3},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_22[] = {
	{TK_WORD, -4},
	{TK_LESS, -4},
	{TK_GREATER, -4},
	{TK_LESS_LESS, -4},
	{TK_GREATER_GREATER, -4},
	{TK_PAREN_R, -4},
	{TK_OR_OR, -4},
	{TK_AND_AND, -4},
	{TK_OR, -4},
	{TK_EOF, -4},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_23[] = {
	{TK_WORD, -5},
	{TK_LESS, -5},
	{TK_GREATER, -5},
	{TK_LESS_LESS, -5},
	{TK_GREATER_GREATER, -5},
	{TK_PAREN_R, -5},
	{TK_OR_OR, -5},
	{TK_AND_AND, -5},
	{TK_OR, -5},
	{TK_EOF, -5},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_24[] = {
	{TK_WORD, -6},
	{TK_LESS, -6},
	{TK_GREATER, -6},
	{TK_LESS_LESS, -6},
	{TK_GREATER_GREATER, -6},
	{TK_PAREN_R, -6},
	{TK_OR_OR, -6},
	{TK_AND_AND, -6},
	{TK_OR, -6},
	{TK_EOF, -6},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_25[] = {
	{TK_PAREN_R, -16},
	{TK_OR_OR, -16},
	{TK_AND_AND, -16},
	{TK_EOF, -16},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_26[] = {
	{TK_PAREN_R, -17},
	{TK_OR_OR, -17},
	{TK_AND_AND, -17},
	{TK_EOF, -17},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_27[] = {
	{TK_PAREN_R, -19},
	{TK_OR_OR, -19},
	{TK_AND_AND, -19},
	{TK_EOF, -19},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_28[] = {
	{TK_LESS, -10},
	{TK_GREATER, -10},
	{TK_LESS_LESS, -10},
	{TK_GREATER_GREATER, -10},
	{TK_PAREN_R, -10},
	{TK_OR_OR, -10},
	{TK_AND_AND, -10},
	{TK_OR, -10},
	{TK_EOF, -10},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info			g_parser_state_29[] = {
	{TK_LESS, -14},
	{TK_GREATER, -14},
	{TK_LESS_LESS, -14},
	{TK_GREATER_GREATER, -14},
	{TK_PAREN_R, -14},
	{TK_OR_OR, -14},
	{TK_AND_AND, -14},
	{TK_OR, -14},
	{TK_EOF, -14},
	{TK_ERROR, PARSER_ERROR}
};

static const t_state_info *const	g_parser_state_table[] = {
	g_parser_state_0,
	g_parser_state_1,
	g_parser_state_2,
	g_parser_state_3,
	g_parser_state_4,
	g_parser_state_5,
	g_parser_state_6,
	g_parser_state_7,
	g_parser_state_8,
	g_parser_state_9,
	g_parser_state_10,
	g_parser_state_11,
	g_parser_state_12,
	g_parser_state_13,
	g_parser_state_14,
	g_parser_state_15,
	g_parser_state_16,
	g_parser_state_17,
	g_parser_state_18,
	g_parser_state_19,
	g_parser_state_20,
	g_parser_state_21,
	g_parser_state_22,
	g_parser_state_23,
	g_parser_state_24,
	g_parser_state_25,
	g_parser_state_26,
	g_parser_state_27,
	g_parser_state_28,
	g_parser_state_29,
};

t_parser_state	parser_state(t_parser_state state, t_token_kind token)
{
	const t_state_info	*info = g_parser_state_table[state];
	size_t				i;

	i = 0;
	while (info[i].token != TK_ERROR)
	{
		if (info[i].token == token)
			return (info[i].state);
		i++;
	}
	return (PARSER_ERROR);
}

void	parser_stack_reserve(t_parser *pst, size_t n)
{
	size_t			capacity;
	t_parser_stack	*attach;
	t_parser_stack	*detach;
	size_t			length;

	capacity = pst->stack_capacity;
	if (capacity == 0)
		capacity = 1;
	length = pst->now + 1 - pst->stack_base;
	while (capacity < length + n)
		capacity <<= 1;
	if (capacity == pst->stack_capacity)
		return ;
	attach = calloc_safe(capacity, sizeof(*pst->stack_base));
	detach = pst->stack_base;
	ft_memcpy(attach, detach, pst->stack_capacity * sizeof(*pst->stack_base));
	pst->stack_base = attach;
	free(detach);
	pst->stack_capacity = capacity;
	pst->now = pst->stack_base + length - 1;
}

void	parser_stack_remove_all(t_parser *pst)
{
	while (pst->now > pst->stack_base)
		clear_parser_stack_item(pst->now--);
}
