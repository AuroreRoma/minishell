/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 01:15:24 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 10:49:50 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	export_no_args(t_shell *shell)
{
	t_env	*tmp;

	sort_env(shell);
	tmp = shell->env_sorted;
	while (tmp)
	{
		printf("declare -x %s\n", tmp->env_full);
		tmp = tmp->sorted_next;
	}
	return (0);
}

char	*ft_join_env(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;
	size_t	i;
	size_t	j;

	len = 0;
	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * len + 2);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i++] = '=';
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

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
