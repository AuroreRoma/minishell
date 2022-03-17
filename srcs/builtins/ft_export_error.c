/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 01:15:24 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/17 13:22:34 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	export_error(t_shell *shell, char *str, int code)
{
	shell->return_status = code;
	if (code == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	if (code == 2)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": invalid option\n", 2);
	}
}

int	export_check_args(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] != '\0')
	{
		export_error(shell, str, 2);
		return (2);
	}
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		export_error(shell, str, 1);
		return (1);
	}
	while (str[++i] && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			export_error(shell, str, 1);
			return (1);
		}
	}
	return (0);
}
