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

int					main(int ac, char **av)
{
	t_options		*options;
	t_lst_all		*lst_root;
	t_lst_all		*tmp;
	t_sort_func		sortfunc;
	t_print_func	printfunc;

	options = NULL;
	lst_root = NULL;
	if (!(lst_root = input(ac, av, &options)))
		return (1);
	sortfunc = get_sort_func(options);
	printfunc = get_print_func(options);
	sort(&lst_root->t_dir, options, sortfunc);
	sort(&lst_root->t_file, options, sortfunc);
	tmp = lst_root;
	print_root_file(lst_root->t_file, options, printfunc);
	if (lst_root->t_file && lst_root->t_dir)
		write(1, "\n", 1);
	if(!(browse_first_node(&tmp->t_dir, options, printfunc, sortfunc)))
		return (1);
	free(options);
	free(lst_root);
	//while(1){};
	return (0);
}
