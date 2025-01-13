/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:36:43 by retanaka          #+#    #+#             */
/*   Updated: 2025/01/07 10:22:49 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H

# define FT_DPRINTF_H
# include <stdarg.h>
# include <unistd.h>

typedef struct s_form
{
	int		base;
	char	fmt;
}	t_form;

int		ft_dputchar(int fd, char s);
int		ft_dputstr(int fd, char *s);
int		ft_dputchar_check(int fd, char s, int *count);
int		ft_dputstr_check(int fd, char *s, int *count);
int		ft_dputnum_check(int fd, char n, char format, int *count);
int		ft_dputptr_check(int fd, unsigned long long p, int *count);
int		ft_dputoct_check(int fd, unsigned int n, int *count);
int		ft_dputdec_check(int fd, int n, char format, int *count);
int		ft_dputhex_check(int fd, unsigned int n, char format, int *count);
void	dget_digit(unsigned long long n, int *digit, int base);
char	dget_place_num(unsigned long long n, int digit, int base);
void	dremove_place_num(unsigned long long *n, int digit, int base);
int		ft_dputnumber_check(int fd, unsigned long long n, t_form f, int *count);
int		ft_dprintf(int fd, const char *str, ...);

#endif
