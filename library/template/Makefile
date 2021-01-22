BASIC := -std=c++11 -Wall -Wextra -Wshadow -g -DLOCAL
VERBOSE := -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

main: main.cc
	g++ $(BASIC) $(VERBOSE) $< -o $@