/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_singleform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

void				print_singlecol(t_file *f, t_opts *opts)
{
	struct winsize	*ws;
	t_file			*tmp;

	if (!(ws = (struct winsize*)malloc(sizeof(struct winsize))))
		return ;
	ioctl(1, TIOCGWINSZ, ws);
	tmp = f;
	while (tmp)
	{
		if (opts && opts->colors && ws->ws_col)
			put_color(tmp->custom_name, tmp->s->st_mode);
		else
			ft_putstr(tmp->custom_name);
		ft_putstr("\n");
		tmp = tmp->next;
	}
	free(ws);
}
