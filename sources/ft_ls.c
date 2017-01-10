/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 00:40:35 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int				main(int ac, char **av)
{
	t_opts		*opts;
	t_lstall	*lst_root;
	t_lstall	*tmp;
	t_sfunc		sfunc;
	t_pfunc		pfunc;

	opts = NULL;
	lst_root = NULL;
	if (!(lst_root = input(ac, av, &opts)))
		return (1);
	sfunc = get_sfunc(opts);
	pfunc = get_pfunc(opts);
	sort(&lst_root->dir, opts, sfunc);
	sort(&lst_root->file, opts, sfunc);
	tmp = lst_root;
	print_root_file(lst_root->file, opts, pfunc);
	if (lst_root->file && lst_root->dir)
		write(1, "\n", 1);
	if (!(browse_first_node(&tmp->dir, opts, pfunc, sfunc)))
		return (1);
	free(opts);
	free(lst_root);
	return (0);
}

void			usage(void)
{
	ft_putstr("usage: ./ft_ls [");
	ft_putstr(OPTIONS);
	ft_putstr("] [file ...]\n");
}
