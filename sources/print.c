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

int print(t_lst_file *lst, t_print_func print_func)
{
	t_lst_file *current;

	current = lst;
	while (current)
	{
		set_elem_to_string(current);
		current = current->next;
	}
	current = lst;
	print_func(current);
	return (1);
}

void 	*get_print_func(t_opts *options)
{
	t_print_func print_func[3];
	char display[3];
	int i;
	int save = 2;
	char *tmp = NULL;

	display[0] = 'l';
	display[1] = '1';
	display[2] = 0;
	print_func[0] = &print_option_l;
	print_func[1] = &print_option_1;
	print_func[2] = &print_normal;
	i = 0;
	while (display[i])
	{
		if (options && options->display && (tmp < ft_strrchr(options->display, display[i])))
		{
			tmp = ft_strrchr(options->display, display[i]);
			save = i;
		}
		i++;
	}
	return (print_func[save]);
}

void 	print_header_dir(char *pathdir, int state)
{
	if (state)
		write(1, "\n", 1);
	ft_putstr(pathdir);
	write(1, ":\n", 2);
}

void 	print_first_node(t_lst_file *lst, int len, int *state, t_print_func print_func)
{
	t_lst_file *node;
	node = lst->node;
	while (node)
	{
		set_elem_to_string(node);
		node = node->next;
	}
	node = lst->node;
	if (len == 1){
		print_func(node);
	}
	else
	{
		print_header_dir(lst->name, *state);
		print_func(node);
		*state = 1;
	}
}

void 		print_option_l(t_lst_file *f)
{
	t_lst_file			*tmp;

	tmp = f;
	set_padding_long(&tmp);
	//if (tmp->node)
	//{
		ft_putstr("total ");
		ft_putnbr(get_total_blocks(tmp));
		write(1, "\n", 1);
//	}
	while (tmp)
	{
		ft_putstr(tmp->permi);
		write(1, "  ", 2);
		ft_putstr(tmp->lnk);
		write(1, " ", 1);
		ft_putstr(tmp->owner);
		write(1, "  ", 2);
		ft_putstr(tmp->group);
		write(1, "  ", 2);
		ft_putstr(tmp->size);
		write(1, " ", 1);
		ft_putstr(tmp->date);
		write(1, " ", 1);
		ft_putstr(tmp->custom_name);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void 		print_option_1(t_lst_file *f)
{
	t_lst_file			*tmp;

	tmp = f;
	while (tmp)
	{
		ft_putstr(tmp->custom_name);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}

void 		print_normal(t_lst_file *f)
{
	t_lst_file			*tmp;

	tmp = f;

	set_padding_normal(&f);
	while (tmp)
	{
		ft_putstr(tmp->custom_name);
		write(1, " ", 1);
		tmp = tmp->next;
	}
	ft_putchar('\n');
}

void 		print_root_file(t_lst_file *f, t_opts *opts, t_print_func print_func)
{
	t_lst_file *current;
	current = f;
	while (current)
	{
		if (opts && opts->display && ft_strchr(opts->display, 'l'))
			set_elem_to_string(current);
		current = current->next;
	}
	current = f;
	print_func(current);
	if (f)
		ft_putchar('\n');
	del_lst_file(&f);
}

