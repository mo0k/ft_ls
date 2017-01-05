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
#define T_RED		"\e[31m"	//exe
#define T_GREEN		"\e[92m"	//socket
#define T_MAGENTA	"\e[35m"	//directory
#define T_CYAN		"\e[96m"	//link
#define T_YELLOW	"\e[93m"	//fifo
#define T_BLUE		"\e[34m"	//block & carac
#define T_BLACK		"\e[30m"
#define T_END		"\e[0m"
//BACKGROUND
#define B_CYAN 			"\e[46m"
#define B_RED 			"\e[41m"
#define B_YELLOW		"\e[43m"
#define B_GREEN 		"\e[42m"
#define B_END			"\e[49m"

void		put_color(char *str, mode_t m);

#endif