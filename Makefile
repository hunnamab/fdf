NAME = fdf
FLAGS = -Wall -Wextra -L. -lmlx -framework OpenGL -framework AppKit
#-lmlx -lX11 -lXext -lm for linux
#-lmlx -framework OpenGL -framework AppKit for mac
LIBRARY = libft/libft.a
HEADER = fdf.h
SRC = fdf.c get_next_line.c key_mouse_control.c map_changes.c map_read_2.c \
		map_settings.c matrix_manipulations.c points_output.c projections.c \
		menu.c colors.c errors.c validation.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c
		gcc -c $(FLAGS) -I libft/ -o $@ $<

$(LIBRARY):
		@make -C libft/

$(NAME): $(LIBRARY) $(OBJ)
		@gcc $(OBJ) $(LIBRARY) -o $(NAME) -lmlx -framework OpenGL -framework AppKit

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all
