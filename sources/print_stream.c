/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stream.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

static void			set_value(char ***tab, t_lst_file *lst, int line, int col)
{
	int i;
	int j;
	t_lst_file *tmp;

	i = 0;
	j = 0;
	tmp = lst;
	while (j < col)
	{
		i = 0;
		while (i < line)
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
}

static int			get_nbr_line(int len_lst, int nbr_col)
{
	int 			nbr_line;

	if (len_lst < nbr_col)
		nbr_line = 1;
	else
	{
		nbr_line = len_lst / nbr_col;
		if (len_lst % nbr_col != 0)
			nbr_line++;
	}
	return (nbr_line);
}

static void			finish_stream(t_lst_file *f, int nbr_col, int len_str)
{
	int 			nbr_line;
	char			***tab;

	nbr_line = get_nbr_line(lstlen(f), nbr_col);
	if(!(tab = ft_get_triple_tab(nbr_line, nbr_col, len_str)))
		return ;
	set_value(tab, f, nbr_line, nbr_col);
	ft_print_triple_tab(tab);
	ft_delete_triple_tab(tab);
}

void 				print_stream(t_lst_file *f, t_options *opts)
{
	struct winsize	*ws;
	int				len_max;
	int				nbr_col;

	(void)opts;
	len_max = name_strlen_max(f) + 1;
	if (!(ws = (struct winsize*)malloc(sizeof(struct winsize))))
		return ;
	ioctl(1, TIOCGWINSZ, ws);
	if (ws->ws_col < len_max)
	{
		free(ws);
		return (print_singlecol(f, NULL));
	}
	nbr_col = ws->ws_col / len_max;
	free(ws);
	//if (f)
		set_padding_normal(&f, len_max - 1);
		finish_stream(f, nbr_col, len_max);
	return ;
}
