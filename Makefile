dev: main.c src/config_parser.c
	gcc -Werror main.c src/config_parser.c src/usage.c -lpcap -oanalyze