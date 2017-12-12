1) compile --> gcc sorter_server.c -o server
2) execute server --> ./server -c movie_color -h localhost -p 9898 -d <optional> -o <optional>
	where -d is input directory and is optional and -o is output directory and also optional.


3) compile --> gcc sorter_client.c -o client
4) execute client --> ./client 9898

