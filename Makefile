


all : 
	@cc main.c pipex_utils.c -g -fsanitize=address libft/ft_strnstr.c libft/ft_strncmp.c libft/ft_memmove.c libft/ft_split.c libft/ft_strdup.c  libft/ft_strlen.c libft/ft_strjoin.c libft/ft_isalpha.c libft/ft_memcpy.c \
	libft/ft_strlcpy.c libft/ft_strlcat.c \
	-g -fsanitize=address && ./a.out infile "cat" "wc -l" outfile