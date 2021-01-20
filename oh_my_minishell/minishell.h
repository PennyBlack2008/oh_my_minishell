#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <string.h>
# include <dirent.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# define READ 0
# define WRTIE 1
# define ERROR -1
# define FALSE 0
# define TRUE 1

/* ECHO, GREP, CLEAR 제외 안쓰임 */
# define ECHO 0
# define CD 1
# define PWD 2
# define EXPORT 3
# define UNSET 4
# define ENV 5
# define EXIT 6
# define LS 7
# define GREP 8
# define CLEAR 10
# define CAT 11

# define READ 0
# define WRITE 1

# define RDONLY 0
# define WRONLY 1
# define RDWR 2

# define BUFF_MAX 1000

enum	e_quotes
{
	Q_E = -3,
	Q_B,
	Q_S,
	OUT,
	DQ_S,
	DQ_B,
	DQ_E
};

enum	e_except
{
	NONE,
	SYNTAX,
	EX_END
};

enum	e_flag
{
	CTRL_D,
	CTRL_BS,
	CTRL_Q,
	F_END
};

enum	e_redirect
{
	LEFT = 1,
	RIGHT,
	D_RIGHT,
	R_END
};

int	g_flag[F_END];
char g_except[EX_END];
int g_status; // 이걸 256으로 나누면 exit status
char g_buf[1000];
int g_dup_stdin;
int g_dup_stdout;



// struct stat {
//     dev_t     st_dev;     /* ID of device containing file */
//     ino_t     st_ino;     /* inode number */
//     mode_t    st_mode;    /* protection */
//     nlink_t   st_nlink;   /* number of hard links */
//     uid_t     st_uid;     /* user ID of owner */
//     gid_t     st_gid;     /* group ID of owner */
//     dev_t     st_rdev;    /* device ID (if special file) */
//     off_t     st_size;    /* total size, in bytes */
//     blksize_t st_blksize; /* blocksize for file system I/O */
//     blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
//     time_t    st_atime;   /* time of last access */
//     time_t    st_mtime;   /* time of last modification */
//     time_t    st_ctime;   /* time of last status change */
// };



typedef struct	s_var
{
	int	i;
	int k;
	int l;
	int flag_bq; // 큰 따옴표
	int flag_sq; // 작은 따옴표
}				t_var;


typedef struct	s_data {
	// unsigned char	exit_status;
	char **cmd_splited;
	char *cmd_trimed;
	char ***cmd_redirect;
	char *symbol_array;
	char **envp;
	int semi_arr[BUFF_MAX];
}				t_data;

typedef struct s_index
{
	int				i;
	int				j;
	int				z;
	int				before;
	int				cnt;
	int				redir_num;
	unsigned char	f_quote;
}t_index;

//builtin함수의 prototype 다 맞춰야 check_command 조건문 사용가능
typedef int	(*t_builtin)(const char *, char *const[], char *const[]);

//get_commands_from_gnl.c
char	*ft_strsep(char **stringp, const char *delim);
void	del(void *content);
char	*string_tolower(char *str);
void	get_commands_from_gnl(t_list **cmd, char *line);

//print_free.c
void	print_cmd_list(t_list *cmd);
void	free_split(char **argv);
void	print_split(char **split);
void	free_3d_split(char ***argv);
void	print_3d_split(char ***argv);

//execute_commands.c
int		execute_multi_commands(t_list *cmd);
int		execute_command(char **split_by_pipes);

//execute_echo.c
int	execute_echo(const char *path, char *const argv[], char *const envp[]);

//execute_pwd.c
int execute_pwd(const char *path, char *const argv[], char *const envp[]);

//execute_exit.c
int execute_exit(const char *path, char *const argv[], char *const envp[]);

//execute_is_dir_file
int			execute_is_dir_file(const char *path, char *const argv[], char *const envp[]);

//utils_jikang.c
t_data	*get_param();
int		ft_is_whitespace(char c);
void	init_array(char *buff);
void	init_array_int(int *buff);
void	check_semicolon(char *str);
void	change_flag(int *flag);
char *ft_strdup_by_index(char *str, int start, int end);
void	free_init(char **data, char *init);

//pipe.c
int		execute_command_nopipe(char *one_cmd);
int		execute_command_pipe(char **split_by_pipes, int *fd, int i);
//pipe_utils.c
char	*string_tolower(char *str);
int		which_command(char *cmd);
int		need_redirection(void);
// char	*which_command2(int num_cmd);
void	parent_process(char **split_by_pipes, int *fd, int i);
void	child_process(char **one_cmd_splited, int *fd);
int		need_redirection();

// signal.c
void	catch_signals(void);
// init.c
void	minishell_init(int argc, char *argv[], char **envp);
void	dup_initalize();
// exit.c
void	minishell_exit(t_list *cmds);
void	cmds_exit(t_list *cmd);
void	cmd_exit();

// vector.c
void	vector_erase(char *arr[], int target);
void	vector_sort(char *arr[]);
int		vector_size(char *arr[]);
void	vector_clear(char *arr[]);
char	**vector_dup(char *arr[]);
void	vector_push_back(char **arr[], char str[]);

int		execute_env(const char *path, char *const argv[], char *const envp[]);
int		execute_unset(const char *path, char *const argv[], char *const envp[]);
int		execute_export(const char *path, char *const argv[], char *const envp[]);
int		execute_cd(const char *path, char *const argv[], char *const envp[]);
int		execute_path(const char *path, char *const argv[], char *const envp[]);

//execute_cd_utils.c
int		is_home_cd(const char *str);
//execute_path_utils.c
int command_not_found_g_status(char *str);
void copy_pathname(char *str, char *buff);
int is_macro_in_envp(const char *env_line, char *buff);
//check_command.c
void check_command(char *cmd, char *argv[], char *envp[]);
// check_command_utils.c
char	*get_path(char *cmd, char *argv[], char *envp[]);
void	ft_execve(const char *path, char *const argv[], char *const envp[]);
//is_execve.c
int is_execve(char *path, char **cmd_split, char *envp[]);

//redirection.c
char	***splited_by_redirect(char **one_cmd_splited, char **array);
int		parsing_redirect(char *str);
//redirection_execute_part.c
int		execute_nopipe_redirect();
//redirection_utils.c
void	input_symbol(char **split, char *symbol_array, t_index *index);
int		parsing_redirect(char *str);
void	s_index_bzero(t_index *index);

// ft_strsemi.c
char *ft_strsemi(char **str, int *array, int i);

// refine_line_a.c
char	*refine_line(char *line);

// refine_line_b.c
int		refining_factory(char *buff, char *line, t_var *v, char **envlist);

// refine_line_c.c
int		convert_env(char *buff, char *line, t_var *v, char **envlist);



//	msg_error.c
int		msg_error(char *program, char *cmd, char *arg, int exit_status);
#endif