/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/11 08:05:16 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <padding.h>



size_t 	is_strlen_max(char *str)
{
	static int 	len_max = 0;
	int 		new_len;
	if(!str)
		return ((len_max = 0));
	new_len = (int)ft_strlen(str);
	if (len_max < new_len)
		len_max = new_len;
	return (len_max);
}

int *array_strlen_max(t_lst_file *lst_file)
{
	int *ret;
	int i;
	int nbr_elem;
	t_lst_file *tmp;

	tmp = lst_file;
	i = 0;
	nbr_elem = 5;
	if (!(ret = (int*)malloc(sizeof(int) * nbr_elem)))
		return (0);
	ret[i++] = lnk_strlen_max(tmp);
	tmp = lst_file;
	ret[i++] = owner_strlen_max(tmp);
	tmp = lst_file;
	ret[i++] = group_strlen_max(tmp);
	tmp = lst_file;
	ret[i++] = size_strlen_max(tmp);
	tmp = lst_file;
	ret[i++] = name_strlen_max(tmp);
	return (ret);
}

int 	padding(char **str, int len_max)
{
	int len;
	char *new;
	char *tmp;

	if (!*str)
		return (0);
	len = (int)ft_strlen(*str);
	//printf("len:%d, len_max:%d\n", len, len_max);
	if (len < len_max)
	{
		//printf("par la\n");
		if (!(new = ft_strnew(len_max)))
			return (-1);
		new = ft_memset(new, ' ', len_max);
		tmp = new;
		//printf("new:%s, (len_max - len):%d\n", new, (len_max - len));
		//printf("*str:\t%p\n", *str);
		//printf("new:\t%p\nnew new:%p\nnew -fin:%p\n", new, new + (len_max - len), new + len_max);
		//printf("new:\t%p\n", new);
		new = ft_memrcpy(new + (len_max - len), *str, len);
		//printf("new:\t%p\n", new);
		//if (*str)
		//	free(*str);
		
		//printf("new:\t%p\n", new);
		//printf("new:%s, len:%d\n", new, (int)ft_strlen(new));
		//printf("new:\t%p\n", new);
		*str = tmp;
		//printf("*str:\t%p\n", *str);
		return (1);
	}
	return (0);
}

void 	set_padding(t_lst_file **lst_file)
{
	int *len_max;
	t_lst_file *tmp;

	tmp = *lst_file;
	len_max = array_strlen_max(tmp);
	while (tmp)
	{
		padding(&tmp->lnk, len_max[0]);
		padding(&tmp->owner, len_max[1]);
		padding(&tmp->group, len_max[2]);
		padding(&tmp->size, len_max[3]);
		//padding(&tmp->name, len_max[4]);
		tmp = tmp->next;
	}
}