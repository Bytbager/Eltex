#include <linux/atomic.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/rwlock.h>
#include <linux/version.h>

#define DEVICE_NAME "hellodev"
#define STRING_LEN 64

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bytbager");
MODULE_DESCRIPTION("A simple module");

static int major;
static rwlock_t lock;
static struct class *cls;
static char hello_string[STRING_LEN] = "Hello!\n\0";

enum {
    DEV_NOT_USED = 0,
    DEV_OPENED = 1,
};

static atomic_t already_open = ATOMIC_INIT(DEV_NOT_USED);

ssize_t hello_dev_read(struct file *fd, char __user *buff, size_t size, loff_t *off) {
    size_t rc;

    read_lock(&lock);
    rc = simple_read_from_buffer(buff, size, off, hello_string, STRING_LEN);
    read_unlock(&lock);

    return rc;
}

ssize_t hello_dev_write(struct file *fd, const char __user *buff, size_t size, loff_t *off) {
    size_t rc;

    if (size > STRING_LEN) return -EINVAL;

    write_lock(&lock);
    rc = simple_write_to_buffer(hello_string, STRING_LEN, off, buff, size);
    write_unlock(&lock);

    return rc;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = hello_dev_read,
    .write = hello_dev_write
};

static int __init hello_module_init(void) {
    pr_info("Hello, World!\n");
    
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) return major;
    pr_info("I was assigned a new major number: %d\n", major);
    
    rwlock_init(&lock);
    
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
        cls = class_create(DEVICE_NAME);
    #else
        cls = class_create(THIS_MODULE, DEVICE_NAME);
    #endif
    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    
    pr_info("Device created: /dev/%s\n", DEVICE_NAME);

    return 0;
}

static void __exit hello_module_exit(void) {
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
    unregister_chrdev(major, DEVICE_NAME);
    
    pr_info("Goodbye, World!\n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);