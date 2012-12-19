/*  
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/fs.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "gummi-logger"
#define MESSAGE_LENGTH 1024
static char *Message_Ptr;
static char Message[MESSAGE_LENGTH];


int Major;
int init_module(void);
void cleanup_module(void);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
//	.read = device_read,
	.write = device_write //,
//	.open = device_open,
//	.release = device_release
};

int init_module(void)
{

        Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", Major);
	  return Major;
	}

	printk(KERN_INFO "I was assigned major number %d. To talk to\n", Major);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/%s c %d 0'.\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");

	return 0;
}

void cleanup_module(void)
{
	/* 
	 * Unregister the device 
	 */
//	int reta = 
	unregister_chrdev(Major, DEVICE_NAME);
	//if (ret < 0)
	//	printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);	

}

static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
    int i;
//    int fd;

    printk(KERN_INFO "Nejakej zapis");
//    printk(KERN_INFO "device_write(%s)", buff);

//    fd = open("/dev/udp", O_RDWR, 0);

    for (i = 0; i < len && i < MESSAGE_LENGTH; i++)
	get_user(Message[i], buff + i);

    Message_Ptr = Message;
    printk(KERN_INFO "DATA: %s\n", Message_Ptr);
    /* 
     * Again, return the number of input characters used 
     */
    return i;


//    return len;
/*
char *tmp;
char *pathname;
struct path path;

printk(KERN_ALERT "Logger write\n");


path = filp->f_path;
path_get(&filp->f_path);

tmp = (char *)__get_free_page(GFP_TEMPORARY);

if (!tmp) {
    path_put(&path);
    return -ENOMEM;
}

pathname = d_path(&path, tmp, PAGE_SIZE);
path_put(&path);

if (IS_ERR(pathname)) {
    free_page((unsigned long)tmp);
    return PTR_ERR(pathname);
}

	printk(KERN_ALERT "data: %s", pathname);

free_page((unsigned long)tmp);



	return 0;  */
}
