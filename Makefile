NAME = ircserv

# Colors

RED = \033[0;31m
GREEN = \033[0;32m
BLUE = \033[0;36m
DEFAULT = \033[0m

# Directories

SRCDIR = src

OBJDIR = lib

# Files

SRCS = $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*/*.cpp)

OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Compiler
CXX = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -I include

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) compiled"
	@echo "$(DEFAULT)Usage: ./$(NAME) <port> <password>"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "$(BLUE)Compiling $<"
	@$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	@if [ -f $(OBJDIR)/main.o ]; then \
		rm -f $(OBJS); \
		echo "$(RED)$(NAME) objects deleted"; \
	fi

fclean: clean
	@if [ -f $(NAME) ]; then \
		rm -f $(NAME); \
		echo "$(RED)$(NAME) deleted"; \
	fi

re: fclean all

.PHONY: all clean fclean re
