/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 20:53:17 by jmoucade          #+#    #+#             */
/*   Updated: 2016/12/12 00:40:35 by jmoucade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

#include <ft_ls.h>

//COLORS
#define RED			"\e[91m"	//exe
#define GREEN		"\e[92m"	//socket
#define MAGENTA		"\e[95m"	//directory
#define CYAN		"\e[96m"	//link
#define YELLOW		"\e[93m"	//fifo
#define BLUE		"\e[34m"	//block & carac
#define ENDCOLOR	"\e[0m"
//END COLORS

void		putstr_color(char *str, mode_t m);

#endif