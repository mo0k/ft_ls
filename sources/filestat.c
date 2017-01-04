/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filestat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 23:32:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/11 23:35:21 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static char		*verif_filepath(char *path)
{
	if (!path)
		return (NULL);
	if (path[(int)ft_strlen(path) - 1] == '/')
		return (ft_strdup(path));
	else
		return (ft_strjoin(path, "/"));
}

int				file_stat(char *path, char *filename, t_lst_file **lst)
{
	struct stat	*s;
	char		*error;
	char		*filepath;
	char		*tmp_path;
	t_lst_file	*tmp;

	if (!(s = (struct stat*)malloc(sizeof(struct stat))))
		return (0);
	if (!(filepath = ft_strjoin((tmp_path = verif_filepath(path)), filename)))
		return (-1);
	free(tmp_path);
	if (lstat(filepath, s) == -1)
	{
		error = ft_strjoin("ft_ls: ", filename);
		perror(error);
		free(error);
		return (0);
	}
	if (!(tmp = add_lst_ascii(lst, NULL, s, filepath)))
		return (0);
	free(filepath);
	lst = &tmp;
	return (1);
}
