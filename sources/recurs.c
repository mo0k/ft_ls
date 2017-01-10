/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/11 00:23:18 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int			browse_node(t_file **lst, t_opts *opts, t_pfunc p, t_sfunc s)
{
	t_file	*tmp;
	int		ret;
	char	*name;

	tmp = *lst;
	while (tmp)
	{
		(name = ft_strrchr(tmp->path, '/')) ? name++ : NULL;
		if (ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0 &&
			S_ISDIR(tmp->s->st_mode))
		{
			if (!((ret = browse_dir(tmp->path, &tmp->node, opts, s))))
				return (0);
			if (ret == 1)
			{
				print_header_dir(tmp->path);
				print(tmp->node, p, opts);
				if (opts && opts->recursive)
					if (browse_node(&tmp->node, opts, p, s))
						del_lst_file(&tmp->node, opts);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
