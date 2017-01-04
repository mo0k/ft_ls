/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfunc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void 				*get_print_func(t_options *options)
{
	if (!options)
		return (NULL);
	if (options->singlecol)
		return (&print_singlecol);
	else if (options->longform)
		return (&print_longform);
	else if (options->stream)
		return (&print_stream);
	else
		return (NULL);
}

void 				print_singlecol(t_lst_file *f, t_options *opts)
{
	struct winsize	*ws;
	t_lst_file		*tmp;

	if (!(ws = (struct winsize*)malloc(sizeof(struct winsize))))
		return ;
	ioctl(1, TIOCGWINSZ, ws);
	tmp = f;
	while (tmp)
	{
		if (opts && opts->colors && ws->ws_col)
			putstr_color(tmp->custom_name, tmp->s->st_mode);
		else
			ft_putstr(tmp->custom_name);
		ft_putstr("\n");
		tmp = tmp->next;
	}
	free(ws);
}

void 				print_stream(t_lst_file *f, t_options *opts)
{
	t_lst_file		*tmp;
	struct winsize	*ws;
	int				len_max;
	float			nbr_col;
	int				mod;
	float			nbr_line;
	char			***tab;
	(void)opts;
	if (!(ws = (struct winsize*)malloc(sizeof(struct winsize))))
		return ;
	tmp = f;
	len_max = name_strlen_max(tmp) + 1;
	ioctl(1, TIOCGWINSZ, ws);
	if (ws->ws_col < len_max)
		return (print_singlecol(tmp, NULL));
	nbr_col = (float)ws->ws_col / (float)len_max;
	mod = lstlen(tmp) % (int)nbr_col;
	if ((int)lstlen(tmp) < (int)nbr_col)
		nbr_line = 1;
	else
	{
		nbr_line = lstlen(tmp) / (int)nbr_col;
		if (mod != 0)
			nbr_line++;
	}
	if(!(tab = get_triple_tab((int)nbr_line, (int)nbr_col, len_max)))
		return ;
	int i, j;
	i = 0;
	j = 0;
	set_padding_normal(&f, len_max - 1);
	while (j < nbr_col)
	{
		i = 0;
		while (i < nbr_line)
		{
			if (tmp)
			{
				tab[i][j] = ft_strcpy(tab[i][j], tmp->custom_name);
				tmp = tmp->next;
			}
			i++;
		}
		j++;
	}
	print_triple_tab(tab);
	delete_triple_tab(tab);
	free(ws);
	return ;
}