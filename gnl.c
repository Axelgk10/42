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

static char	*update_backup(char *backup)
{
	int		i;
	int		j;
	char	*new_backup;

	i = 0;
	j = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	new_backup = malloc(ft_strlen(backup) - i + 1);
	if (!new_backup)
		return (NULL);
	j = 0;
	while (backup[++i])
		new_backup[j++] = backup[i];
	new_backup[j] = '\0';
	free(backup);
	return (new_backup);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*backup;

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
	line = extract_line(backup);
	backup = update_backup(backup);
	return (line);
}
