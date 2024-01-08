
SRCM	= mandatory/pipex.c mandatory/pipex_utils.c mandatory/pipex_error.c

SRCB	= bonus/pipex_bonus.c bonus/pipex_utils_bonus.c bonus/pipex_utils2_bonus.c bonus/pipex_error_bonus.c

OBJM	= ${SRCM:.c=.o}

OBJB	= ${SRCB:.c=.o}

CFLAGS	= -Wall -Werror -Wextra -g -fsanitize=address 
CC		= cc

NAME	= pipex
NAME_BONUS = ./pipex_bonus

LIBFTA 	= ./libft/libft.a


all : ${NAME}

bonus : ${NAME_BONUS}

${LIBFTA} : 
	make -C libft

${NAME}:	${OBJM} ${LIBFTA}
	${CC} ${CFLAGS} ${OBJM} ${LIBFTA} ${LINKS} -o ${NAME}

${NAME_BONUS}: ${OBJB} ${LIBFTA}
	${CC} ${CFLAGS} ${OBJB} ${LIBFTA} ${LINKS} -o ${NAME_BONUS}

clean:
	rm -f ${OBJM} ${OBJB}

fclean:		clean
	rm -f ${NAME} ${NAME_BONUS}
#make -C libft fclean

re:			fclean all

run : fclean bonus
	./pipex_bonus /dev/random "cat" "head -n 5" "head -n 1" outfile
	@cat outfile

run2 : fclean bonus
	./pipex_bonus infile "cat" "cat /dev/random" "head -n 5" "head -n 1" outfile
	clear
	@cat outfile

runmand : 
	./pipex /dev/random "cat" "head -n 5" outfile
	@cat outfile

sleep : 
	./pipex_bonus /dev/random "sleep 2" "ls -l"  "ls -la" outfile
	@cat outfile

here : fclean bonus
	./pipex_bonus here_doc end "cat" "head -n 5" outfile
	@cat outfile

random : 
	< /dev/random cat | head -n 5 | head -n 1 > outfile
	@cat outfile


.SECONDARY : ${OBJM}
.PHONY: all bonus clean fclean re

