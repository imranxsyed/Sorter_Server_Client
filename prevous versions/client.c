#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>




int main(int argc, char * argv[]){


	if (argc < 3){

		printf("INVALID PARAMETERS\n");
		exit(0);

	}

	int sockfd , clientfd, n, portno;
	struct hostent* server;
	char buffer[255];

	struct sockaddr_in serv_add , client_add;
	socklen_t clilen;

	//making a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd <0){

		printf("error making a socekt\n");
		exit(0);
	}

	
	portno = atoi(argv[2]);

	server = gethostbyname(argv[1]);

	if (server == NULL){


		printf("wront IP Address\n");
		exit(0);
	}


	bzero((char *) &serv_add, sizeof(serv_add));
	serv_add.sin_family = AF_INET;
	bcopy (server->h_addr , (char *) &serv_add.sin_addr.s_addr , server-> h_length);
	serv_add.sin_port = htons(portno);

	if (connect (sockfd , (struct sockaddr *) &serv_add, sizeof(serv_add)) < 0){

		printf("connection error\n");
		exit(0);

	}

	printf("connection successful\n");

	



	FILE * file = fopen("dataset2_a.csv", "r");
	if (file == NULL){


		printf("erorr opening the file:\n");
		exit(0);
	}

	char line[1000];

	fgets(line,1000,file);//getting the header

	fgets(line,1000,file); //getting the first line



	 while (strlen(line)>1){

		printf("%s\n" , line);
		write(sockfd , line,strlen(line));
		
		read(sockfd , line , 5);

		bzero(line ,1000);
		fgets(line,1000,file);

	}


		bzero(line ,1000);
		write(sockfd , "done",4);

		read(sockfd , line , 5);
		bzero(line ,1000);

		bzero(line ,1000);
		write(sockfd, "movie_title", 11);
		fclose(file);
		close(sockfd);
		
	
	/*while (1){

	
		printf("you message?\n");
		bzero(buffer , 255);


		fgets(buffer , 255, stdin);
		n = write(sockfd , buffer,strlen(buffer));
		printf("ME:  %s\n" , buffer);

		

		
		//bzero(buffer , 255);
		//n = read(sockfd , buffer , 255);
		//printf("server: %s\n", buffer);

		
		if (strncmp("done", buffer, 4) ==0){

			break;

		}



	}*/

	

	printf("connection closed");
	return 0;


}







