NAME_C := client
NAME_S := server

OBJ_DIR := objs
LIBFT := ./libft

HEADERS := -I ./include -I $(LIBFT)/include
LIBS := $(LIBFT)/libft.a -ldl -lglfw -pthread -lm -g

SRC_C := client.c
SRC_S := server.c

OBJ_C := $(SRC_C:%.c=$(OBJ_DIR)/%.o)
OBJ_S := $(SRC_S:%.c=$(OBJ_DIR)/%.o)

RM := rm
CC := cc
MAKE := make
MAKE_DIR := mkdir

CFLAGS := -Wall -Wextra -Werror

#dont forget to add $(NAME_C)
all: $(NAME_S) $(NAME_C)

$(NAME_S): libft $(OBJ_DIR) $(OBJ_S)
	@$(CC) $(CFLAGS) $(OBJ_S) $(LIBS) $(HEADERS) -o $(NAME_S)
	@echo "$(NAME_S) built successfully!"

$(NAME_C): libft $(OBJ_DIR) $(OBJ_C)
	@$(CC) $(CFLAGS) $(OBJ_C) $(LIBS) $(HEADERS) -o $(NAME_C)
	@echo "$(NAME_C) built successfully!"

libft:
	@$(MAKE) -C $(LIBFT)

clean:
	@$(RM) -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean
	@echo "Bins successfully cleaned!"

#dont forget to add $(NAME_C)
fclean: clean
	@$(RM) -rf $(NAME_S) $(NAME_C)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "Everything successfully cleaned!"

re: fclean all

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(OBJ_DIR):
	@echo "Starting..."
	$(MAKE_DIR) $(OBJ_DIR)

.PHONY: all clean fclean re libft