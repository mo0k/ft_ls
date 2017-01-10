/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_longform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/11 00:23:22 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <print.h>

static void			print_size_or_minmaj(t_file *f)
{
	int				i;
	int				len_major;
	int				len_minor;

	if (!S_ISBLK(f->s->st_mode) && !S_ISCHR(f->s->st_mode))
		ft_putstr(f->size);
	else
	{
		i = 0;
		len_major = ft_nbrlen(major(f->s->st_rdev));
		len_minor = ft_nbrlen(minor(f->s->st_rdev));
		while (i++ < 3 - len_major)
			write(1, " ", 1);
		ft_putnbr(major(f->s->st_rdev));
		write(1, ", ", 2);
		i = 0;
		while (i++ < 3 - len_minor)
			write(1, " ", 1);
		ft_putnbr(minor(f->s->st_rdev));
	}
}

static void			print_linkreading(t_file *f)
{
	char			buff[256];
	int				len;

	if (S_ISLNK(f->s->st_mode))
	{
		if ((len = readlink(f->path, buff, 255)) != -1)
			buff[len] = 0;
		write(1, " -> ", 4);
		ft_putstr(buff);
	}
}

static void			print_firstpart(t_file *f, t_opts *opts)
{
	rights_xattr(f->path, f->permi);
	ft_putstr(f->permi);
	write(1, " ", 1);
	ft_putstr(f->lnk);
	write(1, " ", 1);
	if (opts && opts->owner)
	{
		ft_putstr(f->owner);
		write(1, "  ", 2);
	}
	if (opts && opts->group)
	{
		ft_putstr(f->group);
		write(1, "  ", 2);
	}
	print_size_or_minmaj(f);
	write(1, " ", 1);
	ft_putstr(f->date);
	write(1, " ", 1);
}

void				print_longform(t_file *f, t_opts *opts)
{
	struct winsize	*ws;
	t_file			*tmp;

	if (!(ws = (struct winsize*)malloc(sizeof(struct winsize))))
		return ;
	ioctl(1, TIOCGWINSZ, ws);
	tmp = f;
	set_padding_long(&tmp);
	while (tmp)
	{
		print_firstpart(tmp, opts);
		if (opts && opts->colors && ws->ws_col)
			put_color(tmp->custom_name, tmp->s->st_mode);
		else
			ft_putstr(tmp->custom_name);
		print_linkreading(tmp);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
	free(ws);
}

void				print_totalblocks(t_file *lst)
{
	t_file			*current;
	int				total_blocks;

	total_blocks = 0;
	current = lst;
	while (current)
	{
		total_blocks += current->s->st_blocks;
		current = current->next;
	}
	ft_putstr("total ");
	ft_putnbr(total_blocks);
	write(1, "\n", 1);
}
