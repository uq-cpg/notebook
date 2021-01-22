BASIC := -std=c++11 -Wall -Wextra -Wshadow -g
VERBOSE := -fsanitize=address -fsanitize=undefined -DLOCAL -D_GLIBCXX_DEBUG

main: main.cc
	g++ $(BASIC) $(VERBOSE) $< -o $@