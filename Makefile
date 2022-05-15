all:
	@make --no-print-directory -s build



build:
	bash .install.sh

clean:
	rm -f main
