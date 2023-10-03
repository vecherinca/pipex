NAME = pipex
CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC =  \
	pipex.c \
	exec.c \
	init.c \
	free.c \
	here_doc.c \
	ft_split.c \
	help_red.c \
	helpers.c \
	helpers2.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c \


OBJ = $(SRC:.c=.o)
.SILENT:

all : ${NAME}

${NAME} : ${OBJ}
	$(CC) $(OBJ) -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "yo pipex is created let's go pipe hope it compiles"
.o: .c
	${CC} -c ${CFLAGS} $< -o $@

clean: 
	rm -f $(OBJ) 
	printf '\033[32m[ ✔ ] %s\n\033[0m' "cleeeaninngggggg"
	
fclean: clean
	rm -f $(NAME) 
	printf '\033[32m[ ✔ ] %s\n\033[0m' "cleeeaninngggggg all"

re: fclean all
	printf '\033[32m[ ✔ ] %s\n\033[0m' "restarted with success hope it compiles"

.PHONY: all clean fclean re all 