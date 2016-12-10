/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/05 14:53:12 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_lst_file		*add_lst(t_lst_file **f)
{
	t_lst_file			*new;

	//printf("IN add_lst\n");
	if (!*f)
	{
		//printf("creation mallion\n");
		if (!(new = (t_lst_file*)malloc(sizeof(t_lst_file))))
			return (NULL);
		new->permi = NULL;
		new->lnk = 0;
		new->owner = NULL;
		new->group = NULL;
		new->size = 0;
		new->date = NULL;
		new->name = NULL;
		new->next = NULL;
		*f = new;
		return (new);
	}
	new = *f;
	if (!new)
		return (NULL);
	return (add_lst(&new->next));
}

void print_lst(t_lst_file *f)
{
	t_lst_file			*tmp;

	tmp = f;
	while (tmp)
	{
		printf("%s  %s %s  %s  %s %s %s\n", tmp->permi, tmp->lnk, tmp->owner, tmp->group, tmp->size, tmp->date, tmp->name);
		//ft_putstr(tmp->name);
		//ft_putchar('\n');
		tmp = tmp->next;
	}
}