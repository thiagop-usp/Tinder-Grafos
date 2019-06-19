all:
	@echo "\e[35mRednit compilado com sucesso! Divirta-se!" 
	@gcc grafo.c leitor.c main.c -o trabs -Wall -pedantic -Wextra

love:
	@./trabs
