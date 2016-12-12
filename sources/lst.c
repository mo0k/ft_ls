/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_lst_file		*add_lst_file(t_lst_file **f, t_lst_file *prev)
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
		new->prev = prev;
		*f = new;
		return (new);
	}
	new = *f;
	if (!new)
		return (NULL);
	return (add_lst_file(&new->next, new));
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

void 		print_lst_file(t_lst_file *f)
{
	t_lst_file			*tmp;

	tmp = f;
	while (tmp)
	{
		//printf("%p\t", tmp);
		ft_putstr(tmp->permi);
		write(1, "  ", 2);
		ft_putstr(tmp->lnk);
		write(1, " ", 1);
		ft_putstr(tmp->owner);
		write(1, "  ", 2);
		ft_putstr(tmp->group);
		write(1, "  ", 2);
		ft_putstr(tmp->size);
		write(1, " ", 1);
		ft_putstr(tmp->date);
		write(1, " ", 1);
		ft_putstr(tmp->name);
		write(1, "\n", 1);
		//printf("%s  %s %s  %s  %s %s %s\n", tmp->permi, tmp->lnk, tmp->owner, tmp->group, tmp->size, tmp->date, tmp->name);
		//ft_putstr(tmp->name);
		//ft_putchar('\n');
		tmp = tmp->next;
	}
}

void 		print_lst_input(t_lst_input *f)
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

void		del_one(t_lst_file **l, t_lst_file *del)
{
	//printf("start del_one ==> &lst_file:%p, tmp->tfile:%p\n", *l, del);
	if ((*l))
	{
		if ((*l) == del)
		{
			//if (del->next)
			*l = del->next;
			free(del);
			return ;
		}
		else
			del_one(&(*l)->next, del);
	}
}

int 		lst_sort(t_lst_file **l)
{
	t_lst_file *current;
	t_lst_file *tmp;
	//t_lst_file *tmp3;

	current = *l;
	while (current)
	{
		//printf("current:%p, current->next:%p\n", current, current->next);
		if (current->next && current->next->next && ft_strcmp(current->next->name, current->next->next->name) > 0)
		{
			tmp = current->next->next;
			//printf("1 - current:%p, current->next:%p, current->next->next:%p\n", current, current->next, current->next->next);
			
			swap_element(&current->next, &tmp);
			//printf("2 - current:%p, current->next:%p, current->next->next:%p\n", current, current->next, current->next->next);
			current = current->prev;
		}
		else
			current = current->next;
	}
	//printf("current:%p\n", current);
	return (1);
}

void	swap_element(t_lst_file **elem1, t_lst_file **elem2)
{
	t_lst_file *tmp1;
	t_lst_file *tmp2;

	tmp1 = *elem1;
	tmp2 = (*elem2)->next;

	*elem1 = *elem2;
	*elem2 = tmp1;

	(*elem1)->next = *elem2;
	(*elem2)->next = tmp2;
 
}
/*
			tmp2 = tmp->next;
			printf("2 - tmp:%p, tmp->next:%p, tmp->next->next:%p\n", tmp, tmp->next, tmp->next->next);
			tmp->next = tmp2->next;
			tmp2->next = tmp;
			printf("3 - tmp:%p, tmp->next:%p, tmp->next->next:%p\n", tmp, tmp->next, tmp->next->next);
		
			tmp = tmp2;
			//printf("2 - tmp:%p, tmp->next:%p\n", tmp, tmp->next);
			printf("4 - tmp:%p, tmp->next:%p, tmp->next->next:%p\n", tmp, tmp->next, tmp->next->next);
			tmp = *l;
			//printf("3 - tmp:%p, tmp->next:%p\n", tmp, tmp->next);*/
			//tmp = *l;