.PHONY: all clean fclean re
NAME = libft.a

INCLUDES_DIR = includes
SRCS_DIR = srcs
OUT_DIR = out

SRCS = \
$(addsuffix .c, \
	$(addprefix $(SRCS_DIR)/, \
		$(addprefix is/, \
			ft_isalpha \
			ft_isdigit \
			ft_isspace \
		) \
		$(addprefix put/, \
			ft_put_fd \
			ft_put_str_fd \
		) \
		$(addprefix str/, \
			ft_atoi \
			ft_strlen \
		) \
	) \
) \

OBJS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))

CC = clang
NPK_FLAG = --noprint-directory

CFLAGS = -Wall -Werror -Wextra
IFLAGS = -I$(INCLUDES_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) rcs $@ $(OBJS)

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@$(RM) -rf $(OUT_DIR)

fclean: clean
	@$(RM) $(NAME) $(VALGRIND_LOG)

re: fclean all
