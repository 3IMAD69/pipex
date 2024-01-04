
SRCM	= pipex.c pipex_utils.c

OBJM	= ${SRCM:.c=.o}

CFLAGS	= -Wall -Werror -Wextra -g -fsanitize=address 
CC		= cc

NAME	= pipex
LIBFTA 	= ./libft/libft.a


all : ${NAME}


${LIBFTA} : 
	make -C libft

${NAME}:	${OBJM} ${LIBFTA}
	${CC} ${CFLAGS} ${OBJM} ${LIBFTA} ${LINKS} -o ${NAME}


clean:
	rm -f ${OBJM} 

fclean:		clean
	rm -f ${NAME} 

re:			fclean all

run : 
	./pipex infile "ls -l" "wc -l" outfile
	@cat outfile
.SECONDARY : ${OBJM}
.PHONY: all bonus clean fclean re

