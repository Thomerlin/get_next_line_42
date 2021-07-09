#include "get_next_line.h"

char	*write_beginning(char *buf)
{
	char	*bgn;
	size_t	len_buf;
	size_t	i;

	i = 0;
	len_buf = ft_strlen(buf, '\n');
	bgn = malloc(sizeof(char) * (len_buf + 1));
	if (bgn == NULL)
		return (NULL);
	while (i < len_buf)
	{
		bgn[i] = buf[i];
		i++;
	}
	bgn[i] = '\0';
	return (bgn);
}

char	*write_end(char **line, char *buf, int *end)
{
	char	*bgn;
	char	*dest;
	size_t	i;

	i = 0;
	bgn = write_beginning(buf);
	dest = ft_strdup(buf);
	line[i] = ft_strjoin(line[i], bgn);
	if (bgn == NULL || dest == NULL || line[i] == NULL)
	{
		free(line[i]);
		line[i] = NULL;
		free(buf);
		return (NULL);
	}
	free(bgn);
	end[i] = 1;
	return (dest);
}

int	read_buf(int fd, int *result, char **line, char **buf)
{
	size_t	i;

	i = 0;
	buf[i] = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	result[i] = read(fd, buf[i], BUFFER_SIZE);
	if (buf[i] == NULL || result[i] == -1)
	{
		free(line[i]);
		line[i] = NULL;
		free(buf[i]);
		return (0);
	}
	*(buf[i] + result[i]) = '\0';
	while ((ft_strchr(buf[i], '\n')) == NULL && result[i] > 0)
	{
		line[i] = ft_strjoin(line[i], buf[i]);
		if (line[i] == NULL)
			return (0);
		result[i] = read(fd, buf[i], BUFFER_SIZE);
		if (result[i] == '\0')
			return (1);
		*(buf[i] + result[i]) = '\0';
	}
	return (2);
}

int	process_end(char **line, char **end, int *is_end)
{
	size_t	i;

	i = 0;
	if (ft_strchr(end[i], '\n'))
	{
		end[i] = write_end(line, end[i], is_end);
		if (end[i] == NULL)
			return (0);
		return (1);
	}
	line[i] = ft_strjoin(line[i], end[i]);
	if (line[i] == NULL)
		return (0);
	free(end[i]);
	is_end[i] = 0;
	return (2);
}

int	get_next_line(int fd, char **line)
{
	static int	is_end;
	static char	*end;
	char		*bf;
	int			res;

	if (fd < 0 || BUFFER_SIZE < 1 || !line || (!*line = malloc(sizeof(char))))
		return (-1);
	**line = '\0';
	if (is_end != '\0')
	{
		if ((res = process_end(line, &end, &is_end)) == '\0')
			return (-1);
		if (res == 1)
			return (1);
	}
	if ((read_buf(fd, &res, line, &bf)) == '\0')
		return (-1);
	if (ft_strchr(bf, '\n') && (end = write_end(line, bf, &is_end)) == NULL)
		return (-1);
	if (res == '\0')
	{
		free(bf);
		return (0);
	}
	return (1);
}
