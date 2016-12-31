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

#include <input.h>

t_lst_all		*input(int ac, char **av, t_options **opts)
{
	int			count;
	int			state;
	t_lst_all	*lst;

	lst = NULL;
	state = 0;
	count = 1;
	if (!(lst = (t_lst_all*)malloc(sizeof(t_lst_all))))
		return (NULL);
	lst->t_file = NULL;
	lst->t_dir = NULL;
	init_options(opts);
	if (!check_input(ac, av, lst, opts))
		return (NULL);
	if ((*opts)->singlecol == 0 && (*opts)->longform == 0)
		(*opts)->stream = 1;
	if (!lst->t_dir && !lst->t_file)
		if (!check_typefile(lst, "."))
			return (NULL);
	//display_opts(*opts);
	return (lst);
}

int				check_input(int ac, char **av, t_lst_all *lst, t_options **opts)
{
	int			state;
	int			count;

	state = 0;
	count = 1;
	while (count < ac)
	{
		if (!state && is_options(av[count]))
		{
			if (!is_option_valid(av[count], OPTIONS) || !set_options(*opts, av[count]))
			{
				USAGE
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
	//free(all_options);
	return (1);
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
	char		*tmp;
	int 		state;

	while (*++str)
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
	}
	return (1);
}

void				display_opts(t_options *opts)
{
	printf("singlecol:%d\n", opts->singlecol);
	printf("longform:%d\n", opts->longform);
	printf("stream:%d\n", opts->stream);
	printf("accesstime:%d\n", opts->accesstime);
	printf("statustime:%d\n", opts->statustime);
	printf("timesort:%d\n", opts->timesort);
	printf("reversesort:%d\n", opts->reversesort);
	printf("recursive:%d\n", opts->recursive);
	printf("allsort:%d\n", opts->allsort);
}

int 				check_typefile(t_lst_all *lst, char const *str)
{
	//printf("str:%s\n", str);
	struct stat	*s;
	char 		*error;
	t_lst_file	*tmp;

	if (!(s = (struct stat*)malloc(sizeof(struct stat))))
		return (0);
	if (lstat(str, s) == -1)
	{
		(error = ft_strjoin("ft_ls: ", (char*)str)) ? perror(error) : NULL;
		free(error);
		return (0);
	}
	else
	{
		if(S_ISDIR(s->st_mode))
		{
			if (!(tmp = add_lst_ascii(&lst->t_dir, NULL, s, (char*)str)))
				return (0);
		}
		else
		{
			if (!(tmp = add_lst_ascii(&lst->t_file, NULL, s, (char*)str)))
				return (0);
		}
	}
	return (1);
}

