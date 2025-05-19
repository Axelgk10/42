static char	*read_from_fd(int fd, char *buffer, char *backup)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(backup, '\n'))
	{
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
	}
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!backup)
			backup = ft_strdup("");
		if (!backup)
			return (NULL);
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		free (temp);
		if (!backup)
			return (NULL);
	}
	return (backup);
}

static char	*extract_line(char *line)
{
	char	*start;
	char	*end;
	size_t	len;

	if (!line)
		return (NULL);
	start = line;
	while (*start == ' ' || (*start >= '\t' || *start <= '\r'))
		start++;
	while (*start == '\0')
		return (ft_strdup(""));
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || (*end >= '\t' || *end <= '\r')))
		end--;
	len = end - start + 1;
	return (ft_substr(start, 0, len));
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;
	static char	*backup;

	backup = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc (sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = read_from_fd(fd, buffer, backup);
	free(buffer);
	if (!line)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = extract_line(line);
	return (line);
}
