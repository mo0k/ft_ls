/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 21:13:13 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 00:40:02 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_lst_all			*check_input(int ac, char **av, t_opts *all_opts, t_opts **opts)
{
	int			count;
	int			state;
	t_lst_all	*lst;
	char 	*all_options;

	lst = NULL;
	state = 0;
	count = 1;

	if (!(lst = (t_lst_all*)malloc(sizeof(t_lst_all))))
		return (NULL);
	lst->t_file = NULL;
	lst->t_dir = NULL;
	all_options = ft_strjoin(all_opts->sort, all_opts->display);
	while (count < ac)
	{
		if (!state && is_options(av[count]))
		{
			if (!is_option_valid(av[count], all_options) || !stock_options(opts, av[count]))
			{
				USAGE
				return (NULL);
			}
		}
		else
		{
			if (!(check_typefile(lst, av[count], *opts) && lst))
				return (NULL);
			state = 1;
		}
		count++;
	}
	free(all_options);
	if (*opts && (*opts)->sort && (ft_strchr((*opts)->sort, 'r')))
	{
		ft_lstrev(&lst->t_file);
		ft_lstrev(&lst->t_dir);
	}
	if (!lst->t_dir && !lst->t_file)
		if (!check_typefile(lst, ".", *opts))
			return (NULL);
	return (lst);
}

int				is_options(char const *str)
{
	if (!str)
		return (0);
	if (*(str++) == '-')
		return (1);
	else
		return (0);
}

int				is_option_valid(char const *str, char *all_options)
{
	char	*tmp;
	int state;

	str++;
	while (*str)
	{
		state = 0;
		tmp = all_options;
		while (*tmp)
		{
			if (*tmp == *str)
				state = 1;
			tmp++;
		}
		if (!state)
		{
			ft_putstr("./ft_ls: illegal option -- ");
			write(1, str, 1);
			write(1, "\n", 1);
			return (0);
		}
		str++;
	}
	return (1);
}

int			add_char(char **dst, char c)
{
	char			*tmp;
	int 			len;

	if (!dst)
		return (0);
	if (!*dst)
	{
		if (!(*dst = ft_strnew(1)))
			return (0);
		**dst = c;
	}
	else
	{
		len = (int)ft_strlen(*dst);
		if (!(tmp = ft_strnew(len + 1)))
			return (0);
		tmp = ft_strcpy(tmp, *dst);
		tmp[len] = c;
		free(*dst);
		if (!(*dst = ft_strdup(tmp)))
			return (0);
		free(tmp);
	}
	return (1);
}
void 		del_options(t_opts **options)
{
	if (!options && !*options)
		return ;
	if ((*options)->sort)
		free((*options)->sort);
	if ((*options)->display)
		free((*options)->display);
	free(*options);
	*options = NULL;
}

int				stock_options(t_opts **options, char const *str)
{
	if (!*options)
	{
		if (!(*options = (t_opts*)malloc(sizeof(t_opts))))
			return (0);
		(*options)->sort = NULL;
		(*options)->display = NULL;
	}
	while (*str)
	{
		if (*str == 't' || *str == 'r')
		{
			if (!(add_char(&(*options)->sort, *str)))
				return (0);
		}
		else
			if (!(add_char(&(*options)->display, *str)))
				return (0);
		str++;
	}
	return (1);
}

int 			check_typefile(t_lst_all *lst, char const *str, t_opts *opts)//, t_opts *all_opts)
{
	struct stat *s;
	char *error;
	t_lst_file *tmp1;
	t_lst_file *tmp2;
	t_sort_func sort_func[2];

	sort_func[0] = &add_lst_ascii;
	sort_func[1] = &add_lst_time;
	if (!(s = (struct stat*)malloc(sizeof(struct stat))))
		return (0);
	if (lstat(str, s) == -1)
	{
		error = ft_strjoin("ft_ls: ", (char*)str);
		perror(error);
		free(error);
		return (0);
	}
	else
	{
		if(S_ISDIR(s->st_mode))
		{
			if (opts && opts->sort && ft_strchr(opts->sort, 't'))
			{
				if (!(tmp1 = sort_func[1](&lst->t_dir, NULL, s, str)))
					return (0);
				return (1);
			}
			if (!(tmp1 = sort_func[0](&lst->t_dir, NULL, s, str)))
				return (0);
		}
		else
		{
			if (opts && opts->sort && ft_strchr(opts->sort, 't'))
			{
				if (!(tmp2 = sort_func[1](&lst->t_file, NULL, s, str)))
					return (0);
				return (1);
			}
			if (!(tmp2 = sort_func[0](&lst->t_file, NULL, s, str)))
				return (0);
		}
	}
	return (1);
}

int 			stock_filepath(t_lst_file **lst, char const *str, t_opts *opts)//, t_opts *all_opts)
{
	struct stat *s;
	char *error;
	t_lst_file *tmp;
	t_sort_func sort_func[2];

	sort_func[0] = &add_lst_ascii;
	sort_func[1] = &add_lst_time;
	if (!(s = (struct stat*)malloc(sizeof(struct stat))))
		return (0);
	tmp = *lst;
	if (lstat(str, s) == -1)
	{
		error = ft_strjoin("ft_ls: ", (char*)str);
		perror(error);
		free(error);
		return (0);
	}
	else
	{
		if (opts && opts->sort && ft_strchr(opts->sort, 't'))
		{
			if (!(tmp = sort_func[1](lst, NULL, s, str)))
				return (0);
			return (1);
		}
		if (!(tmp = sort_func[0](lst, NULL, s, str)))
			return (0);
	}
	return (1);
}
