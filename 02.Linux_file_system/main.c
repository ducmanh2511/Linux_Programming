#include <fcntl.h>     
#include <unistd.h>     
#include <sys/types.h>  
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
char buff[MAX_SIZE];
int main(int argc, char*argv[]){
	if(argc !=5){
		fprintf(stderr,"Cach dung: %s <file> <offset> <number-bytes> <SET|CUR|END>\n",argv[0]);
		return EXIT_FAILURE;
	}
	int fd;
	fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("open");
		return EXIT_FAILURE;
	}
	int offset = atoi(argv[2]);
	int number_bytes = atoi(argv[3]);
	if(number_bytes >= MAX_SIZE || number_bytes < 0){
		fprintf(stderr,"So luong byte khong hop le!\n");
		return EXIT_FAILURE;
	}
	int whence;
	if(strcmp("SET",argv[4]) == 0){
		whence = SEEK_SET;
	}
	else if(strcmp("CUR",argv[4])==0){
		whence = SEEK_CUR;
	}
	else if(strcmp("END", argv[4])==0){
		whence = SEEK_END;
	}
	else{
		fprintf(stderr, "Moc phai la <SET|CUR|END>\n");
		return EXIT_FAILURE;
	}
	lseek(fd, offset, whence);
        ssize_t byte_read = read(fd,buff, number_bytes);
	if(byte_read == -1){
		perror("read");
	}
	for(int i = 0;i<byte_read;i++){
		printf("%c",buff[i]);
	}
	

	


}
