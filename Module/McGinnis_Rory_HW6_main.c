/**************************************************************
* Class:  CSC-415-1 Spring 2023
* Name: Rory McGinnis
* Student ID: 921337245
* GitHub UserID: rorymcginnis1
* Project: Assignment 6 – device driver
*
* File: Module/McGinnis_Rory_HW6_main.c
*
* Description:This assignment is create a device driver that
includes open, release, read, write, and an iotcl command, and
to implimentation this using an encrypt and decrypt option that
can be switched back and forth
*
**************************************************************/

#include <linux/module.h>
#define DEVICE_NAME "my_device"
#define BUF_SIZE 512

//initalizing variables
static int number;

static char device_buffer[BUF_SIZE] = {0}; 
static bool is_encryption_enabled = false;

int bytes_to_read;
int bytes_to_write;
int i;


//function that encrypts data in the buffer using ceaser cipher
static void encrypt_data(char *data, size_t size)
{
printk(KERN_INFO "My Device Driver: Device Encrypt\n");
    for (i = 0; i < size; i++)
    {
        if (data[i] >= 'a' && data[i] <= 'z')
        {
            data[i] = 'a' + ((data[i] - 'a' + 2) % 26);
        }
        else if (data[i] >= 'A' && data[i] <= 'Z')
        {
            data[i] = 'A' + ((data[i] - 'A' + 2) % 26);
        }
    }
}

//function that decrypts data in the buffer using ceaser cipher
static void decrypt_data(char *data, size_t size)
{
printk(KERN_INFO "My Device Driver: Device Decrpyt\n");
    for (i = 0; i < size; i++)
    {
        if (data[i] >= 'a' && data[i] <= 'z')
        {
            data[i] = 'a' + ((data[i] - 'a' - 2 + 26) % 26);
        }
        else if (data[i] >= 'A' && data[i] <= 'Z')
        {
            data[i] = 'A' + ((data[i] - 'A' - 2 + 26) % 26);
        }
    }
}
//open the device
static int device_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "My Device Driver: Device opened\n");
    return 0;
}
// read date into our buffer
static ssize_t device_read(struct file *file, char __user *buffer, 
size_t length, loff_t *offset)
{
	printk(KERN_INFO "My Device Driver: Device Read\n");

	//get the number of bytes we need to read
	if(length>BUF_SIZE){
		bytes_to_read=BUF_SIZE;
	}
	else{
		bytes_to_read=length;
	}
	// get encryption status and encrypt or decrypt
	if(is_encryption_enabled){
		encrypt_data(device_buffer, bytes_to_read);
	}
	else{
		decrypt_data(device_buffer, bytes_to_read);
	}
	//copy data
	if (copy_to_user(buffer, device_buffer, bytes_to_read)){
        	return -1; 
        }
    	printk(KERN_INFO "My Device Driver: string return value %s\n",
    	device_buffer);
    	return bytes_to_read;
}

//write data from buffer
static ssize_t device_write(struct file *file, const char __user *buffer,
size_t length, loff_t *offset)
{
	printk(KERN_INFO "My Device Driver: Device Write\n");
	
	//get number of bytes to write
	if(length>BUF_SIZE){
	bytes_to_write=BUF_SIZE;
	}
	else{
	bytes_to_write=length;
	}

	//copy data
    	if (copy_from_user(device_buffer , buffer, bytes_to_write)){
        	return -1; }
        
    	printk(KERN_INFO "My Device Driver: string start value %s\n",
    	device_buffer);
    	return bytes_to_write;
}

//ioctl operation, switches is_encryption_enabled
static long device_ioctl(struct file *file, unsigned int ioctl_num, 
unsigned long ioctl_param){
    printk(KERN_INFO "My Device Driver: Device changing encryption\n");
    is_encryption_enabled = !is_encryption_enabled;
    printk(KERN_INFO "My Device Driver: Device encryption is %s\n", 
    is_encryption_enabled ? "encrypt" : "decrypt");
    if(is_encryption_enabled){
    
    return 1;}

    return 0;
}
// file operations for hte device driver
static struct file_operations fops = {
    .open = device_open,
    .read = device_read,
    .write = device_write,
    .unlocked_ioctl = device_ioctl,
};

//initalize the device
static int __init my_device_init(void)
{
    memset(device_buffer, 0, BUF_SIZE);
    number = register_chrdev(0, DEVICE_NAME, &fops);
    if (number < 0) {
        printk(KERN_ALERT "Failed to register the device \
        driver with error code \n");
        return number;
    }
    printk(KERN_INFO "My Device Drivers: Registered \
     successfully with number %d\n", number);
    return 0;
}
// exit the device
static void __exit my_device_exit(void)
{
    unregister_chrdev(number, DEVICE_NAME);
    printk(KERN_INFO "My Device Drivers: Unregistered\n");
}

//specify initialization and exit, gets rid of warrnings
module_init(my_device_init);
module_exit(my_device_exit);

MODULE_LICENSE("GPL");

