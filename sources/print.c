/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int				print(t_file *lst, t_pfunc pfunc, t_opts *opts)
{
	t_file	*current;

	current = lst;
	if (opts && opts->longform && current)
		set_list_to_string(current, opts);
	if (opts && opts->longform && lstlen_custom(current))
		print_totalblocks(current);
	pfunc(current, opts);
	return (1);
}

void			print_header_dir(char *pathdir)
{
	static int	state = 0;

	if (state)
		write(1, "\n", 1);
	if (pathdir)
	{
		ft_putstr(pathdir);
		write(1, ":\n", 2);
	}
	state = 1;
}

void			print_root_dir(t_file *lst, int len, t_pfunc p, t_opts *opts)
{
	t_file		*node;

	node = lst->node;
	if (len == 1 && !lst->state)
	{
		print_header_dir(NULL);
		if (p == &print_longform && lstlen_custom(node))
			print_totalblocks(node);
		p(node, opts);
	}
	else
	{
		print_header_dir(lst->path);
		if (p == &print_longform)
			print_totalblocks(node);
		p(node, opts);
	}
}

void			print_root_file(t_file *f, t_opts *opts, t_pfunc pfunc)
{
	t_file	*current;

	current = f;
	if (opts && opts->longform && current)
		set_list_to_string(current, opts);
	current = f;
	if (f)
	{
		pfunc(current, opts);
		del_lst_file(&f, opts);
	}
}

void			*get_pfunc(t_opts *opts)
{
	if (!opts)
		return (NULL);
	if (opts->singlecol)
		return (&print_singlecol);
	else if (opts->longform)
		return (&print_longform);
	else if (opts->stream)
		return (&print_stream);
	else
		return (NULL);
}
