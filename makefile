vector:
	g++ -o programa main.cpp funkcijos.cpp funkcijos.h && ./programa
list:
	g++ -o programa main_list.cpp funkcijos.cpp funkcijos.h && ./programa
deque:
	g++ -o programa main_deque.cpp funkcijos.cpp funkcijos.h && ./programa
clean:
	rm *.txt *.exe
