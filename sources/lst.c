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

t_lst_file		*add_lst_ascii(t_lst_file **f, t_lst_file *prev, struct stat *s, const char *name)
{
	t_lst_file			*new;

	if (!*f)
	{
		if (!(new = (t_lst_file*)malloc(sizeof(t_lst_file))))
			return (NULL);
		set_elem_stat(new, s, (char*)name);
		new->next = NULL;
		new->prev = prev;
		*f = new;
		return (new);
	}
	if (ft_strcmp((*f)->name, (char*)name) > 0)
	{
		if (!(new = (t_lst_file*)malloc(sizeof(t_lst_file))))
			return (NULL);
		set_elem_stat(new, s, (char*)name);
		new->next = *f;
		new->prev = (*f)->prev;
		(*f)->prev = new;
		*f = new;
		return (new);
	}
	return (!(new = *f)) ? (NULL) : (add_lst_ascii(&(new)->next, new, s, name));
}

t_lst_file		*add_lst_time(t_lst_file **f, t_lst_file *prev, struct stat *s, const char *name)
{
	t_lst_file			*new;

	if (!*f)
	{
		if (!(new = (t_lst_file*)malloc(sizeof(t_lst_file))))
			return (NULL);
		set_elem_stat(new, s, (char*)name);
		new->next = NULL;
		new->prev = prev;
		*f = new;
		return (new);
	}
	if ((*f)->s->st_mtime < s->st_mtime)
	{
		if (!(new = (t_lst_file*)malloc(sizeof(t_lst_file))))
			return (NULL);
		set_elem_stat(new, s, (char*)name);
		new->next = *f;
		new->prev = (*f)->prev;
		(*f)->prev = new;
		*f = new;
		return (new);
	}
	new = *f;
	if (!new)
		return (NULL);
	return (add_lst_time(&new->next, new, s, name));
}

void 	ft_lstrev(t_lst_file **f)
{
	t_lst_file *current;
	t_lst_file *tmp;
	t_lst_file *end;

	end = *f;
	current = *f;
	while (current)
	{
		if(!current->next)
			end = current;
		tmp = current->next;
		current->next = current->prev;
		current->prev = tmp;
		current = tmp;
	}
	*f = end;
}

void	set_elem_stat(t_lst_file *elem, struct stat *s, char *name)
{
	if (!(elem->s = (struct stat*)malloc(sizeof(struct stat))))
		return ;
	elem->s = (struct stat*)ft_memmove(elem->s, s, sizeof(struct stat));
	elem->node = NULL;
	elem->name = ft_strdup(name);
	elem->custom_name = ft_strdup(name);
	elem->owner = NULL;
	elem->group = NULL;
	elem->size = NULL;
	elem->date = NULL;
	free(s);
}

void	set_elem_to_string(t_lst_file *elem)
{
	if (!elem)
		return ;
	char *tmp;

	if (!(tmp = ft_itoa_base(elem->s->st_mode, "01234567")))
		return ;
	elem->permi = get_permi(tmp + (ft_strlen(tmp) - 3), elem->s->st_mode);
	free(tmp);
	elem->lnk = ft_itoa((int)elem->s->st_nlink);
	if (!getpwuid(elem->s->st_uid))
		elem->owner = ft_itoa((int)elem->s->st_uid);
	else
		elem->owner = ft_strdup(getpwuid(elem->s->st_uid)->pw_name);
	if (!getgrgid(elem->s->st_gid))
		elem->group = ft_itoa((int)elem->s->st_gid);
	else
		elem->group = ft_strdup(getgrgid(elem->s->st_gid)->gr_name);
	elem->size = ft_itoa((int)elem->s->st_size);
	elem->date = ft_strsub(ctime(&elem->s->st_mtime), 4, 12);
}

void		del_lst_file(t_lst_file **l)
{
	if (!l || !(*l))
		return ;
	if ((*l)->next)
		del_lst_file(&(*l)->next);
	free((*l)->name);
	free((*l)->custom_name);
	free((*l)->s);
	if ((*l)->permi)
		free((*l)->permi);
	if ((*l)->lnk)
		free((*l)->lnk);
	if ((*l)->size)
		free((*l)->size);
	if ((*l)->date)
		free((*l)->date);
	if ((*l)->owner)
		free((*l)->owner);
	if ((*l)->group)
		free((*l)->group);
	if ((*l)->node)
		del_lst_file(&(*l)->node);
	free(*l);
	*l = NULL;
}


void		del_one(t_lst_file **l, t_lst_file *del)
{
	if ((*l) && del)
	{
		if ((*l) == del)
		{
			*l = del->next;
			free(del->name);
			free(del->custom_name);
			if (del->node)
				del_lst_file(&del->node);
			if (del->s)
				free(del->s);
			free(del);
			return ;
		}
		else
			del_one(&(*l)->next, del);
	}
}

int		 lstlen_custom(t_lst_file *lst)
{
	int		ret;
	t_lst_file	*begin;

	ret = 0;
	begin = lst;
	while (begin)
	{
		ret++;
		begin = begin->next;
		if (ret > 1)
			return (ret);
	}
	return (ret);
}

int 		lst_sort(t_lst_file **l)
{
	t_lst_file *current;
	t_lst_file *tmp;
		current = *l;
	while (current)
	{
		if (current->next && current->next->next && ft_strcmp(current->next->name, current->next->next->name) > 0)
		{
			tmp = current->next->next;
			swap_element(&current->next, &tmp);
			current = current->prev;
		}
		else
			current = current->next;
	}
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