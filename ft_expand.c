

// char	*ft_strrange(char *s, int start, int end)
// {
// 	int		i;
// 	char	*str;

// 	str = ft_malloc(end - start + 1);
// 	i = 0;
// 	while (start < end)
// 		str[i++] = s[start++];
// 	return (str);
// }
// bool	special_letter(char l)
// {
// 	char	*s;
// 	int		i;

// 	i = 0;
// 	s = "$=/*-+\"\'@!#%^.*:";
// 	if (l == ' ' || (l >= 9 && l <= 13))
// 		return (true);
// 	while (s[i])
// 	{
// 		if (s[i] == l)
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }
// char	*get_key(char *s)
// {
// 	t_expanding	e;
// 	int			i;
// 	char		*str;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 		{
// 			e.start = i++;
// 			while (s[i] && !special_letter(s[i]))
// 				i++;
// 			e.end = i;
// 			break ;
// 		}
// 		i++;
// 	}
// 	str = ft_strrange(s, e.start, e.end);
// 	return (str);
// }
// char *expand_exit_status(int status)
// {
//     char *str;

//     str = ft_itoa(status);
//     return (str);
// }
// char *expanding_valuess(char *key, t_env *env)
// {
//     t_env *tmp;
//     char *value;

//     tmp = env;
//     while (tmp)
//     {
//         if (!ft_strcmp(tmp->key, key))
//         {
//             value = ft_strdup(tmp->value);
//             return (value);
//         }
//         tmp = tmp->next;
//     }
//     return (ft_strdup(""));
// }
// char	*expansion(char *s, t_minishell *mini)
// {
//     int i = 0;
//     char *buffer = NULL;
//     char *tmp;

//     while (s[i])
//     {
//         if (s[i] == '\'')
//         {
//             e.start = i++;
//             while (s[i] != '\'')
//                 i++;
//             e.end = i;
//             tmp = ft_strrange(s, e.start + 1, e.end);
//             printf("tmp:%s\n", tmp);
//             buffer= ft_strjoin(buffer, tmp);
//         }
//         else if (s[i] == '\"')
//         {
//             if (s[i + 1] == '\"')
//             {
//                 i++;
//                 buffer= ft_strjoin(buffer, "");
//             }
//             else
//             {
//                 e.start = i++;
//                 while (s[i] && s[i] != '\"')
//                     i++;
//                 e.end = i--;
//                 tmp = ft_strrange(s, e.start + 1, e.end);
//                 if (checkexpanding(tmp))
//                 {
//                     int j = 0;
//                     while (tmp[j])
//                     {
//                         if (tmp[j] == '$')
//                         {
//                         e.key = get_key(tmp + j);
//                         j += ft_strlen(e.key) - 1;
//                         e.value = expanding_valuess(e.key + 1, env);
//                         buffer = ft_strjoin(buffer, e.value);
//                         }
//                         else
//                         {
//                             e.start = j;
//                             while (tmp[j] && tmp[j] != '$')
//                                 j++;
//                             e.end = j--;
//                             e.value = ft_strrange(tmp, e.start,e.end);
//                             buffer = ft_strjoin(buffer, e.value);
//                         }
//                         j++;
//                     }
//                 }
//                 else
//                 {
//                     buffer = ft_strjoin(buffer, tmp);
//                 }
//                 i++;
//             }
//         }
//         else if (s[i] == '$')
//         {
//             if (s[i + 1] == '$' && s[i + 2] == 0)
//             {
//                 buffer = ft_strjoin(buffer, ft_strdup("$"));
//                 i++;
//             }else if (s[i + 1] == '?')
//             {
//                 buffer = ft_strjoin(buffer, expand_exit_status(get_exitst(0,false)));
//                 i++;
//             }else if (s[i + 1] == '\"' || s[i + 1] == '\'')
//                 i++;
//             else
//             {
//                 e.key = get_key(s + i);
//                 i += ft_strlen(e.key) - 1;
//                 tmp = expanding_valuess(e.key + 1, env);
//                 buffer = ft_strjoin(buffer, tmp);
//             }
//         }
//         else 
//         {
//             e.start = i;
//             while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
//                 i++;
//             tmp = ft_strrange(s, e.start, i--);
//             buffer = ft_strjoin(buffer, tmp);
//         }
//         i++;
//     }
//     return (buffer);
// }
