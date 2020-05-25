CC			=	clang++-6.0

FWARN		=	-Wall -Wextra -Werror
FSTD		=	-std=c++98
FDEBUG		=	-g
FOPTI		=	-O3 -Ofast
FLAGS		=	$(FWARN) $(FDEBUG) $(FOPTI)

NAME		=	tests
SUFFIX		=	_tests.cpp
DDIR		=	diffs
TDIR		=	container_tests
DIFF		=	./diff_script.sh

VECTOR		=	vector
LIST		=	list
STACK		=	stack
QUEUE		=	queue
MAP			=	map
MULTIMAP	=	multimap
SET			=	set
MULTISET	=	multiset
DEQUE		=	deque

all:	$(NAME)

$(NAME) :	$(VECTOR) $(LIST) $(STACK) $(QUEUE) $(MAP) $(MULTIMAP) $(SET) $(MULTISET) $(DEQUE)

correc:
	$(CC) $(FWARN) -Wno-unused-local-typedef $(FSTD) correc.cpp
	@./a.out

$(MAP):	$(TDIR)/$(MAP)$(SUFFIX)
	@printf "$(MAP) --> "
	@$(CC) $(FWARN) $(FSTD) $(TDIR)/$(MAP)$(SUFFIX) -o $(NAME)
	@./$(NAME)
	@$(DIFF) $(DDIR)/my_map.txt $(DDIR)/real_map.txt
	@rm $(NAME)

$(MULTIMAP):	$(TDIR)/$(MULTIMAP)$(SUFFIX)
	@printf "$(MULTIMAP) --> "
	@$(CC) $(FWARN) $(FSTD) $(TDIR)/$(MULTIMAP)$(SUFFIX) -o $(NAME)
	@./$(NAME)
	@$(DIFF) $(DDIR)/my_multimap.txt $(DDIR)/real_multimap.txt
	@rm $(NAME)

$(LIST):	$(TDIR)/$(LIST)$(SUFFIX)
	@printf "$(LIST) --> "
	@$(CC) $(FWARN) $(FSTD) $(TDIR)/$(LIST)$(SUFFIX) -o $(NAME)
	@./$(NAME)
	@$(DIFF) $(DDIR)/my_list.txt $(DDIR)/real_list.txt
	@rm $(NAME)

$(VECTOR):	$(TDIR)/$(VECTOR)$(SUFFIX) 
	@printf "$(VECTOR) --> "
	@$(CC) $(FWARN) $(FSTD) $(TDIR)/$(VECTOR)$(SUFFIX) -o $(NAME)
	@./$(NAME)
	@$(DIFF) $(DDIR)/my_vector.txt $(DDIR)/real_vector.txt
	@rm $(NAME)

$(STACK):	$(TDIR)/$(STACK)$(SUFFIX)
	@printf "$(STACK) --> "
	@$(CC) $(FWARN) $(FSTD) $(TDIR)/$(STACK)$(SUFFIX) -o $(NAME)
	@./$(NAME)
	@$(DIFF) $(DDIR)/my_stack.txt $(DDIR)/real_stack.txt
	@rm $(NAME)

$(SET):	$(TDIR)/$(SET)$(SUFFIX)
	@printf "$(SET) --> "
	@$(CC) $(FWARN) $(FSTD) $(TDIR)/$(SET)$(SUFFIX) -o $(NAME)
	@./$(NAME)
	@$(DIFF) $(DDIR)/my_set.txt $(DDIR)/real_set.txt
	@rm $(NAME)

$(MULTISET):	$(TDIR)/$(MULTISET)$(SUFFIX)
	@printf "$(MULTISET) --> "
	@$(CC) $(FWARN) $(FSTD) $(TDIR)/$(MULTISET)$(SUFFIX) -o $(NAME)
	@./$(NAME)
	@$(DIFF) $(DDIR)/my_multiset.txt $(DDIR)/real_multiset.txt
	@rm $(NAME)

$(DEQUE):	$(TDIR)/$(DEQUE)$(SUFFIX)
	@printf "$(DEQUE) --> "
	@$(CC) $(FWARN) $(FSTD) $(TDIR)/$(DEQUE)$(SUFFIX) -o $(NAME)
	@./$(NAME)
	@$(DIFF) $(DDIR)/my_deque.txt $(DDIR)/real_deque.txt
	@rm $(NAME)

$(QUEUE):	$(TDIR)/$(QUEUE)$(SUFFIX)
	@printf "$(QUEUE) --> "
	@$(CC) $(FWARN) $(FSTD) $(TDIR)/$(QUEUE)$(SUFFIX) -o $(NAME)
	@./$(NAME)
	@$(DIFF) $(DDIR)/my_queue.txt $(DDIR)/real_queue.txt
	@rm $(NAME)

zone: zone.cpp
	@$(CC) $(FWARN) $(FSTD) zone.cpp -o zone
	@./zone
