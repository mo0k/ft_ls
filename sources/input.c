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

t_lst_input			*check_input(int ac, char **av, char *all_options, char **options)
{
	int			count;
	int			state;
	t_lst_input	*lst;

	lst = NULL;

	state = 0;
	count = 1;
	while (count < ac)
	{
		if (!state && is_options(av[count]))
		{
			if (!is_option_valid(av[count], all_options) || !stock_options(options, av[count]))
			{
				USAGE
				return (NULL);
			}
			//printf("options trouver valide\n");
		}
		else
		{
			//printf("fichier:%s\n", av[count]);
			if (!(stock_filepath(&lst, av[count])))
				return (NULL);
			state = 1;
		}
		count++;
	}
	if (lst == NULL)
		stock_filepath(&lst, ".");
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
		//printf("address all_options:%p\n", tmp);
		while (*tmp)
		{
		//	printf("options:%c, char:%c\n", *tmp, *str);
			if (*tmp == *str)
			{
	//			printf("OK:%c, char:%c\n", *tmp, *str);
				state = 1;
			}
			tmp++;
		}
		if (!state)
		{
			//printf("options non valide\n");
			//printf("options:%c, char:%c\n", *all_options, *str);
			ft_putstr("./ft_ls: illegal option -- ");
			write(1, str, 1);
			write(1, "\n", 1);
			return (0);
		}
		//Afficher erreur
		//return (0);
		str++;
	}
	//printf("options valide\n");
	return (1);
}

int				stock_options(char **options, char const *str)
{
	if (!*options)
	{
		if (!(*options = ft_strdup((char*)str + 1)))
			return (0);
	}
	else if (!(ft_stracat(options, (char*)str + 1)))
				return (0);
	return (1);
}

int 			stock_filepath(t_lst_input **lst, char const *str)
{
	t_lst_input *tmp;

	if (!(tmp = add_lst_input(lst)))
		return (0);
	tmp->name = (char*)str;
	return (1);
}
