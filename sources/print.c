/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 14:50:56 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 03:41:01 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int print(t_lst_file *lst, t_print_func print_func, t_options *opts)
{
	t_lst_file *current;
		(void)opts;
	current = lst;
	if (opts && opts->longform && current)
		set_list_to_string(current, opts);
	if (opts && opts->longform)
		get_total_blocks(current);
	print_func(current);
	return (1);
}

void 	*get_print_func(t_options *options)
{
	if (!options)
		return (NULL);
	if (options->singlecol)
		return (&print_option_1);
	else if (options->longform)
		return (&print_option_l);
	else if (options->stream)
		return (&print_stream);
	else
		return (NULL);
}

void 	print_header_dir(char *pathdir, int state)
{
	//state = 1;
	if (state)
		write(1, "\n", 1);
	ft_putstr(pathdir);
	write(1, ":\n", 2);
}

void 	print_first_node(t_lst_file *lst, int len, int *state, t_print_func print_func)
{
	t_lst_file *node;

	node = lst->node;
	if (len == 1 && !lst->state)
	{
		if (print_func == &print_option_l)
			get_total_blocks(node);
		print_func(node);
	}
	else
	{
		print_header_dir(lst->path, *state);
		if (print_func == &print_option_l)
			get_total_blocks(node);
		print_func(node);
		*state = 1;
	}
}

void 		print_option_l(t_lst_file *f)
{
	//printf("petit test\n");
	t_lst_file			*tmp;
	char buff[256];
	int len ;
	tmp = f;

	set_padding_long(&tmp);
	//	return ;
	while (tmp)
	{
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
		ft_putstr(tmp->custom_name);
		if (S_ISLNK(tmp->s->st_mode))
		{
			//ft_putstr("___________________________________________________\n");
			//write(1, "xxx\n", 4);
			//printf("name:%s\n", tmp->name);
			if ((len = readlink(tmp->path, buff, 255)) != -1)
			{
				buff[len] = 0;
				//ft_putstr(buff);
				//write(1, "xxx\n", 4);
			}
			write(1, " -> ", 4);
			ft_putstr(buff);
		}
		
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

void 		print_option_1(t_lst_file *f)
{
	t_lst_file			*tmp;

	tmp = f;
	while (tmp)
	{
		ft_putstr(tmp->custom_name);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}

void 		print_stream(t_lst_file *f)
{
	//printf("print stream\n");
	t_lst_file			*tmp;
	struct winsize *ws;
	int len_max;
	float nbr_col;
	int mod;
	float nbr_line;
	char ***tab;


	if (!(ws = (struct winsize*)malloc(sizeof(struct winsize))))
		return ;

	tmp = f;
	len_max = name_strlen_max(tmp) + 1;
	ioctl(1, TIOCGWINSZ, ws);
	//printf("len_max:%d\n", len_max);
	//printf("name:%s\n", tmp->name);
	//printf("lstlen:%d\n", (int)lstlen(tmp));
	//printf("Cols: %d\n", ws->ws_col);
	//printf("nbr colonne:%d\n",  ws->ws_col/len_max);
	//printf("nbr ligne:%d\n",  (int)lstlen(tmp) / (int)(ws->ws_col / len_max));
	if (ws->ws_col < len_max)
	{
		/*while (tmp)
		{
			ft_putstr(tmp->custom_name);
			write(1, "\n", 1);
			tmp = tmp->next;
		}*/
		print_option_1(tmp);
		return ;
	}
	//ERROR
	nbr_col = (float)ws->ws_col / (float)len_max;
	//printf("___________________________lstlen:%d\n", lstlen(tmp));
	mod = lstlen(tmp) % (int)nbr_col;
	if ((int)lstlen(tmp) < (int)nbr_col)
		nbr_line = 1;
	else
	{
		nbr_line = lstlen(tmp) / (int)nbr_col;
		if (mod != 0)
			nbr_line++;
	}
	//(nbr_line = (int)lstlen(tmp) / nbr_col) ? 0 : nbr_line++;
	//return ;
	//printf("nbr colonne:%f\n",  nbr_col);
	//printf("nbr ligne:%f\n",  nbr_line);
	tab = get_tab_lst_align((int)nbr_line, (int)nbr_col, len_max);
	if(!tab)
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
			//printf("i:%d, j:%d\n", i, j);
			if (tmp)
			{
				tab[i][j] = tmp->custom_name;
				tmp = tmp->next;
			}
			i++;
		}
		j++;
	}
	print_tab_lst_align(tab);
	return ;
	
	/*while (tmp)
	{
		ft_putstr(tmp->custom_name);
		write(1, " ", 1);
		tmp = tmp->next;
	}*/
	ft_putchar('\n');
	//DELETE TAB TMP
}

char ***get_tab_lst_align(int line, int columm, int len)
{
	char ***tab;
	int cells;
	int cols;

	if (!line || !columm || !len)
	{
		//printf("ERROR\n");
		return (NULL);
	}
	cells = 0;
	if (!(tab = (char***)malloc(sizeof(char**) * (line + 1))))
	{
		//printf("ERROR 1\n");
		return (NULL);
	}
	while (cells < line)
	{
		if (!(tab[cells] = (char**)malloc(sizeof(char*) * (columm + 1))))
		{
			//printf("ERROR 2\n");
			return (NULL);
		}
		cols = 0;
		while (cols < columm)
		{
			if (!(tab[cells][cols] = (char*)malloc(sizeof(char) * (len + 1))))
			{
				//printf("ERROR 3\n");
				return (NULL);
			}
			
			//printf("TEST 1\n");
			tab[cells][cols][len] = '\0';
			cols++;
		}
		tab[cells][columm] = NULL;
		cells++;
		//printf("TEST 2\n");
		
	}
	//printf("TEST 3\n");
	tab[line] = NULL;
	return (tab);
}

void 	print_tab_lst_align(char ***tab)
{
	//printf("START\n");
	if (!tab || !(*tab) || !(**tab))
	{
		//printf("START 2222222\n");
		return ;
	}
	int i, j, h;
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			h = 0;
			//while (tab[i][j][h])
			//{
				ft_putstr(tab[i][j]);
				ft_putchar(' ');
				//(*tab)++;
			//	h++;
			//}
			j++;
		}
		ft_putchar('\n');
		i++;
		//tab++;
	}
}

void 		print_root_file(t_lst_file *f, t_options *opts, t_print_func print_func)
{
	t_lst_file *current;
	current = f;
	if (opts && opts->longform && current)
		set_list_to_string(current, opts);
	current = f;
	if (f)
	{
		print_func(current);
		//ft_putchar('\n');
		del_lst_file(&f, opts);
	}
	
}

