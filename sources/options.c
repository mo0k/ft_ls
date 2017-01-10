/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 21:13:13 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/11 00:23:29 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		set_opts(t_opts *opts, char const *str)
{
	while (*str)
	{
		if (!set_flags(opts, *str))
			if (!set_flags_bis(opts, *str))
				set_flags_bis_bis(opts, *str);
		str++;
	}
	return (1);
}

int		set_flags(t_opts *opts, const char c)
{
	if (c == '1')
	{
		opts->singlecol = 1;
		opts->longform = 0;
		return (1);
	}
	else if (c == 'l')
	{
		opts->longform = 1;
		opts->singlecol = 0;
		return (1);
	}
	else if (c == 'R')
	{
		opts->recursive = 1;
		return (1);
	}
	else if (c == 'a')
	{
		opts->allsort = 1;
		return (1);
	}
	return (0);
}

int		set_flags_bis(t_opts *opts, const char c)
{
	if (c == 'c')
	{
		opts->statustime = 1;
		opts->accesstime = 0;
		return (1);
	}
	else if (c == 'r')
	{
		opts->reversesort = 1;
		return (1);
	}
	else if (c == 't')
	{
		opts->timesort = 1;
		return (1);
	}
	else if (c == 'u')
	{
		opts->accesstime = 1;
		opts->statustime = 0;
		return (1);
	}
	return (0);
}

int		set_flags_bis_bis(t_opts *opts, const char c)
{
	if (c == 'n')
	{
		opts->numericonly = 1;
		opts->longform = 1;
		return (1);
	}
	if (c == 'G')
	{
		opts->colors = 1;
		return (1);
	}
	if (c == 'o')
	{
		opts->group = 0;
		opts->longform = 1;
		return (1);
	}
	if (c == 'g')
	{
		opts->owner = 0;
		opts->longform = 1;
		return (1);
	}
	return (0);
}

int		init_opts(t_opts **opts)
{
	if (!*opts)
		if (!(*opts = (t_opts*)malloc(sizeof(t_opts))))
			return (0);
	(*opts)->singlecol = 0;
	(*opts)->longform = 0;
	(*opts)->stream = 0;
	(*opts)->accesstime = 0;
	(*opts)->statustime = 0;
	(*opts)->timesort = 0;
	(*opts)->reversesort = 0;
	(*opts)->recursive = 0;
	(*opts)->allsort = 0;
	(*opts)->numericonly = 0;
	(*opts)->colors = 0;
	(*opts)->group = 1;
	(*opts)->owner = 1;
	return (1);
}
