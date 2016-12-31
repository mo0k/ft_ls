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

int 	browse_node(t_lst_file **lst, t_options *options, t_print_func printfunc, t_sort_func sortfunc)
{
	//printf("IN Browse dir\n");
	t_lst_file *tmp;
	int ret;
	char *name;

	tmp = *lst;
	while (tmp)
	{
		//name = ft_strrchr(tmp->name, '/') + 1;
		//printf("avant name:%s\n", tmp->path);
		(name = ft_strrchr(tmp->path, '/')) ? name++ : NULL;
		//printf("apres name:%s\n", name);
		if(ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0 && S_ISDIR(tmp->s->st_mode))
		{
			if(!((ret = browse_dir(tmp->path, &tmp->node, options, sortfunc))))
				return (0);
			if (ret == 1)
			{
				print_header_dir(tmp->path, 1);
				print(tmp->node, printfunc, options);
				if (options && options->recursive)
				{
					//if(prepare_path_recursion(tmp))
						if (browse_node(&tmp->node, options, printfunc, sortfunc))
							del_lst_file(&tmp->node, options);
				}
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int 	prepare_path_recursion(t_lst_file *lst)
{
	printf("START prepare path\n");
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
		printf("name:%s\n", node->name);
		printf("custom_name:%s\n", node->custom_name);
		printf("path:%s\n\n", node->path);
		node = node->next;
	}
	return (1);
}
