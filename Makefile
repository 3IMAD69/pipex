


all : 
	@cc main.c -g -fsanitize=address && ./a.out input.txt "ls -l" "wc -l" output.txt