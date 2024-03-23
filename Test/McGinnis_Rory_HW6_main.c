/**************************************************************
* Class:  CSC-415-1 Spring 2023
* Name: Rory McGinnis
* Student ID: 921337245
* GitHub UserID: rorymcginnis1
* Project: Assignment 6 – device driver
*
* File: Test/McGinnis_Rory_HW6_main.c
*
* Description:This assignment is create a device driver that
includes open, release, read, write, and an iotcl command, and
to implimentation this using an encrypt and decrypt option that
can be switched back and forth
*
**************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#define DEVICE_FILE_PATH "/dev/my_device"

int main(int argc, char *argv[])

{	
	//make sure we have the right number of arguments
	if (argc != 3) {
	        return 1;
	}
	//open the device
    	int fd = open(DEVICE_FILE_PATH, O_RDWR);
    	
    	//get command line arguments
    	char *strings =argv[1];
    
  	char *enc = argv[2];
    	
    	//take encryption data based on command line
    	//if not e or d then the encryption 
    	//stays as it was before
    	if(*enc=='e'){
    		int ret = ioctl(fd,  1);
    		if(ret ==1){
    			int ret = ioctl(fd,  1);
    		}
    	}
    	else if(*enc=='d'){
        	int ret = ioctl(fd,  1);
    		if(ret ==0){
    			int ret = ioctl(fd,  1);
    		}
    	}

    
    	printf("your input is %s\n",strings);
	
	//check for error
    	if (fd < 0)
    	{
       		perror("Error opening device file");
        	return -1;
    	}


	//copy input into string for device
	char original_message[512];
    	strncpy(original_message, argv[1], sizeof(original_message));
    	size_t message_length = strlen(original_message);
    

    	//write to the device
    	write(fd, original_message, message_length);
	
	//read back from the device
    	char read_buffer[message_length];
    	int bytes_read=read(fd, read_buffer, message_length);
    	read_buffer[bytes_read] = '\0';

	//print the information returned
        printf("the data you entered is now read as: %s\n", read_buffer);

 	//close the device
    	close(fd);
    	return 0;
}
