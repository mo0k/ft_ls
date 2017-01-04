/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 00:40:35 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <colors.h>

void		putstr_color(char *str, mode_t m)
{
	if (S_ISLNK(m))
		ft_putstr(MAGENTA);
	else if (S_ISDIR(m))
		ft_putstr(CYAN);
	else if (S_ISCHR(m) || S_ISBLK(m))
		ft_putstr(YELLOW);
	else if (S_ISFIFO(m))
		ft_putstr(YELLOW);
	else if (S_ISSOCK(m))
		ft_putstr(GREEN);
	else if (m & S_IXUSR || m & S_IXGRP || m & S_IXOTH)
		ft_putstr(RED);
	else
	{
		ft_putstr(str);
		return;
	}
	ft_putstr(str);
	ft_putstr(ENDCOLOR);
}