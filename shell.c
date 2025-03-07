/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 20:34:05 by jkong             #+#    #+#             */
/*   Updated: 2022/11/12 07:40:42 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "libft.h"
#include "safe_io.h"
#include "safe_mem.h"

extern char		**environ;
sig_atomic_t	g_exit_status;

static void	_eval(t_shell *sh, t_parser *pst, char *rl)
{
	int	success;

	pst->str = rl;
	pst->begin = pst->str;
	pst->error = PE_SUCCESS;
	success = parse(pst);
	if (pst->error == PE_AGAIN)
	{
		pst->str = NULL;
		pst->begin = pst->str;
		pst->error = PE_SUCCESS;
		success = parse(pst);
	}
	if (success & (gather_here_document(pst, sh) == 0))
	{
		sh->next_pipe = NO_PIPE;
		g_exit_status = execute_command(sh, &pst->now->command,
				NO_PIPE, NO_PIPE);
	}
	else if (pst->error != PE_SUCCESS && pst->error != PE_AGAIN)
		g_exit_status = EX_BADUSAGE;
	parser_stack_remove_all(pst);
}

static void	_reader_loop(t_shell *sh, t_parser *pst, int interactive)
{
	char	*rl;

	if (interactive)
		set_signal_handler(1);
	else
		print_err("warning: non-interactive is partial supported.\n");
	while (1)
	{
		if (interactive)
			rl = readline(get_var(sh->var_list, "PS1"));
		else
			rl = readline(NULL);
		if (!rl)
		{
			if (interactive)
				puterr_safe("exit\n");
			break ;
		}
		if (ft_strlen(rl) != 0)
			add_history(rl);
		_eval(sh, pst, rl);
		free(rl);
	}
}

static void	_initialize_var_list(t_list_var **v_list_ptr)
{
	put_var(v_list_ptr, "PS1", "$ ", 0);
	put_var(v_list_ptr, "PS2", "> ", 0);
	put_var(v_list_ptr, "IFS", " \t\n", 0);
}

int	main(int argc, char *argv[])
{
	t_shell		sh;
	t_parser	pst;

	if (argc != 1)
		print_err("warning: option is not supported.\n");
	(void)argv;
	ft_memset(&sh, 0, sizeof(sh));
	ft_memset(&pst, 0, sizeof(pst));
	parser_stack_reserve(&pst, 1);
	_initialize_var_list(&sh.var_list);
	strvec_to_var_list(&sh.var_list, environ, VFV_EXPORTED);
	_reader_loop(&sh, &pst, isatty(STDIN_FILENO));
	dispose_word(&pst.backup_word);
	free(pst.stack_base);
	dispose_var_list(sh.var_list);
	return (g_exit_status);
}

char	*get_ifs(t_list_var *v_list)
{
	char *const	value = get_var(v_list, "IFS");

	if (!value)
		return (" \t\n");
	return (value);
}
