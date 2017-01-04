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

int				print(t_lst_file *lst, t_print_func print_func, t_options *opts)
{
	t_lst_file	*current;

	current = lst;
	if (opts && opts->longform && current)
		set_list_to_string(current, opts);
	if (opts && opts->longform && lstlen_custom(current))
		print_totalblocks(current);
	print_func(current, opts);
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

void			print_root_dir(t_lst_file *lst, int len, t_print_func print_func, t_options *opts)
{
	t_lst_file	*node;

	node = lst->node;
	if (len == 1 && !lst->state)
	{
		print_header_dir(NULL);
		if (print_func == &print_longform && lstlen_custom(node))
			print_totalblocks(node);
		print_func(node, opts);
	}
	else
	{
		print_header_dir(lst->path);
		if (print_func == &print_longform)
			print_totalblocks(node);
		print_func(node, opts);
	}
}

void			print_root_file(t_lst_file *f, t_options *opts, t_print_func print_func)
{
	t_lst_file	*current;

	current = f;
	if (opts && opts->longform && current)
		set_list_to_string(current, opts);
	current = f;
	if (f)
	{
		print_func(current, opts);
		del_lst_file(&f, opts);
	}
}
