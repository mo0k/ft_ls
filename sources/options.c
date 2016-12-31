/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 21:13:13 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 00:40:02 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

int		set_options(t_options *options, char const *str)
{
	while (*str)
	{
		if (!set_flags(options, *str))
			set_flags_bis(options, *str);
		str++;
	}
	return (1);
}

int		set_flags(t_options *options, const char c)
{
	if (c == '1')
	{
		options->singlecol = 1;
		options->longform = 0;
		return (1);
	}
	else if (c == 'l')
	{
		options->longform = 1;
		options->singlecol = 0;
		return (1);
	}
	else if (c == 'R')
	{
		options->recursive = 1;
		return (1);
	}
	else if (c == 'a')
	{
		options->allsort = 1;
		return (1);
	}
	return (0);
}

int		set_flags_bis(t_options *options, const char c)
{
	if (c == 'c')
	{
		options->statustime = 1;
		options->accesstime = 0;
		return (1);
	}
	else if (c == 'r')
	{
		options->reversesort = 1;
		return (1);
	}
	else if (c == 't')
	{
		options->timesort = 1;
		return (1);
	}
	else if (c == 'u')
	{
		options->accesstime = 1;
		options->statustime = 0;
		return (1);
	}
	return (0);
}

int 	init_options(t_options **opts)
{
	if (!*opts)
		if (!(*opts = (t_options*)malloc(sizeof(t_options))))
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
	return (1);
}
