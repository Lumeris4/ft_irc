MAKEFLAGS += --silent

NAME = ircserv

CC = c++
CFLAGS = -Wall -Wextra -Werror -g3 -std=c++98

OBJDIR = obj

SRCS = main.cpp parsing/Parsing.cpp parsing/Check_password.cpp Server.cpp Channel.cpp User.cpp HandleMode.cpp
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR) && cd $(OBJDIR) && mkdir parsing

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[32m✔ Compilation completed\033[0m"

clean:
	$(RM) -r $(OBJDIR)
	@echo "\033[33m✔ $(OBJDIR) suppressed\033[0m"

fclean: clean
	$(RM) $(NAME)
	@echo "\033[31m✔ $(NAME) suppressed\033[0m"

re: fclean all
