/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/11 06:59:26 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_lst_file		*add_lst_file(t_lst_file **f)
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
	return (add_lst_file(&new->next));
}

t_lst_input		*add_lst_input(t_lst_input **f)
{
	t_lst_input			*new;

	//printf("IN add_lst\n");
	if (!*f)
	{
		//printf("creation mallion\n");
		if (!(new = (t_lst_input*)malloc(sizeof(t_lst_input))))
			return (NULL);
		new->name = NULL;
		new->next = NULL;
		new->tfile = NULL;
		*f = new;
		return (new);
	}
	new = *f;
	if (!new)
		return (NULL);
	return (add_lst_input(&new->next));
}

void 	print_lst_file(t_lst_file *f)
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

void 	print_lst_input(t_lst_input *f)
{
	t_lst_input			*tmp;

	tmp = f;
	while (tmp)
	{
		printf("%s  %p\n", tmp->name, tmp->tfile);
		//ft_putstr(tmp->name);
		//ft_putchar('\n');
		tmp = tmp->next;
	}
}

void		del_lst_file(t_lst_file **l)
{
	if ((*l))
	{
		if ((*l)->next)
			del_lst_file(&(*l)->next);
		//Ajouter free pour chaque string malloc
		free(*l);
	}
	*l = NULL;
}

void		del_lst_input(t_lst_input **l)
{
	if ((*l))
	{
		if ((*l)->next)
			del_lst_input(&(*l)->next);
		//Ajouter free pour chaque string malloc
		free(*l);
	}
	*l = NULL;
}