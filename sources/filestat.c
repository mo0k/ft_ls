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
	//printf("HEREE => nbr:%d\n", nbr);
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

int 	file_stat(char *filename, t_lst_file **lst)
{
	struct stat s;
	char *test1;
	char *error;
	//
	t_lst_file *tmp;

	//if (!(filepath = ft_strjoin((tmp_path = verif_filepath(path)), filename)))
	//	return (-1);
	//free(tmp_path);
	//printf("filename:%s\n", filename);
	if (lstat(filename, &s) == -1)
	{
		error = ft_strjoin("ft_ls: ", filename);
		perror(error);
		free(error);
		return (0);
	}
	else
	{

		tmp = *lst;
		tmp = add_lst_file(lst, NULL);

		if (!(test1 = ft_itoa_base(s.st_mode, "01234567")))
			return (0);
		tmp->permi = get_permi(test1 + (ft_strlen(test1) - 3), s.st_mode);
		free(test1);
		tmp->lnk = ft_itoa((int)s.st_nlink);
		tmp->owner = getpwuid(s.st_uid)->pw_name;
		tmp->group = getgrgid(s.st_gid)->gr_name;
		tmp->size = ft_itoa((int)s.st_size);
		tmp->date = ft_strsub(ctime(&s.st_mtime), 4, 12);
		tmp->name = ft_strdup(filename);
		//printf("new:%s, address:%p\n", tmp->name, tmp);
	}
	//free(filepath);
	return (1);
}