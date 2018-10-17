dev: main.c src/config_parser.c
	gcc -Werror main.c src/config_parser.c src/usage.c src/helpers.c src/analyze_all.c -lpcap -oanalyze