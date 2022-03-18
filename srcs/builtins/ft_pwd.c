/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroma <aroma@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 17:22:57 by pblagoje          #+#    #+#             */
/*   Updated: 2022/03/18 12:03:08 by aroma            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	shell->return_status = 0;
	return (0);
}
