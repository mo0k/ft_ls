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

static void		put_background(mode_t m)
{
	if (m & S_IXUSR && m & S_ISUID)
		ft_putstr(B_RED);
	else if ((m & S_IXGRP && m & S_ISGID) || S_ISBLK(m))
		ft_putstr(B_CYAN);
	else if (S_ISCHR(m) || (m & S_IWOTH && !(m & S_ISVTX) && S_ISDIR(m)))
		ft_putstr(B_YELLOW);
	else if (m & S_IWOTH && m & S_ISVTX && S_ISDIR(m))
		ft_putstr(B_GREEN);
}

static void		put_foreground(mode_t m)
{
	if ((m & S_IXUSR && m & S_ISUID) || (m & S_IXGRP && m & S_ISGID) ||
		(S_ISDIR(m) && m & S_IWOTH))
		ft_putstr(T_BLACK);
	else if (S_ISDIR(m))
		ft_putstr(T_CYAN);
	else if (S_ISLNK(m))
		ft_putstr(T_MAGENTA);
	else if (S_ISCHR(m) || S_ISBLK(m))
		ft_putstr(T_BLUE);
	else if (S_ISFIFO(m))
		ft_putstr(T_YELLOW);
	else if (S_ISSOCK(m))
		ft_putstr(T_GREEN);
	else if (m & S_IXUSR || m & S_IXGRP || m & S_IXOTH)
		ft_putstr(T_RED);
}

void			put_color(char *str, mode_t m)
{
	int			foreground;
	int			background;

	foreground = 0;
	background = 0;
	if (S_ISLNK(m) || S_ISDIR(m) || S_ISCHR(m) || S_ISBLK(m) || S_ISFIFO(m) ||
		m & S_IXUSR || m & S_IXGRP || m & S_IXOTH || m & S_IWOTH)
		foreground = 1;
	if ((m & S_IXUSR && m & S_ISUID) || (m & S_IXGRP && m & S_ISGID) ||
		(m & S_IXOTH && m & S_ISVTX) || S_ISCHR(m) || S_ISBLK(m) ||
		(m & S_IWOTH))
		background = 1;
	if (background)
		put_background(m);
	if (foreground)
		put_foreground(m);
	ft_putstr(str);
	if (background)
		ft_putstr(B_END);
	if (foreground)
		ft_putstr(T_END);
}
