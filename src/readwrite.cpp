#include<sys/unistd.h>
#include<fcntl.h>
#include<iostream>
using namespace std;

int main()
{
	char buffer[11] = {0,};
	
	//print to screen
	write(1, "enter some", 10);
	//read from console
	read(0, buffer, 10);

	//write to file
	int fd = open("b.txt", O_CREAT | O_WRONLY);
	write(fd, buffer, 10);
	close(fd);

	//read from file
	fd = open("b.txt", O_RDONLY);
	read(fd, buffer, 10);
	close(fd);
	write(1, buffer, 10);

	//inter process communication
	int pd[2];
	pipe(pd);
	if(fork()) {
		write(pd[1], "from other", 10);
	} else {
		read(pd[0], buffer, 10);
		write(1, buffer, 10);
	}

}
