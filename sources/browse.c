/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int 	browse_first_node(t_lst_file **lst, t_options *options, t_print_func printfunc, t_sort_func sortfunc)
{
	t_lst_file *tmp;
	int len;
	int state;

	state = 0;
	len = lstlen_custom(*lst);
	tmp = *lst;
	while (tmp)
	{
		if(tmp->s->st_mode && S_ISDIR(tmp->s->st_mode))
		{
			if(!(browse_dir(tmp->path, &tmp->node, options, sortfunc)))
				return (0);
			if (options && options->longform && tmp->node)
				set_list_to_string(tmp->node, options);
			print_first_node(tmp, len, &state, printfunc);

			if (options && options->recursive)
			{
				//if(prepare_path_recursion(tmp))
				//{
					//printf("PREPARE PATH OK\n");
					if (browse_node(&tmp->node, options, printfunc, sortfunc))
						del_lst_file(&tmp->node, options);
				//}
				//else
					//printf("PREPARE PATH KO\n");
			}
		}
		del_one(lst, tmp, options);
		tmp = tmp->next;
	}
	return (1);
}

static int 	browse_dir_error(char *path, t_options *options)
{
	char *error;
	char *name;
	//printf("IN DIR ERRORß\n");
	!(name = ft_strrchr(path, '/')) ? name = path : name++;
	if (options && options->recursive)
	{
		print_header_dir(path, 1);
		error = ft_strjoin("ft_ls: ", name);
		perror(error);
		free(error);
		return (1);
	}
	error = ft_strjoin("ft_ls: ", name);
	perror(error);
	free(error);
	return (0);
}

int 	browse_dir(char *path, t_lst_file **lst, t_options *options, t_sort_func sortfunc)
{
	DIR *dir;
	struct dirent *x;
	//char *hidden;
	//printf("browse dir\n");
	//hidden = NULL;
	dir = opendir(path);
	if (dir == NULL)
		return (browse_dir_error(path, options)) ? (2) : (0);
	while ((x = readdir(dir)))
	{
		//printf("browse dir=>namefile:%s\n", x->d_name);
		if (options && options->allsort)
		{
			if (!file_stat(path, x->d_name, lst))
				return (0);
		}
		else
		{
			if (ft_strchr(x->d_name, '.') != x->d_name)
				if (!file_stat(path, x->d_name, lst))
					return (0);
		}
	}
	sort(lst, options, sortfunc);
	if (closedir(dir) == -1)
		return (0);
	return (1);
}

void	get_total_blocks(t_lst_file *lst)
{
	t_lst_file *current;
	int 	total_blocks;

	total_blocks = 0;
	current = lst;
	while (current)
	{
		total_blocks += current->s->st_blocks;
		current = current->next;
	}
	ft_putstr("total ");
	ft_putnbr(total_blocks);
	write(1, "\n", 1);
}


