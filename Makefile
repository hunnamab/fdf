NAME = fdf
FLAGS = -Wall -Wextra -L. -lmlx -framework OpenGL -framework AppKit
#-lmlx -lX11 -lXext for linux
#-lmlx -framework OpenGL -framework AppKit for mac
LIBRARY = libft/libft.a
HEADER = fdf.h
SRC = fdf.c map_read.c coordinates.c get_next_line.c control.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c
		gcc -c $(FLAGS) -I libft/ -o $@ $<

$(LIBRARY):
		@make -C libft/

$(NAME): $(LIBRARY) $(OBJ)
		@gcc $(OBJ) $(LIBRARY) -o $(NAME) -lmlx -framework OpenGL -framework AppKit -L.

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all
