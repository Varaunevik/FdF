NAME = fdf

#----------------DIRECTORIES------------#
INC_DIR = includes/
SRCS_DIR = srcs/
LIB_DIR = libraries/
OBJ_DIR = obj/

#-------------------FILES----------------#
LIBS = $(LIB_DIR)minilibx_macos/libmlx.a
LIB_HEADERS = -I$(LIB_DIR)minilibx_macos

INC = -I$(INC_DIR) $(LIB_HEADERS)
H_FILES = $(INC_DIR)fdf_structs.h $(INC_DIR)fdf.h $(INC_DIR)get_next_line.h

SRCS = $(SRCS_DIR)draw_line.c \
	   $(SRCS_DIR)gnl/get_next_line.c \
	   $(SRCS_DIR)gnl/get_next_line_utils.c \
	   $(SRCS_DIR)error_utils.c \
	   $(SRCS_DIR)fdf.c \
	   $(SRCS_DIR)image.c \
	   $(SRCS_DIR)keyhooks.c \
	   $(SRCS_DIR)mousehooks.c \
	   $(SRCS_DIR)parse.c \
	   $(SRCS_DIR)perspective.c \
	   $(SRCS_DIR)transform.c \
	   $(SRCS_DIR)color.c \
	   $(SRCS_DIR)std_utils.c \
	   $(SRCS_DIR)main.c \
	   $(SRCS_DIR)utils.c

OBJ = $(patsubst $(SRCS_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

#-----------------COMPILING-------------#
CC = gcc
CFLAGS = -Wall -Werror -Wextra $(INC)
MLXFLAGS = -framework OpenGL -framework AppKit

#-------------------RULES---------------#
$(OBJ_DIR)%.o:$(SRCS_DIR)%.c $(LIBS)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) -o $@ $<
	@echo "Compiling $<"

all: lib $(NAME)

bonus: all

lib:
	@make -C $(LIB_DIR)minilibx_macos

$(NAME): $(OBJ) $(LIBS) Makefile $(LIB_DIR) $(H_FILES)
	@$(CC) $(OBJ) $(MLXFLAGS) $(LIBS) -o $(NAME)
	@echo "Built $(NAME)"

clean: 
		make clean -C $(LIB_DIR)minilibx_macos
		rm -rf $(OBJ_DIR)

fclean: 
		make clean -C $(LIB_DIR)minilibx_macos
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
