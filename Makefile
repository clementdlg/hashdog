NAME	=	hashdog

SRC		=	main.c						\
			functions/arguments.c		\
			functions/bruteforceAtk.c	\
			functions/checkDigest.c		\
			functions/dictAtk.c			\
			functions/config.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall #-Wextra -iquote include
LDFLAGS	=	-lcrypto

all:	$(NAME)

$(NAME):	$(OBJ)
	@gcc -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re:	fclean all
