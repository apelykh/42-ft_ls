/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 19:22:26 by apelykh           #+#    #+#             */
/*   Updated: 2017/05/02 19:22:26 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define IMPL_FLAGS		"[-1latrfR] "
# define PROG_NAME		"ft_ls"
# define MAX_PATH_LEN	1024

# define MAX(a, b) ((a) < (b) ? (b) : (a))

# include <time.h>
# include <sys/stat.h>

typedef struct			s_vars
{
	int					i;
	int					file_i;
	int					dir_i;
	int					n_flag;
	int					name_flag;
}						t_vars;

typedef struct			s_flags
{
	int					l_flag;
	int					rb_flag;
	int					a_flag;
	int					r_flag;
	int					t_flag;
	int					f_flag;
}						t_flags;

typedef struct			s_node_info
{
	char				*name;
	char				*full_path;
	char				*acc_rights;
	int					num_links;
	char				*owner_name;
	char				*owner_group;
	long long			size_bytes;
	long long			num_blocks;
	time_t				mod_time;
	char				*last_mod_time;
	char				*last_mod_date;
	char				*last_mod_year;
	struct timespec		ts;
	int					dev_major;
	int					dev_minor;
	int					spaces[8];
	struct s_node_info	*next;
}						t_node_info;

void					sort_arr(char **arr, int start, int end,
							int (*f)(const char *, const char *));
void					nexist_to_beginning(char **arr,
							struct stat *f_stat, int *file_i);
void					files_to_beginning(char **arr,
							struct stat *f_stat, int *dir_i,
							int file_i);
void					sort_dirpaths(char **dirpaths, int *file_i,
							int *dir_i, t_flags *flags);
void					sort_full_len(char **dirpaths, int *file_i, int *dir_i,
							t_flags *flags);

void					process_flag(char *arg, t_flags *flags);
void					parse_args(char **argv, char **dirpaths,
							t_flags *flags);

int						handle_error(char *param, char *error_msg,
							int to_exit);

t_node_info				*init_node(char *name, char *path, int is_dir);
void					set_file_mode(char *acc_rights,
							struct stat *file_stat, int *i);
void					set_acc_rights(t_node_info *node,
							struct stat *file_stat);
void					set_datetime(t_node_info *node,
							struct stat *file_stat);
void					set_node_info(t_node_info *node,
							struct stat *file_stat);

int						*init_maxes(t_node_info *node);
void					count_list_maxes(t_node_info *head, t_flags *flags,
							int if_total);
void					update_maxes(t_node_info *node, int *maxes);
void					count_spaces(t_node_info *head, int maxes[4]);
void					apply_list_ops(t_node_info **head, t_flags *flags,
							int if_total);

int						ft_nodetimecmp(t_node_info *n1, t_node_info *n2);
int						ft_revnodetimecmp(t_node_info *n1,
							t_node_info *n2);
int						ft_nodestrcmp(t_node_info *n1, t_node_info *n2);
int						ft_revnodestrcmp(t_node_info *n1, t_node_info *n2);

int						ft_revstrcmp(const char *s1, const char *s2);
int						ft_modcmp(const char *s1, const char *s2);
int						ft_revmodcmp(const char *s1, const char *s2);

void					print_node(t_node_info *node);
void					print_list(t_node_info *head, t_flags *flags);
void					print_dev_nums(t_node_info *node);
void					print_padded_str(char *str, int pad_n);
void					print_lnk_src(t_node_info *node);

t_node_info				*get_prev_node(t_node_info *head, t_node_info *x);
void					swap_nodes_links(t_node_info **head, t_node_info **x,
							t_node_info **y);
void					sort_list(t_node_info **head,
							int (*f)(t_node_info *, t_node_info *));
void					apply_sorting(t_node_info **head, t_flags *flags);

void					ls_files_group(char **files, int i_from, int i_to,
							t_flags *flags);
void					ls_dir(char *dirpath, t_flags *flags);
void					ls_file(char *filename, t_flags *flags);
void					ls_object(char *path, t_flags *flags, int n_flag,
							int name_flag);
void					recursive_ls_dir(t_node_info *head, t_flags *flags);

void					ft_putlonglong(long long n);
int						compare_timestamp(time_t mod_time);
void					free_str_arr(char **dt_split);
void					swap_strings(char **s1, char **s2);
int						num_len(long long nbr);

void					init_vars(t_vars *vars, int argc, char **dirpaths);
int						get_dlen(char **dirpaths);

t_node_info				*lst_add_back(t_node_info *head,
							t_node_info *node_info);
void					lst_free(t_node_info *head);
void					node_pre_free(t_node_info *node);

#endif
