/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmuller <fmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 08:39:48 by fmuller           #+#    #+#             */
/*   Updated: 2018/03/21 20:06:20 by fmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"

# define PC -1

typedef unsigned char	t_byte;

typedef enum	e_param_nbr
{
	first,
	second,
	third
}				t_param_nbr;

typedef struct	s_process
{
	t_byte				registers[REG_NUMBER * REG_SIZE];
	t_byte				pc[REG_SIZE];
	int					carry;
	int					waiting_time;
	int					live_nbr;
	int					index;
	t_byte				ocp;
	struct s_process	*next;
}				t_process;

typedef struct	s_player
{
	char		name[PROG_NAME_LENGTH + 1];
	char		comment[COMMENT_LENGTH + 1];
	int			number;
	int			fd;
	int			size;
}				t_player;

typedef struct	s_cor_env
{
	t_byte			mem[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	t_process		*process_lst;
	int				dump_nbr;
	long long		cycle;
	int				cycle_to_die;
	int				cycle_nbr_befor_check;
	int				checks_nbr;
	int				total_live_nbr;
	t_player		*last_player_live;
}				t_cor_env;

typedef struct	s_cmd
{
	int		argc;
	char	**argv;
	int		i;
}				t_cmd;

long long		ft_read_nb(t_byte *nbr, int nbr_size);
void			ft_write_nb(t_byte *dest, int nbr_size, long long nbr);
long long		ft_signed_nb(long long nbr, int size);

long long		ft_read_mem(t_cor_env *cor_env, int addr, int size);
void			ft_write_mem(t_cor_env *cor_env, int addr, int size,
																long long nbr);

long long		ft_read_register(t_process *process, int reg_nbr);
void			ft_write_register(t_process *process, int reg_nbr,
																long long nbr);

long long		ft_pc(t_process *process);
void			ft_add_pc(t_process *process, long long add);
void			ft_advance_pc(t_process *process, int index);

int				ft_type_size(t_arg_type type, int index);
int				ft_get_param_size(t_process *process, unsigned int param_nbr,
																	int index);
t_arg_type		ft_get_param_type(t_process *process, unsigned int param_nbr);
long long		ft_get_param_value(t_cor_env *cor_env, t_process *process,
										unsigned int param_nbr, int index);
long long		ft_get_full_param_value(t_cor_env *cor_env, t_process *process,
											unsigned int param_nbr, int index);

void			ft_parse_cmd(t_cor_env *cor_env, int argc, char *argv[]);
void			ft_get_player(t_cor_env *cor_env, char *file, int player_num);
int				ft_player_num(t_cor_env *cor_env, int players_num[MAX_PLAYERS],
														int *next_player_num);
void			ft_after_n(t_cor_env *cor_env, t_cmd *cmd,
							int players_num[MAX_PLAYERS], int *next_player_num);

void			ft_init_game(t_cor_env *cor_env);
t_player		*ft_find_player(t_cor_env *cor_env, int number);
void			ft_set_waiting_time(t_cor_env *cor_env, t_process *process);
int				ft_is_instruction(int opcode);

void			ft_play_game(t_cor_env *cor_env);
void			ft_check_cycle(t_cor_env *cor_env);
void			ft_exec_instruction(t_cor_env *cor_env, void (*inst_array[16])
						(t_cor_env *cor_env, t_process *process, int index));
t_process		*ft_dup_process(t_cor_env *cor_env, t_process *src,
															long long pc_val);

void			ft_live(t_cor_env *cor_env, t_process *process, int index);
void			ft_ld(t_cor_env *cor_env, t_process *process, int index);
void			ft_st(t_cor_env *cor_env, t_process *process, int index);
void			ft_add(t_cor_env *cor_env, t_process *process, int index);
void			ft_sub(t_cor_env *cor_env, t_process *process, int index);
void			ft_and(t_cor_env *cor_env, t_process *process, int index);
void			ft_or(t_cor_env *cor_env, t_process *process, int index);
void			ft_xor(t_cor_env *cor_env, t_process *process, int index);
void			ft_zjmp(t_cor_env *cor_env, t_process *process, int index);
void			ft_ldi(t_cor_env *cor_env, t_process *process, int index);
void			ft_sti(t_cor_env *cor_env, t_process *process, int index);
void			ft_fork(t_cor_env *cor_env, t_process *process, int index);
void			ft_lld(t_cor_env *cor_env, t_process *process, int index);
void			ft_lldi(t_cor_env *cor_env, t_process *process, int index);
void			ft_lfork(t_cor_env *cor_env, t_process *process, int index);
void			ft_aff(t_cor_env *cor_env, t_process *process, int index);

void			ft_print_mem(t_cor_env *cor_env);
void			ft_quit(t_cor_env *cor_env, int ret_value);
#endif
