#include "../headers/execution.h"

int	ft_env(t_shell *shell)
{
	t_env	*head;

	head = shell->env->next;
	while (head)
	{
		printf("%s=%s\n", head->var, head->value);
		head = head->next;
	}
	return (0);
}