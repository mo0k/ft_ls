/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2017/01/10 02:59:52 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <ft_ls.h>

t_lstall		*input(int ac, char **av, t_opts **opts);
int				check_input(int ac, char **av, t_lstall *lst, t_opts **opts);
int				is_options(char const *str);
int				is_option_valid(char const *str, char *all_options);
int				set_opts(t_opts *options, char const *str);
int				set_flags(t_opts *options, const char c);
int				set_flags_bis(t_opts *options, const char c);
int				set_flags_bis_bis(t_opts *options, const char c);
int				check_typefile(t_lstall *lst, const char *str);
int				init_opts(t_opts **opts);

#endif
