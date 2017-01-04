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

#include <lst.h>

static void		set_elem_stat(t_lst_file *elem, struct stat *s, char *filepath)
{
	char		*name;
	static int	state = 0;

	init_lstfile(elem);
	(name = ft_strrchr(filepath, '/')) ? name++ : NULL;
	if (!(elem->s = (struct stat*)malloc(sizeof(struct stat))))
		return ;
	elem->s = (struct stat*)ft_memmove(elem->s, s, sizeof(struct stat));
	if (name)
	{
		elem->name = ft_strdup(name);
		elem->custom_name = ft_strdup(name);
	}
	else
	{
		elem->name = ft_strdup(filepath);
		elem->custom_name = ft_strdup(filepath);
	}
	elem->path = ft_strdup(filepath);
	(!state) ? state++ : 1;
	free(s);
}

t_lst_file		*add_lst_ascii(t_lst_file **f, t_lst_file *prev, struct stat *s, char *filepath)
{
	t_lst_file	*new;

	if (!*f)
	{
		if (!(new = (t_lst_file*)malloc(sizeof(t_lst_file))))
			return (NULL);
		set_elem_stat(new, s, filepath);
		new->next = NULL;
		new->prev = prev;
		*f = new;
		return (new);
	}
	if (ft_strcmp((*f)->path, filepath) > 0)
	{
		if (!(new = (t_lst_file*)malloc(sizeof(t_lst_file))))
			return (NULL);
		set_elem_stat(new, s, filepath);
		new->next = *f;
		new->prev = (*f)->prev;
		(*f)->prev = new;
		*f = new;
		return (new);
	}
	return (!(new = *f)) ? (NULL) : (add_lst_ascii(&(new)->next, new, s, filepath));
}

static void		del_longform(t_lst_file *l)
{
	if (l->permi)
		free(l->permi);
	if (l->lnk)
		free(l->lnk);
	if (l->size)
		free(l->size);
	if (l->date)
		free(l->date);
	if (l->owner)
		free(l->owner);
	if (l->group)
		free(l->group);
}

void			del_lst_file(t_lst_file **l, t_options *opts)
{
	if (!l || !(*l))
		return ;
	if ((*l)->next)
		del_lst_file(&(*l)->next, opts);
	free((*l)->name);
	free((*l)->custom_name);
	free((*l)->path);
	free((*l)->s);
	if (opts && opts->longform)
		del_longform((*l));
	if ((*l)->node)
		del_lst_file(&(*l)->node, opts);
	free(*l);
	*l = NULL;
}


void			del_one(t_lst_file **l, t_lst_file *del, t_options *opts)
{
	if ((*l) && del)
	{
		if ((*l) == del)
		{
			*l = del->next;
			free(del->name);
			free(del->custom_name);
			free(del->path);
			if (del->node)
				del_lst_file(&del->node, opts);
			if (del->s)
				free(del->s);
			free(del);
			return ;
		}
		else
			del_one(&(*l)->next, del, opts);
	}
}
