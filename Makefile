dev: main.c src/config_parser.c
	gcc -Werror main.c src/config_parser.c src/usage.c src/helpers.c src/analyze_all.c src/frame.c src/packet.c src/helpers2.c src/tcp.c src/icmp.c -lpcap -oanalyze