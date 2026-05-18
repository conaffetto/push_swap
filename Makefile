
# variables definitions
NAME = push_swap

# compilation flags and linker flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

LDFLAGS = $(foreach dir,$(SLIB_DIRS),-L$(dir)/bin/)
LDLIBS = $(foreach lib,$(LIBS),-l$(patsubst lib%.a,%,$(notdir $(lib))))

# header
HEADER = $(SRC_DIR)/$(NAME).h

# source and object files
SRCS = $(addprefix $(SRC_DIR)/, main.c utils.c memory_control.c parsing.c \
	parsing_utils.c indexing.c double_pivot_quick_sort.c ps_instructions.c \
	split_and_sort.c split_utils.c sorting.c split_max_utils.c \
	split_mid_utils.c split_min_utils.c sort_top_a.c merge_bottom_a.c \
	merge_top_b.c merge_bottom_b.c early_sort_optimization.c)
OBJS = $(addprefix $(OBJ_DIR)/, $(patsubst $(SRC_DIR)/%.c, %.o, $(SRCS)))

# subdirectories
SRC_DIR = sources
OBJ_DIR = objects
BIN_DIR = bin
SLIB_DIRS = libft

# static libraries
LIBS = ./libft/bin/libft.a

# rules
$(NAME): build_libs
	@make CFLAGS="$(CFLAGS)" --no-print-directory $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(LIBS) $(OBJS) | $(BIN_DIR)
	@echo "linking object files and static libraries into program: $(NAME)"
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(BIN_DIR):
	@mkdir -p $@

build_libs:
	$(foreach dir,$(SLIB_DIRS),make --no-print-directory -C $(dir) \
		CFLAGS="$(CFLAGS)";)

all: $(NAME)

clean:
	@echo "cleaning all object files for program: $(NAME)"
	$(foreach dir,$(SLIB_DIRS),make --no-print-directory clean -C $(dir);)
	rm -rf $(OBJ_DIR)

fclean:
	@echo "cleaning all object files, as well as the static library and the \
	executable for program: $(NAME)"
	$(foreach dir,$(SLIB_DIRS),make --no-print-directory fclean -C $(dir);)
	rm -rf $(OBJ_DIR) $(BIN_DIR)

re: fclean all

.PHONY: all clean fclean re build_libs
