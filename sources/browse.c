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

int 	browse_first_node(t_lst_file **lst, t_opts *options, void (*f)(t_lst_file*))
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
			if(!(browse_dir(tmp->name, &tmp->node, options)))
				return (0);

			print_first_node(tmp, len, &state, f);
			if (options && options->display && ft_strchr(options->display, 'R'))
				if(prepare_path_recursion(tmp))
					if (browse_node(&tmp->node, options, f))
						del_lst_file(&tmp->node);
		}
		del_one(lst, tmp);
		tmp = tmp->next;
	}
	return (1);
}

static int 	browse_dir_error(char *path, t_opts *options)
{
	char *error;

	if (options && options->display && ft_strchr(options->display, 'R'))
	{
		print_header_dir(path, 1);
		error = ft_strjoin("ft_ls: ", ft_strrchr(path, '/') + 1);
		perror(error);
		free(error);
		return (1);
	}
	error = ft_strjoin("ft_ls: ", ft_strrchr(path, '/') + 1);
	perror(error);
	free(error);
	return (0);
}

int 	browse_dir(char *path, t_lst_file **lst, t_opts *options)
{
	DIR *dir;
	struct dirent *x;
	char *hidden;

	hidden = NULL;
	dir = opendir(path);
	if (dir == NULL)
		return (browse_dir_error(path, options)) ? (2) : (0);
	while ((x = readdir(dir)))
	{
		if (options && options->display && (hidden = ft_strchr(options->display, 'a')))
			if (!file_stat(path, x->d_name, lst, options))
				return (0);
		if (!hidden)
			if (ft_strchr(x->d_name, '.') != x->d_name)
				if (!file_stat(path, x->d_name, lst, options))
					return (0);
	}
	if (options && options->sort && (ft_strchr(options->sort, 'r')))
		ft_lstrev(lst);
	if (closedir(dir) == -1)
		return (0);
	return (1);
}

int		get_total_blocks(t_lst_file *lst)
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
	return (total_blocks);
}


