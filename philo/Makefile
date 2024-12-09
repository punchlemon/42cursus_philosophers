.PHONY: all clean fclean re val norm test
NAME = philosopher

INCLUDES_DIR = includes
SRCS_DIR = srcs
OUT_DIR = out

RESET = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
WHITE = \033[37m

SRCS = \
$(addsuffix .c, \
	$(addprefix $(SRCS_DIR)/, \
		destroy \
		ft_atoi \
		main \
		my_sleep \
		philo_die \
		philo_eat \
		philo_life \
		philo_sleep \
		philo_think \
		print_time \
		put_stderr \
		run \
		valid \
	) \
) \

OBJS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))

NPD_FLAG = --no-print-directory

CFLAGS = -Wall -Werror -Wextra
IFLAGS = -I$(INCLUDES_DIR)
VFLAGS = \
	--leak-check=full \
	--show-leak-kinds=all \

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LFLAGS) -o $@

$(OUT_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OUT_DIR)

fclean: clean
	@$(RM) $(NAME) $(VALGRIND_LOG)

re: fclean all

de:
	@clear
	@make $(NPD_FLAG) re

VALGRIND_LOG = valgrind.log

val:
	@clear
	@make $(NPD_FLAG) re
	@valgrind $(VFLAGS) ./$(NAME) 2> $(VALGRIND_LOG)

norm:
	@$(call check_norminette, $(SRCS_DIR))
	@$(call check_norminette, $(INCLUDES_DIR))

define ok
	echo $1"$(GREEN)OK$(RESET)"
endef

define check_norminette
	@if norminette $1 | grep -q Error; then \
		norminette $1 | grep Error; \
	else \
		$(call ok, $1": "); \
	fi
endef
