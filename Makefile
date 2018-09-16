NAME1 = server
NAME2 = client

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INC = Includes

COMMON = common
COMMON_INC = common
COMMON_SDIR = common

SDIR = Srcs

SRCS1 =	parse_args.c\
		start_server.c\
		choose_necessary_sockets.c\
		examine_sockets.c\
		accept_incoming_connection.c\
		read_incoming_data.c\
		process_server_stdin.c\
		process_incoming_data.c\
		is_command.c\
		is_who_command.c\
		is_leave_command.c\
		is_msg_command.c\
		is_exit_command.c\
		execute_client_command.c\
		execute_nick_command.c\
		execute_join_command.c\
		execute_leave_command.c\
		execute_who_command.c\
		execute_msg_command.c\
		execute_exit_command.c\
		remove_processed_data.c\
		send_data_to_clients.c\
		disconnect_clients.c\
		main.c

SRCS2 =	is_connect_command.c\
		main.c

COMMON_SRCS =	send_msg.c\
				receive_msg.c


HEADERS1 = server.h\
			typedefs.h

HEADERS2 = client.h

COMMON_HEADERS = common.h

ODIR = Objects

OBJ1 = $(SRCS1:.c=.o)

OBJ1_R = $(OBJ1:%.o=$(ODIR)/$(NAME1)/%.o)

OBJ2 = $(SRCS2:.c=.o)

OBJ2_R = $(OBJ2:%.o=$(ODIR)/$(NAME2)/%.o)

COMMON_OBJ = $(COMMON_SRCS:.c=.o)

COMMON_OBJ_R = $(COMMON_OBJ:%.o=$(ODIR)/$(COMMON_SDIR)/%.o)

all : $(NAME1) $(NAME2)

$(NAME1) : $(COMMON) $(ODIR)/$(NAME1)/ $(OBJ1_R)
	make -C Libs/libft
	$(CC) $(CFLAGS) -o $(NAME1) $(OBJ1_R) $(COMMON_OBJ_R) Libs/libft/libft.a

$(NAME2) : $(COMMON) $(ODIR)/$(NAME2)/ $(OBJ2:%.o=$(ODIR)/$(NAME2)/%.o)
	make -C Libs/libft
	$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2_R)  $(COMMON_OBJ_R) Libs/libft/libft.a

$(COMMON) :  $(ODIR)/$(COMMON_SDIR)/ $(COMMON_OBJ:%.o=$(ODIR)/$(COMMON_SDIR)/%.o)

.PHONY: clean1 fclean1 dfclean1 re1 clean fclean re

clean1 :
	rm -f $(OBJ1:%.o=$(ODIR)/$(NAME1)/%.o)

fclean1 : clean1
	rm -f $(NAME1)

re1 : fclean1 $(NAME1)

clean2 :
	rm -f $(OBJ2:%.o=$(ODIR)/$(NAME2)/%.o)

fclean2 : clean2
	rm -f $(NAME2)

re2 : fclean2 $(NAME2)

clean: clean1 clean2

fclean : fclean1 fclean2
	make fclean -C Libs/libft

re : re1 re2

norm:
	make norm -C Libs/libft
	norminette $(SRCS1:%.c=$(SDIR)/$(NAME1)/%.c) $(HEADERS1:%.h=$(INC)/$(NAME1)/%.h)\
				$(SRCS2:%.c=$(SDIR)/$(NAME2)/%.c) $(HEADERS2:%.h=$(INC)/$(NAME2)/%.h)\
				$(COMMON_SRCS:%.c=$(SDIR)/$(COMMON_SDIR)/%.c) $(COMMON_HEADERS:%.h=$(INC)/$(COMMON_INC)/%.h)

add:
	make add -C Libs/libft
	git add $(SRCS1:%.c=$(SDIR)/$(NAME1)/%.c) $(HEADERS1:%.h=$(INC)/$(NAME1)/%.h)\
			$(SRCS2:%.c=$(SDIR)/$(NAME2)/%.c) $(HEADERS2:%.h=$(INC)/$(NAME2)/%.h)\
			$(COMMON_SRCS:%.c=$(SDIR)/$(COMMON_SDIR)/%.c) $(COMMON_HEADERS:%.h=$(INC)/$(COMMON_INC)/%.h)\
			.gitignore Makefile CMakeLists.txt author

test1: $(NAME1)
	./$(NAME1) $(NAME1)

$(ODIR)/$(NAME1)/ :
	mkdir -p $@

$(ODIR)/$(NAME2)/ :
	mkdir -p $@

$(ODIR)/$(COMMON_SDIR)/ :
	mkdir -p $@

$(ODIR)/$(NAME1)/%.o : $(SDIR)/$(NAME1)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I Libs/libft -I $(INC)/$(NAME1) -I $(INC)/$(COMMON_INC)

$(ODIR)/$(NAME2)/%.o : $(SDIR)/$(NAME2)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I Libs/libft -I $(INC)/$(NAME2) -I $(INC)/$(COMMON_INC)

$(ODIR)/$(COMMON_SDIR)/%.o : $(SDIR)/$(COMMON_SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I Libs/libft -I $(INC)/$(COMMON_INC)
