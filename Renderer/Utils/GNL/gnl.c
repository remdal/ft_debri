/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                        +       +          */
/*      File: gnl.c            +++     +++					**/
/*                                        +       +          */
/*      By: Laboitederemdal      **        +       +        **/
/*                                       +           +       */
/*      Created: 22/09/2025 11:22:30      + + + + + +   * ****/
/*                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "gnl.h"

# define BUFFER_SIZE 42

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (0);
	if ((char)c == '\0')
		return ((char *)s);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}

char	*ft_strcpy(char *str, char *leftover)
{
	int	i;

	i = 0;
	while (leftover[i])
	{
		str[i] = leftover[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strcat(char *str, char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		i++;
	}
	while (buff[j])
	{
		str[i + j] = buff[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strjoin(char *leftover, char *buff)
{
	char	*str;
	size_t	length;

	if (!leftover)
	{
		leftover = (char *)malloc(sizeof(char) * 1);
		leftover[0] = '\0';
	}
	if (!leftover || !buff)
		return (NULL);
	length = ft_strlen(leftover) + ft_strlen(buff) + 1;
	str = (char *)malloc(sizeof(char) * length);
	if (str == NULL)
		return (NULL);
	if (leftover)
		ft_strcpy(str, leftover);
	ft_strcat(str, buff);
	free(leftover);
	return (str);
}

char	*ft_read_before_newline(int fd, char *leftover)
{
	char	*buff;
	ssize_t	bytes_read;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(leftover, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		leftover = ft_strjoin(leftover, buff);
	}
	free(buff);
	return (leftover);
}

char	*ft_line_from_leftover(char *leftover)
{
	int		i;
	char	*line;

	i = 0;
	if (!leftover[i])
		return (NULL);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
	{
		line[i] = leftover[i];
		i++;
	}
	if (leftover[i] == '\n')
	{
		line[i] = leftover[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_trim_leftover(char *leftover)
{
	int		i;
	int		j;
	char	*new_leftover;

	i = 0;
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
	{
		free(leftover);
		return (NULL);
	}
	new_leftover = (char *)malloc(sizeof(char) * (ft_strlen(leftover) - i + 1));
	if (!new_leftover)
		return (NULL);
	i++;
	j = 0;
	while (leftover[i])
		new_leftover[j++] = leftover[i++];
	new_leftover[j] = '\0';
	free(leftover);
	return (new_leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	leftover = ft_read_before_newline(fd, leftover);
	if (!leftover)
		return (NULL);
	line = ft_line_from_leftover(leftover);
	leftover = ft_trim_leftover(leftover);
	return (line);
}