/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/10 02:59:08 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <padding.h>

size_t			is_strlen_max(char *str)
{
	static int	len_max = 0;
	int			new_len;

	if (!str)
		return ((len_max = 0));
	new_len = (int)ft_strlen(str);
	if (len_max < new_len)
		len_max = new_len;
	return (len_max);
}

int				*array_strlen_max(t_file *lst_file)
{
	int			*ret;
	int			i;
	int			nbr_elem;
	t_file		*tmp;

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

void			set_padding_long(t_file **lst_file)
{
	int			*len_max;
	t_file		*tmp;

	tmp = *lst_file;
	len_max = array_strlen_max(tmp);
	while (tmp)
	{
		ft_strpadding_right(&tmp->lnk, len_max[0]);
		ft_strpadding_left(&tmp->owner, len_max[1]);
		ft_strpadding_left(&tmp->group, len_max[2]);
		ft_strpadding_right(&tmp->size, len_max[3]);
		tmp = tmp->next;
	}
	free(len_max);
}

void			set_padding_normal(t_file **lst_file, int len_max)
{
	t_file	*tmp;

	tmp = *lst_file;
	if (!tmp)
		return ;
	while (tmp)
	{
		ft_strpadding_left(&tmp->custom_name, len_max);
		tmp = tmp->next;
	}
}
