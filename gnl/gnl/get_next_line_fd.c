#include "get_next_line_multiple_fd.h"

char	*get_next_line(int fd)
{
	char			*str;
	static char		*string[256];
	char			*tmp;

	if ((read(fd, 0, 0) == -1) || BUFFER_SIZE <= 0)
		return (NULL);
	string[fd] = read_file(fd, string[fd]);
	if (!string[fd])
		return (NULL);
	if (chr_src(string[fd], '\n') > 0 || string[fd][0] == '\n')
	{
		str = make_string(NULL, string[fd], chr_src(string[fd], '\n') + 1);
		tmp = string[fd];
		string[fd] = make_string(NULL,
				&string[fd][chr_src(string[fd], '\n') + 1], -1);
		free(tmp);
		return (str);
	}
	str = make_string(NULL, string[fd], -1);
	if (string[fd])
		free(string[fd]);
	string[fd] = NULL;
	return (str);
}

char	*read_file( int fd, char *string)
{
	ssize_t		n_byte;
	char		*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	n_byte = 1;
	while (n_byte > 0)
	{
		n_byte = read(fd, buff, BUFFER_SIZE);
		buff[n_byte] = '\0';
		if (chr_src (buff, '\n') > 0 || buff[0] == '\n')
			return (ft_return_string(string, buff));
		string = make_string(string, buff, -1);
	}
	free (buff);
	if (string[0] == '\0')
	{
		free(string);
		string = NULL;
	}
	return (string);
}

char	*make_string(char *tail, char *head, size_t n_byte)
{
	size_t	j;
	size_t	i;
	char	*str;

	i = str_len(tail);
	j = 0;
	while (head[j] && j < n_byte)
		j++;
	str = malloc(i + j + 1);
	if (!str)
		return (NULL);
	str = ft_cpy(j, str, tail, head);
	if (tail)
		free (tail);
	return (str);
}
