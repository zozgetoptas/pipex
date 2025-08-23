NAME	= libft.a

SRC	= ft_strlen.c \
		  ft_strchr.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_strrchr.c \
		  ft_strncmp.c \
		  ft_atoi.c \
		  ft_bzero.c \
		  ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isprint.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_memset.c \
		  ft_memcpy.c \
		  ft_memmove.c \
		  ft_memcmp.c \
		  ft_memchr.c \
		  ft_strdup.c \
		  ft_calloc.c \
		  ft_strnstr.c \
		  ft_substr.c \
		  ft_striteri.c \
	      ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_strmapi.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c

BONUS_SRC = ft_lstnew_bonus.c \
            ft_lstadd_front_bonus.c \
            ft_lstsize_bonus.c \
            ft_lstlast_bonus.c \
            ft_lstadd_back_bonus.c \
            ft_lstdelone_bonus.c \
            ft_lstclear_bonus.c \
            ft_lstiter_bonus.c \
            ft_lstmap_bonus.c
INC		= libft.h

OBJ	= $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
CC		= cc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -I. -c $< -o $@
all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)
bonus: $(BONUS_OBJ)
	ar -rcs $(NAME) $(BONUS_OBJ)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean:	clean
	$(RM) $(NAME)


re: fclean all



.PHONY:			all clean fclean re bonus
