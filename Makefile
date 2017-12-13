FLAGS=-std=c++11
all:obj.cc
	clang++ $(FLAGS) obj.cc -o obj 
