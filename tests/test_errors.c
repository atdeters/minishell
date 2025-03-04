#include "minishell.h"

int main(void)
{
    p_err(ERR_EXECVE);
	p_err(ERR_DUP2);
	p_err(ERR_FORK);
	p_err(ERR_USAGE);
	p_err(ERR_PIPE);
	p_err(ERR_PARS_SINGLE_QUTE);
	p_err(ERR_PARS_DOUBLE_QUTE);

	p_err_arg(ERR_ACCESS, "dummes file");
	p_err_arg(ERR_ACCESS_FILE, "dummes file");
	p_err_arg(ERR_PERM, "dummes file");
	p_err_arg(ERR_OPEN, "dummes file");
}