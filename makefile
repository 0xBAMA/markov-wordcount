all:
	g++ -o salad salad.cc
	@echo "call with ./salad <corpus path> <number of words>"
	@echo
	g++ -o nonword nonword.cc
	@echo "call with ./nonword <corpus path> <number of words>"
	@echo
