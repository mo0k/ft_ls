/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 00:40:35 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

#include <ft_ls.h>

t_lst_all		*input(int ac, char **av, t_options **opts);
int				check_input(int ac, char **av, t_lst_all *lst, t_options **opts);
int				is_options(char const *str);
int				is_option_valid(char const *str, char *all_options);
int				set_options(t_options *options, char const *str);
int				set_flags(t_options *options, const char c);
int				set_flags_bis(t_options *options, const char c);
int				set_flags_bis_bis(t_options *options, const char c);
int 			check_typefile(t_lst_all *lst, const char  *str);
int 			init_options(t_options **opts);

#endif