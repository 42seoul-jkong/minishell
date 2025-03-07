/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 02:18:56 by jkong             #+#    #+#             */
/*   Updated: 2022/09/23 03:26:41 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_flag.h"
#include "string_buffer.h"

static size_t	_parse_matched_quote(t_parser *pst, size_t len, char delim)
{
	char		*str;
	size_t		idx;

	str = &pst->str[len];
	idx = 0;
	if (str[idx] == delim)
		idx++;
	while (str[idx] != '\0')
	{
		if (str[idx++] == delim)
			break ;
	}
	if (idx <= 1 || str[idx - 1] != delim)
	{
		pst->error = PE_INCOMPLETED_PAIR;
		pst->str = str;
		return (0);
	}
	return (idx);
}

static t_token_kind	_read_token_word(t_parser *pst)
{
	size_t		len;
	t_str_buf	*buf;
	t_word		word;

	len = 0;
	buf = NULL;
	while (pst->error == PE_SUCCESS && pst->str[len] != '\0'
		&& !has_flag(char_flags(pst->str[len]), CF_BREAK))
	{
		if (has_flag(char_flags(pst->str[len]), CF_QUOTE))
			len += _parse_matched_quote(pst, len, pst->str[len]);
		else
			len++;
	}
	if (pst->error == PE_SUCCESS)
	{
		buf = str_append_raw(buf, pst->str, len);
		pst->str += len;
	}
	word.str = str_dispose(buf);
	free(pst->backup_word.str);
	pst->backup_word = word;
	return (TK_WORD);
}

static t_token_kind	_read_token_meta(t_parser *pst)
{
	char	tok;

	tok = *pst->str++;
	if (tok == '<' && *pst->str == '<' && pst->str++)
		return (TK_LESS_LESS);
	else if (tok == '>' && *pst->str == '>' && pst->str++)
		return (TK_GREATER_GREATER);
	else if (tok == '&' && *pst->str == '&' && pst->str++)
		return (TK_AND_AND);
	else if (tok == '|' && *pst->str == '|' && pst->str++)
		return (TK_OR_OR);
	if (tok == '&')
	{
		pst->error = PE_UNSUPPORTED_TOKEN;
		pst->str--;
	}
	return (tok);
}

static void	_discard(t_parser *pst)
{
	while (has_flag(char_flags(*pst->str), CF_BLANK))
		pst->str++;
	if (*pst->str == '#')
	{
		while (*pst->str != '\0' && *pst->str != '\n')
			pst->str++;
	}
	while (has_flag(char_flags(*pst->str), CF_BLANK))
		pst->str++;
}

t_token_kind	read_token(t_parser *pst)
{
	t_token_kind	result;

	pst->error = PE_SUCCESS;
	if (!pst->str)
		return (TK_EOF);
	result = TK_UNDEFINED;
	_discard(pst);
	if (result == TK_UNDEFINED && *pst->str == '\0')
		result = TK_AGAIN;
	if (result == TK_UNDEFINED && has_flag(char_flags(*pst->str), CF_META))
		result = _read_token_meta(pst);
	if (result == TK_UNDEFINED)
		result = _read_token_word(pst);
	if (pst->error != PE_SUCCESS)
	{
		if (pst->error == PE_INCOMPLETED_PAIR)
			print_err("unexpected token, expected `%c'\n", *pst->str);
		else if (pst->error == PE_UNSUPPORTED_TOKEN)
			print_err("unsupported token `%c'\n", *pst->str);
		else
			print_err("unknown token\n");
		result = TK_ERROR;
	}
	return (result);
}
