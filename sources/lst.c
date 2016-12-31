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

t_lst_file		*add_lst_ascii(t_lst_file **f, t_lst_file *prev, struct stat *s, char *filepath)
{
	t_lst_file			*new;
	//printf("TEST\n");
	if (!*f)
	{
		//printf("FISRT\n");
		if (!(new = (t_lst_file*)malloc(sizeof(t_lst_file))))
			return (NULL);
		set_elem_stat(new, s, filepath);
		//printf("FISRT 1\n");
		new->next = NULL;
		new->prev = prev;
		*f = new;
		return (new);
	}
	//printf("cmp => name:%s, name:%s\n",(*f)->name, ft_strrchr(filepath, '/') + 1);
	if (ft_strcmp((*f)->path, filepath) > 0)
	{
		//printf("ADD\n");
		if (!(new = (t_lst_file*)malloc(sizeof(t_lst_file))))
			return (NULL);
		set_elem_stat(new, s, filepath);
		new->next = *f;
		new->prev = (*f)->prev;
		(*f)->prev = new;
		*f = new;
		return (new);
	}
	//printf("NEXT\n");
	return (!(new = *f)) ? (NULL) : (add_lst_ascii(&(new)->next, new, s, filepath));
}

void 	ft_lstrev(t_lst_file **f)
{
	//printf("IN revlst\n");
	t_lst_file *current;
	t_lst_file *tmp;
	t_lst_file *end;

	end = *f;
	current = *f;
	while (current)
	{
		//printf("name:%s\taddress:%p\tnext:%p\tprev:%p\n", current->name, current, current->next, current->prev);
		if(!current->next)
			end = current;
		tmp = current->next;
		current->next = current->prev;
		current->prev = tmp;
		current = tmp;
	}
	*f = end;
	//printf("end of revlst\n");
}

void	set_elem_stat(t_lst_file *elem, struct stat *s, char *filepath)
{
	//printf("START set elem stat\n");
	char *name;
	static int state = 0;
	//printf("filepath:%s\n", filepath);
	(name = ft_strrchr(filepath, '/')) ? name++ : NULL;
	//printf("START set elem stat 1\n");
	if (!(elem->s = (struct stat*)malloc(sizeof(struct stat))))
		return ;
	//printf("START set elem stat 2\n");
	elem->s = (struct stat*)ft_memmove(elem->s, s, sizeof(struct stat));
	elem->node = NULL;
	//printf("START set elem stat 3\n");
	//printf("name:%s\n", name);
	if (name)
	{
		//printf("PAR ICI\n");
		elem->name = ft_strdup(name);
		elem->custom_name = ft_strdup(name);
		//*(name) = 0;
		

	}
	else
	{
		//printf("PAR LA\n");
		elem->name = ft_strdup(filepath);
		elem->custom_name = ft_strdup(filepath);
	}
	elem->path = ft_strdup(filepath);
	//printf("elem->name:%s\n", elem->name);
	//printf("elem->path:%s\n", elem->path);
	//printf("START set elem stat 4\n");
	
	//printf("START set elem stat 5\n");
	//elem->custom_name = ft_strdup(elem->name);
	elem->owner = NULL;
	elem->group = NULL;
	elem->size = NULL;
	elem->date = NULL;
	elem->state = state;
	(!state) ? state++ : 1;
	free(s);
}

void 	set_list_to_string(t_lst_file *lst, t_options *opts)
{
	t_lst_file *node;

	node = lst;
	while (node)
	{
		set_elem_to_string(node, opts);
		node = node->next;
	}
}

static char 	*format_time(t_lst_file *elem, t_options *opts)
{
	char *tmp;

	if (opts && opts->accesstime && opts->timesort){
		return(ft_strsub(ctime(&elem->s->st_atime), 4, 12));
	}
	else if (opts && opts->statustime && opts->timesort)
		return(ft_strsub(ctime(&elem->s->st_ctime), 4, 12));
	else
	{
		//printf("%s:\t\t\tcalcul time:%ld\n",elem->name, time(NULL) - elem->s->st_mtime);
		//printf("time:%ld\n", elem->s->st_mtime);
		//printf("current time:%ld\n", time(NULL));
		//printf("other time:%ld\n", elem->s->st_mtime);
		if (time(NULL) - elem->s->st_mtime > 15778800 || elem->s->st_mtime - time(NULL) > 3600)
		{
			tmp = ft_strnew(12);
			tmp = ft_strncpy(tmp, ctime(&elem->s->st_mtime) + 4, 7);
			tmp = ft_strncat(tmp, ctime(&elem->s->st_mtime) + 19, 5);
			return(tmp);
		}
		return(ft_strsub(ctime(&elem->s->st_mtime), 4, 12));
	}
}

void	set_elem_to_string(t_lst_file *elem, t_options *opts)
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
	/*	if (opts && opts->accesstime && opts->timesort){
		elem->date = ft_strsub(ctime(&elem->s->st_atime), 4, 12);
	}
	else if (opts && opts->statustime && opts->timesort)
		elem->date = ft_strsub(ctime(&elem->s->st_ctime), 4, 12);
	else
	{
		printf("%s:\t\t\tcalcul time:%ld\n",elem->name, time(NULL) - elem->s->st_atime);
		printf("time:%ld\n", time(&elem->s->st_atime));
		printf("current time:%ld\n", time(NULL));
		printf("other time:%ld\n", elem->s->st_atime);
		if (time(NULL) - elem->s->st_atime > 15778800)
		{
			printf("OKKKK");
		}
		elem->date = ft_strsub(ctime(&elem->s->st_mtime), 4, 12);
	}
	*/
	elem->date = format_time(elem, opts);
}

void		del_lst_file(t_lst_file **l, t_options *opts)
{
	if (!l || !(*l))
		return ;
	if ((*l)->next)
		del_lst_file(&(*l)->next, opts);
	free((*l)->name);
	free((*l)->custom_name);
	free((*l)->s);
	if (opts && opts->longform)
	{
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
	}
	if ((*l)->node)
		del_lst_file(&(*l)->node, opts);
	free(*l);
	*l = NULL;
}


void		del_one(t_lst_file **l, t_lst_file *del, t_options *opts)
{
	if ((*l) && del)
	{
		if ((*l) == del)
		{
			*l = del->next;
			free(del->name);
			free(del->custom_name);
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

int		 lstlen(t_lst_file *lst)
{
	int		ret;
	t_lst_file	*begin;

	ret = 0;
	begin = lst;
	while (begin)
	{
		ret++;
		begin = begin->next;
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

int 		lstsort_time(t_lst_file **l)
{
	t_lst_file *current;
	t_lst_file *tmp;
		current = *l;
	while (current)
	{
		if (current == *l && current && current->next && current->s->st_mtime < current->next->s->st_mtime)
		{
			tmp = current->next;
			swap_element(&current, &tmp);
			current->prev = tmp->prev;
			tmp->prev = current;
			*l = current;;
		}
		else if (current->next && current->next->next && current->next->s->st_mtime < current->next->next->s->st_mtime)
		{
			tmp = current->next->next;
			swap_element(&current->next, &tmp);
			current->next->prev = tmp->prev;
			tmp->prev = current->next;
			(current->prev) ? (current = current->prev) : (current = *l);
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