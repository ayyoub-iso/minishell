#include "../minishell.h"

t_env   *new_env_node(char *key,char *value)
{
    t_env   *new;

    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = key;
    new->value = value;
    new->hidden = false;
    if (!value || !ft_strcmp(key, "_"))
        new->hidden = true;
    new->next = NULL;
    return (new);

}

t_env   *copy_node(t_env *node)
{
    t_env   *new;

    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->hidden = node->hidden;
    new->key = ft_strdup(node->key);
    new->value = ft_strdup(node->value);
    new->next = NULL;
    return (new);
}

t_env   *null_env(t_env **head)
{
    char    *path;

    path = getcwd(NULL, 0);
    if (!path)
        return (NULL);
    if (!add_env(head, ft_strdup("PATH"), ft_strdup("/usr/local/sbin:/usr/local/bin:"\
			"/usr/sbin:/usr/bin:/sbin:/bin"), NEW))
        return (free(path), NULL);
    if (!add_env(head, "PWD", ft_strdup(path), NEW))
        return (free(path), NULL);
    free(path);
    if (!add_env(head, ft_strdup("SHLVL"), ft_strdup("1"), NEW))
        return (NULL);
    if (!add_env(head, ft_strdup("_"), ft_strdup("/usr/bin/env"), NEW))
        return (NULL);
    if (!add_env(head, ft_strdup("OLDPWD"), NULL, NEW))
        return (NULL);
    return (*head);
}

t_env   *create_env(char **av, t_env **head)
{
    char    *key;
    char    *value;
    int     i;
    int     j;

    i = -1;
    if (!av)
        return (null_env(head));
    while (av[++i])
    {
        key = get_till_char(av[i], '=');
        if (!key)
            return (NULL);
        j = -1;
        while (av[i][++j] && av[i][j] != '=')
            ;
        if (av[i][j] == '=')
            j++;
        value = ft_strdup(av[i] + j);
        if (!value)
            return (NULL);
        if (!add_env(head, key, value, NEW))
            return (NULL);
    }
    return (*head);
}

char    *get_var(t_env *head, char *key)
{
    while (head)
    {
        if (!ft_strcmp(key, head->key))
            return (ft_strdup(head->value));
        head = head->next;
    }
    return (ft_strdup(""));
}

t_env   *is_exist(t_env *head, char *key)
{
    while (head)
    {
        if (!ft_strcmp(key, head->key))
            return (head);
        head = head->next;
    }
    return (NULL);

}

t_env   *add_env(t_env **head, char *key, char *value, t_call call)
{
    t_env   *tmp;
    t_env   *new;

    tmp = is_exist(*head, key);
    (call != NEW && tmp) && (tmp->hidden = false);
    if (tmp && call == ADD)
        return (tmp->value = ft_strjoin(tmp->value, value), tmp);
    if (tmp && call == CHANGE)
        return (tmp->value = value, tmp);
    new = new_env_node(key, value);
    if (!new)
        return (NULL);
    if (!*head)
        *head = new;
    else
    {
        tmp = *head;
        while (tmp && tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (*head);
}

void    *del_key(t_env **head, char *key)
{
    t_env   *tmp;
    t_env   *prev;

    tmp = *head;
    while (tmp)
    {
        if (!ft_strcmp(key, tmp->key))
        {
            if (tmp == *head)
                *head = (*head)->next;
            else
                prev->next = tmp->next;
            return (NULL);
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return (NULL);
}

void    *change_var(t_env *head, char *key, char *value)
{
    while (head)
    {
        if (!ft_strcmp(key, head->key))
            return (head->value = value, NULL);
        head = head->next;
    }
    return (NULL);
}

void prnt_env(int fd)
{
    t_env   *env;

    env = _env_(NULL, NULL, NULL, GET_STRCT);
    while (env)
    {
        if (!env->hidden)
        {
            ft_putstr_fd(env->key, fd);
            ft_putstr_fd("=", fd);
            ft_putstr_fd(env->value, fd);
            ft_putstr_fd("\n", fd);
        }
        env = env->next;
    }
}

int env_len(t_env *node)
{
    int i;

    i = 0;
    while (node)
    {
        node = node->next;
        if (!node->hidden || (!ft_strcmp(node->key, "_") && node->value))
            i++;
    }
    return (i);
}

char    **get_env_char(t_env *head)
{
    char    **ret;
    char    *tmp;
    int     i;

    ret = malloc(sizeof(char *) * (env_len(head) + 1));
    if (!ret)
        return (NULL);
    i = 0;
    while (head)
    {
        if (!head->hidden || (!ft_strcmp(head->key, "_") && head->value))
        {
            tmp = ft_strjoin(head->key, "=");
            (tmp) && (tmp = ft_strjoin(tmp, head->value));
            if (!tmp)
                return (NULL);
            ret[i++] = tmp;
        }
    }
    ret[i] = NULL;
    return (ret);
}

void	ft_swap(t_env *a, t_env *b)
{
	char	*key;
	char	*value;
	bool	hidden;

	key = a->key;
	value = a->value;
	hidden = a->hidden;
	a->key = b->key;
	a->value = b->value;
	a->hidden = b->hidden;
	b->key = key;
	b->value = value;
	b->hidden = hidden;
}

void	sort_export(t_env *head)
{
	t_env	*ptr1;
	t_env	*lptr;
	int		swapped;

	lptr = NULL;
	if (head == NULL)
		return ;
	while (1)
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				ft_swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		if (!swapped)
			break ;
		lptr = ptr1;
	}
}

t_env   *copy_env(t_env *head)
{
    t_env   *ret;
    t_env   *tmp;

    ret = NULL;
    while (head)
    {
        tmp = copy_node(head);
        if (!tmp)
            return (NULL);
        if (!add_env(&ret, tmp->key, tmp->value, NEW))
            return (NULL);
        head = head->next;
    }
    return (ret);
}

int disp_exprt(int fd)
{
    t_env   *tmp;

    tmp = copy_env(_env_(NULL, NULL, NULL, GET_STRCT));
    if (!tmp)
        return (0);
    sort_export(tmp);
    while (tmp)
    {
        if (ft_strcmp(tmp->value, "_"))
        {
            ft_putstr_fd("declare -x ", fd);
            ft_putstr_fd(tmp->key, fd);
            if (tmp->value)
            {
                ft_putstr_fd("=\"", fd);
                ft_putstr_fd(tmp->value, fd);
                ft_putstr_fd("\"\n", fd);
            }
            else
                ft_putstr_fd("\"\n", fd);
        }
        tmp = tmp->next;
    }
    return (1);
}

void    *_env_(char **env, char *key, char *value, t_call call)
{
    static t_env    *head;

    if (call == GET_STRCT)
        return (head);
    else if (call == INIT)
        return (create_env(env, &head));
    else if (call >= 1 && call <= 3)
        return (add_env(&head, key, value, call));
    else if (call == SEARCH)
        return (get_var(head, key));
    else if (call == REMOVE)
        return (del_key(&head, key));
    else if (call == GET_CHAR)
        return (get_env_char(head));
    return (NULL);
}
