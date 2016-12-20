/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int 	browse_node(t_lst_file **lst, t_opts *options, void (*f)(t_lst_file*))
{
	t_lst_file *tmp;
	int ret;

	tmp = *lst;
	while (tmp)
	{
		if(S_ISDIR(tmp->s->st_mode))
		{
			if(!((ret = browse_dir(tmp->name, &tmp->node, options))))
				return (0);
			if (ret == 1)
			{
				print_header_dir(tmp->name, 1);
				print(tmp->node, f);
				if (options && options->display && ft_strchr(options->display, 'R'))
					if(prepare_path_recursion(tmp))
						if (browse_node(&tmp->node, options, f))
							del_lst_file(&tmp->node);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int 	prepare_path_recursion(t_lst_file *lst)
{
	t_lst_file *tmp;
	t_lst_file *node;
	char *p;

	tmp = lst;
	node = tmp->node;
	while (node)
	{
		if (tmp->name[0] == '/' && ft_strlen(tmp->name) == 1)
		{
			if (!(p = ft_strjoin(tmp->name, node->name)))
				return (0);
		}
		else
		{
			if(!(p = ft_strnew(ft_strlen(tmp->name) + ft_strlen(node->name) + 1)))
					return (0);
				p = ft_strcpy(p, tmp->name);
				p[ft_strlen(tmp->name)] = '/';
				p = ft_strcat(p, node->name);
		}
		free(node->name);
		node->name = p;
		node = node->next;
	}
	return (1);
}
