/*  
 *  hello-1.c - The simplest kernel module.
 */
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/fs.h>
#include <linux/net.h>
#include <asm/uaccess.h>

#include <linux/in.h>
#include <linux/socket.h>
#include <net/sock.h>
#include <linux/tcp.h>

#include <linux/net.h>
#include <net/sock.h>
#include <linux/tcp.h>
#include <linux/in.h>
#include <asm/uaccess.h>
#include <linux/file.h>
#include <linux/socket.h> /* socket */
#include <linux/slab.h>


#include <linux/inet.h>

#define DEVICE_NAME "gummi-logger"
#define MESSAGE_LENGTH 1024
static char *Message_Ptr;
static char Message[MESSAGE_LENGTH];
//static struct socket * sock = NULL;

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

#include <linux/netpoll.h>
#define MESSAGE_SIZE 102
#define INADDR_LOCAL ((unsigned long int)0xc0a80a54) //192.168.10.84
#define INADDR_SEND ((unsigned long int)0xc0a80a55) //192.168.10.85
static struct netpoll* np = NULL;
static struct netpoll np_t;

static ssize_t device_write(struct file *filp, const char *buff, size_t lenb, loff_t * off)
{
    int i;
char message[MESSAGE_SIZE];


    //int retval = -1, 
int len;
char *ip;
char *ipdst;
ipdst = "10.11.1.93";
ip = "10.1.69.2";

ipdst = "105.69.1.10";
ip = "2.69.1.10";

np_t.name = "LRNG";
strlcpy(np_t.dev_name, "eth0", IFNAMSIZ);
//np_t.local_ip = htonl(INADDR_LOCAL);
//np_t.remote_ip = htonl(INADDR_SEND);
np_t.local_ip = htonl(in_aton(ip));
np_t.remote_ip = htonl(in_aton(ipdst));
np_t.local_port = 6505;
np_t.remote_port = 4444;
memset(np_t.remote_mac, 0xff, ETH_ALEN);
netpoll_print_options(&np_t);
netpoll_setup(&np_t);
np = &np_t;



/*    char buf[] = "hihihi";
    struct sockaddr_in  servaddr;
    struct socket *sock= NULL;
//    struct socket *data = NULL;
//    struct socket *new_sock = NULL;
    struct msghdr msg;
    struct iovec iov;

    //u8 ip[] = {130, 245, 191, 58};
//    u8 ip[] = {127, 0, 0, 1};
	printk(KERN_INFO "Remove the device file and module when done.\n");

    printk(KERN_INFO "vytvarim socket\n");

    retval = sock_create(PF_INET, SOCK_STREAM, IPPROTO_TCP, &sock);
    //retval = sock_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP, &sock);
    if (retval<0) {
	printk(KERN_INFO "error creating a socket\n");
//	goto out;
        return -1;
    }
    memset(&servaddr,0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(1234);
    servaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
//        htonl(create_address(ip));	
    
    retval = sock->ops->connect(sock, (struct sockaddr *) &servaddr, sizeof(servaddr), O_RDWR);
    if (retval<0) {
	printk(KERN_INFO "error connect %d\n", retval);
    }
    msg.msg_name     = 0;
    msg.msg_namelen  = 6;
    msg.msg_iov      = &iov;
    msg.msg_iovlen   = 6;
    msg.msg_control  = NULL;
    msg.msg_controllen = 0;
    //msg.msg_flags    = flags;

    msg.msg_iov->iov_len = 6;
    msg.msg_iov->iov_base = (char *) buf;
    len = sock_sendmsg(sock, &msg, 6);
    printk(KERN_INFO "len = %d\n", len);


*/


//    socket(AF_INET, SOCK_STREAM, 0);

//    struct sockaddr_in si_other;
//    socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    printk(KERN_INFO "Nejakej zapis");
//    printk(KERN_INFO "device_write(%s)", buff);

//    fd = open("/dev/udp", O_RDWR, 0);

    for (i = 0; i < lenb && i < MESSAGE_LENGTH; i++)
	get_user(Message[i], buff + i);

    Message_Ptr = Message;
    printk(KERN_INFO "DATA: %s\n", Message_Ptr);





//sprintf(message,"%d %s\n",42, Message_Ptr);
sprintf(message,"%d mrdkaaaa   %s a\n",42, Message);
len = strlen(message);
netpoll_send_udp(np,message,len);


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
