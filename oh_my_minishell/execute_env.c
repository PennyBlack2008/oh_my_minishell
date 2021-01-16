#include "minishell.h"

static void	export_env_path(const char *path, char *const argv[], char *const envp[])
{
	char	*tmp[3];

	tmp[0] = "export";
	if (ft_strncmp(path, "env", 4) == '\0')
		tmp[1] = ft_strjoin("_=", "/usr/bin/env");
	else
		tmp[1] = ft_strjoin("_=", path);
	tmp[2] = NULL;
	execute_export(path, tmp, envp);
	free(tmp[1]);
}

int		execute_env(const char *path, char *const argv[], char *const envp[])
{

	int		i;
	int		j;
	char	**tmp;
	if (argv[1] != NULL)
	{
		g_status = 256 * 127;
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (-1);
	}

	export_env_path(path, argv, get_param()->envp);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			if (ft_strncmp(envp[i], "_=", 2) == '\0')
			{
				j = i++;
				continue;
			}
			ft_putendl_fd(envp[i], 1);
		}
		i++;
	}
	ft_putendl_fd(envp[j], 1);
	g_status = 0;
	return (0);
	(void)argv;
}