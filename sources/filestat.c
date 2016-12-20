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

char *get_permi(char *nbr, mode_t	m)
{
	char *ret;
	char *tmp;
	int i;
	int j;

	j = 0;
	i = 0;
	ret = ft_strnew(10);
	
	ret[i++] = get_filetype(m);
	tmp = ret + 1;
	while (i < 10)
	{
		tmp = ft_memmove(tmp, convert_permi(nbr[j++]), 3);
		i += 3;
		tmp += 3;
	}
	return (ret);
}

char *convert_permi(char nbr)
{
	if (nbr == '0')
		return ("---");
	if (nbr == '1')
		return ("--x");
	if (nbr == '2')
		return ("-w-");
	if (nbr == '3')
		return ("-wx");
	if (nbr == '4')
		return ("r--");
	if (nbr == '5')
		return ("r-x");
	if (nbr == '6')
		return ("rw-");
	if (nbr == '7')
		return ("rwx");
	else
		return (NULL);
}

char 	get_filetype(mode_t	m)
{
	if (S_ISLNK(m))
		return ('l');
	else if (S_ISREG(m))
		return ('-');
	else if (S_ISDIR(m))
		return ('d');
	else if (S_ISCHR(m))
		return ('c');
	else if (S_ISBLK(m))
		return ('b');
	else if (S_ISFIFO(m))
		return ('p');
	else if (S_ISSOCK(m))
		return ('s');
	else
		return(0);
}

char	*verif_filepath(char *path)
{
	if (!path)
		return (NULL);
	if (path[(int)ft_strlen(path) - 1] == '/')
		return (ft_strdup(path));
	else
		return (ft_strjoin(path, "/"));
}

int 	file_stat(char *path, char *filename, t_lst_file **lst, t_opts *opts)
{
	struct stat *s;
	char *error;
	char *filepath;
	char *tmp_path;
	t_lst_file *tmp;
	t_sort_func sort_func[2];

	sort_func[0] = &add_lst_ascii;
	sort_func[1] = &add_lst_time;
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
	else
	{
		free(filepath);
		if (opts && opts->sort && ft_strchr(opts->sort, 't'))
		{
			if (!(tmp = sort_func[1](lst, NULL, s, filename)))
				return (0);
			return (1);
		}
		if (!(tmp = sort_func[0](lst, NULL, s, filename)))
			return (0);
		lst = &tmp;
	}
	return (1);
}