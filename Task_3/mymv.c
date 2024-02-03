#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
 
#define RET_STATUS 0
    
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
     
//int main(int argc, char** argv)
int main(int argc, char *argv[]) 
    {  int fd_dest, fd, num_read, num_write;
    
	// fd_dest for write file descriptor 
	// file descriptor for read file
	// num_read stores return value from read 
	// num_write stores retutn value from write
    unsigned char buf[100];
    
	// buffer stores values to write
	if (argc != 3)
	 {
	
	    // 1 >> command name
	    // 2 >> source file name
	    // 3 >> destination file name
	    printf("Usage: %s source_file_name destination_file_name\n",
		   argv[0]);
	
	    // handles wronge usage
	    return -1;
	}
    fd_dest = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0644);
    
	// stores open file value file descriptor
	// if it doesn't exist it will create it with O_CREAT
	// O_CREAT
	// if the specified file does not exist, it may op‐tionally (if O_CREAT is specified in flags) be created by open().
	// If the file already exists and is a regular file and the access mode allows writing
	// O_TRUNC
	// (i.e., is O_RDWR or O_WRONLY) it will be  truncated to length 0.  
	//we give it argument number 0644 mode
	fd = open(argv[1], O_RDONLY);
    
	// fd for read file
	// return the new file descriptor (a nonnegative integer), or -1 if an error occurred
	if (fd < 0) {
	printf(">> Could not open the file\n");
	return -1;
    }
    printf(">> the file opend with fd = %d\n", fd);
      while ((num_read = read(fd, buf, 100)) != 0) {
	
	    // while there is something to read in read file read function will return >-1
	    // so it will remain true till file ends
	    if (num_read < 0) {
	    
		//On  success,  the  number  of bytes read is returned
		// On  error,  -1  is  returned
		printf(">> Could not read from the file\n");
	    return -1;
	}
	printf(">> I read %d bytes\n", num_read);

	num_write = write(fd_dest, buf, num_read);
	if (num_write < 0) {
	    
		//On  success,  the  number of bytes written is returned.  On error, -1 is returned
		printf(">> Could not write to file\n");
	    return -1;
	}
	printf("\n>> I wrote %d bytes\n", num_write);
    }
     close(fd);
    
	// closes read file
	close(fd_dest);
    
	// closes write file
	if (unlink(argv[1]) == 0) {
	printf("file deleted\n");
    }

    else {
	printf("error in deleting\n");
    }

    return RET_STATUS;
}


