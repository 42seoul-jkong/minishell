/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:25 by jkong             #+#    #+#             */
/*   Updated: 2022/06/23 23:24:48 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

static const t_builtin_info	g_builtins[] = {
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"pwd", &ft_pwd},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{"env", &ft_env},
	{"exit", &ft_exit},
	{NULL, NULL},
};

t_builtin_func	get_builtin(char *cmd)
{
	size_t	i;

	i = 0;
	while (g_builtins[i].key)
	{
		if (ft_strcmp(g_builtins[i].key, cmd) == 0)
			break ;
		i++;
	}
	return (g_builtins[i].pfn);
}
