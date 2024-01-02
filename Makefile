


all : 
	@cc main.c libft/ft_strnstr.c libft/ft_strncmp.c libft/ft_split.c libft/ft_strdup.c  libft/ft_strlen.c libft/ft_strjoin.c libft/ft_memcpy.c -g -fsanitize=address && ./a.out infile "ls -l" "wc -l" outfile