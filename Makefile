NAME = ircserv

BOT = bot

# Colors

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;36m
DEFAULT = \033[0m

# Directories

SRCDIR = src

OBJDIR = lib

COMMANDS = $(SRCDIR)/commands

CHECK = $(SRCDIR)/check

BOTDIR = $(SRCDIR)/bot


# Files

SRCS = $(wildcard $(SRCDIR)/*.cpp $(COMMANDS)/*.cpp $(CHECK)/*.cpp)

OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Compiler
CXX = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -I include

# Rules
all: $(NAME)

$(BOT):
	@make -C $(BOTDIR)

removebot:
	@make -C $(BOTDIR) fclean

$(NAME): $(OBJS)
	@$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) compiled"
	@echo "$(DEFAULT)Usage: ./$(NAME) <port> <password>"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "$(BLUE)Compiling $<"
	@$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	@make -C $(BOTDIR) clean
	@if [ -f $(OBJDIR)/main.o ]; then \
		rm -f $(OBJS); \
		echo "$(RED)$(NAME) objects deleted"; \
	fi

fclean: clean
	@make -C $(BOTDIR) fclean
	@if [ -f $(NAME) ]; then \
		rm -f $(NAME); \
		echo "$(RED)$(NAME) deleted"; \
	fi

re: fclean all

rebot: removebot $(BOT)

.PHONY: all clean fclean re
