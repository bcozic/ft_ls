/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_data.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:04:32 by bcozic            #+#    #+#             */
/*   Updated: 2018/11/02 23:37:08 by bcozic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_DATA_H
# define FT_PRINTF_DATA_H

# include <stdarg.h>
# include <stdlib.h>

# define LIST_CONV "sSpPoOuUxXcCdDibB%\0\0\0\0\0\0\0\0\0\0"
# define VALID_F "sSpPoOuUxXcCdDibB%0-.#+ hjzl*"
# define MODIFER "zjlh"

int		write_buff(char *buffer);
int		print_string(va_list va, const char *restrict format);
int		check(char *buffer, int blen, int *len);
int		chr_arg(va_list va, const char *restrict format, int *i, char *buffer);
int		save_flags(const char *restrict format, int i, char *buff_f, int *nb);
int		add_flag(char *buff_f, int i, int j, const char *restrict format);
int		chr_digit(const char *restrict format, int i, int *nb, int *end);
int		send_flag(va_list va, char *flag, char *buffer, int *nb);
char	*conv_arg(va_list va, char *f, int *nb);
int		add_string(char *buffer, char *str, int *nb, char *f);
int		uni_n_cara(char *flag, va_list va, int *nb, char *buff);
void	char_unicode(wchar_t cara, int *len);
int		write_unicode(wchar_t *uni, int *nb, int len);
wchar_t	convert_uni(wchar_t cara);
int		unilen(wchar_t *uni, int mod, int *nb);
char	*conv_nbr(va_list va, char *f, int *nb);
int		chr_base(char *f, va_list va);
char	*signed_conv(va_list va, char *f, int base);
char	*unsigned_conv(va_list va, char *f, int base);
void	char_conv(va_list va, char *buff, int *len);
char	*ft_llitoa_base_mod(long long n, int base, char mode);
char	*ft_ullitoa_base_mod(unsigned long long n, int base);
int		apply_hash(char *flag, char *buffer, int blen);
void	cpt_hash_n_up(char *flag, char *str, int *nb);
int		cara_after(char *buffer, char *str, int *nb, char *f);
int		point_flag(char *buffer, char *str, int *nb, char *flags);
void	flag_min(char *buffer, int *nb, int blen, int *len);
int		aff_sign(char *buffer, char *str, int *nb, char cara);
int		after_ccs(char *buffer, int slen, int *nb, char *f);
int		flag_sl(char *flag, va_list va, int *nb, char *buff);
int		print_mps(char *buffer, char *str, int *nb, char *f);

#endif
