/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a18979859 <a18979859@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:42:08 by sschmele          #+#    #+#             */
/*   Updated: 2021/06/23 23:32:00 by a18979859        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <sys/ioctl.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# include <signal.h>

# include <stdio.h>      //DELETE

# include <string.h>

# include "libft.h"

struct termios		g_tty;
struct termios		g_backup_tty;

typedef struct		s_args
{
	char			*arg;
	short			selected;
	short			underline;
	short			down;
	unsigned int	x;
	unsigned int	y;
	size_t			len;
	struct s_args	*next;
	struct s_args	*prev;
	struct s_args	*up; //delete because it is uppest list for each file
}					t_args;

typedef struct		s_celldata
{
	t_args			*list;
	t_args			*upper_list;
	size_t			max_len;
	int				argc;
}					t_celldata;

/*
** File main.c
*/

char				**prepare_arguments(int *argc, char **argv);
int					before_start(void);
int					before_finish(void);

/*
** File main_start_finish.c
*/

char				*main_start_selection(int argc, const char **argv);
char				*generate_selected_line(t_args *list, char *result);
char				**find_selected(t_args *list, int *total, size_t *j);

/*
** File terminal_changes.c
*/

int					set_noncanonical_input(void);
void				reset_canonical_input(void);
void				back_to_noncanonical_input(void);
void				make_fullscreen(void);
void				reset_terminal_mode(void);

/*
** File globals_forbidden.c
*/

void				save_for_exit(t_args *list, int flag);
void                resize_monitor(t_args *list, int argc,
						size_t max_len, int *flag);

/*
** File signals_processing.c
*/

void				redirect_signals(void);
void				signal_handler(int sig);

/*
** File readline.c
*/

char				*read_commands(t_args **list, int *flag);
char				*read_commands_and_signals(t_args **list, int key, int *flag);
int					key_hook(void);

/*
** File args_initiation.c
*/

t_args				*save_arguments(size_t *max_len, int argc,
						const char **argv);
t_args				*init_first_argument(const char *argument);
void				init_next_argument(t_args *current,
						const char *argument, short flag);

/*
** File args_position_calculation.c
*/

int					calculate_position(t_args *list, int total, size_t max_len);
void				fill_in_position(t_args *list, int term_lines, int max_len);
t_args				*reposition_till_the_end(t_args *list, t_args *first_after);

/*
** File args_processing.c
*/

int					args_total(const t_args *list, const t_args *under);
t_args				*find_list(t_args *list, char flag);
void				output_arguments(const t_args *list, const t_args *under);
t_args				*delete_argument(t_args *list, t_args *selected);
void				free_arguments(t_args *list);

/*
** File keys_movement_dir.c
*/

void				make_movements(t_args *list, int key);
t_args				*move_up_a(t_args *under);
t_args				*move_down_b(t_args *under);
t_args				*move_right_c(t_args *under);
t_args				*move_left_d(t_args *under);

/*
** File keys_bs_del_select.c
*/

void				select_element(t_args *list);
void				check_selected(int under_selected);
t_args				*backspace_element(t_args *list);
t_args				*delete_element(t_args *list);

/*
** File termcap_position.c
*/

void				output_element(char *element);
void				position_cursor(int x, int y);
void				position_and_clear_element(int x, int y, size_t len);
void				clean_screen(void);

/*
** File termcap_underline_inverse_video.c
*/

void				underline_on(void);
void				underline_off(void);
void				inverse_video_on(void);
void				inverse_video_off(void);

/*
** File bonus_functionalities.c
*/

void				bell_sound();

/*
** File errors_output.c
*/

int					usage(void);
int					terminal_errors(int flag);
void				message_resize(void);

/*
** File help_fucntions.c
*/

void				*ft_xmalloc(size_t size);
char				*ft_straddsy(char *dest, char sy);
int					ft_putint(int c);

#endif
