/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 21:13:13 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/10 02:59:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <input.h>

t_lstall		*input(int ac, char **av, t_opts **opts)
{
	int			count;
	int			state;
	t_lstall	*lst;

	lst = NULL;
	state = 0;
	count = 1;
	if (!(lst = (t_lstall*)malloc(sizeof(t_lstall))))
		return (NULL);
	lst->file = NULL;
	lst->dir = NULL;
	init_opts(opts);
	if (!check_input(ac, av, lst, opts))
		return (NULL);
	if ((*opts)->singlecol == 0 && (*opts)->longform == 0)
		(*opts)->stream = 1;
	if (!lst->dir && !lst->file)
		if (!check_typefile(lst, "."))
			return (NULL);
	return (lst);
}

int				check_input(int ac, char **av, t_lstall *lst, t_opts **opts)
{
	int			state;
	int			count;

	state = 0;
	count = 1;
	while (count < ac)
	{
		if (!state && is_options(av[count]))
		{
			if (!is_option_valid(av[count], OPTIONS) ||
				!set_opts(*opts, av[count]))
			{
				usage();
				return (0);
			}
		}
		else
		{
			if (!(check_typefile(lst, av[count]) && lst))
				return (0);
			state = 1;
		}
		count++;
	}
	return (1);
}

int				is_options(char const *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) > 1 && *(str++) == '-')
		return (1);
	else
		return (0);
}

int				is_option_valid(char const *str, char *all_opts)
{
	char		*tmp;
	int			state;

	while (*++str)
	{
		state = 0;
		tmp = all_opts;
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
	}
	return (1);
}

int				check_typefile(t_lstall *lst, char const *str)
{
	struct stat	*s;
	char		*error;
	t_file		*tmp;

	if (!(s = (struct stat*)malloc(sizeof(struct stat))))
		return (0);
	if (lstat(str, s) == -1)
	{
		(error = ft_strjoin("ft_ls: ", (char*)str)) ? perror(error) : NULL;
		free(s);
		free(error);
		return (0);
	}
	if (S_ISDIR(s->st_mode))
	{
		if (!(tmp = addlst_ascii(&lst->dir, NULL, s, (char*)str)))
			return (0);
	}
	else
	{
		if (!(tmp = addlst_ascii(&lst->file, NULL, s, (char*)str)))
			return (0);
	}
	return (1);
}
