#include "../src/minishell.h"

#define NON_EXISTING_FILE "this_does_not_exist.c"
#define NON_PERMITTED_FILE "this_is_not_permitted.c"

int main(void)
{
	p_err(ERR_USAGE);
    p_err(ERR_EXECVE);
	p_err(ERR_DUP2);
	p_err(ERR_FORK);
	p_err(ERR_PIPE);
	p_err(ERR_PARS_SINGLE_QUTE);
	p_err(ERR_PARS_DOUBLE_QUTE);

	p_err_arg(ERR_ACCESS, NON_EXISTING_FILE);
	p_err_arg(ERR_ACCESS_FILE, NON_EXISTING_FILE);
	p_err_arg(ERR_PERM, NON_PERMITTED_FILE);
	p_err_arg(ERR_OPEN, NON_EXISTING_FILE);
}