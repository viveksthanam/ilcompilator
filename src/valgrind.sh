#options avancées pour une analyse mémoire (Valgrind) du comportement du compilateur

valgrind -v --show-reachable=yes --tool=memcheck --leak-check=full --leak-resolution=high $1


