#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/rwlock.h>
#include <linux/string.h>
#include <linux/version.h>

#define DEVICE_NAME "hellodev"
#define PROC_NAME "helloproc"
#define KOBJ_NAME "hellokobj"
#define STRING_LEN 64

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
#define HAVE_PROC_OPS
#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bytbager");
MODULE_DESCRIPTION("A simple module");

static int major;
static rwlock_t lock;
static struct class *cls;
static char hello_string[STRING_LEN] = "Hello!\n\0";
static struct proc_dir_entry *proc_file;

enum {
    DEV_NOT_USED = 0,
    DEV_OPENED = 1,
};

static ssize_t hello_read(struct file *fd, char __user *buff, size_t size, loff_t *off) {
    size_t rc;

    read_lock(&lock);
    rc = simple_read_from_buffer(buff, size, off, hello_string, STRING_LEN);
    read_unlock(&lock);

    return rc;
}

static ssize_t hello_write(struct file *fd, const char __user *buff, size_t size, loff_t *off) {
    size_t rc;

    if (size > STRING_LEN) return -EINVAL;

    write_lock(&lock);
    rc = simple_write_to_buffer(hello_string, STRING_LEN, off, buff, size);
    write_unlock(&lock);

    return rc;
}

static ssize_t hello_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
    size_t rc;

    read_lock(&lock);
    rc = sprintf(buf, "%s", hello_string);
    read_unlock(&lock);

    return rc;
}

static ssize_t hello_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
    size_t rc;

    write_lock(&lock);
    memcpy(hello_string, buf, count);
    rc = strlen(buf);
    write_unlock(&lock);

    return rc;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = hello_read,
    .write = hello_write
};

#ifdef HAVE_PROC_OPS
static struct proc_ops pops = {
    .proc_read = hello_read,
    .proc_write = hello_write
};
#else
static struct file_operations pops = {
    .read = hello_read,
    .write = hello_write
};
#endif

static struct kobj_attribute hello_attr =
    __ATTR(hello_string, 0664, hello_show, hello_store);

static struct attribute *attrs[] = {
    &hello_attr.attr,
    NULL,
};

static struct attribute_group group = {
    .attrs = attrs,
};

static struct kobject *hello_kobj;

static int __init hello_module_init(void) {
    int retval;
    
    pr_info("Hello, World!\n");
    
    rwlock_init(&lock);

    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) return major;
    pr_info("I was assigned a new major number: %d\n", major);
    
    #if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
        cls = class_create(DEVICE_NAME);
    #else
        cls = class_create(THIS_MODULE, DEVICE_NAME);
    #endif
    device_create(cls, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    pr_info("Device created: /dev/%s\n", DEVICE_NAME);

    proc_file = proc_create(PROC_NAME, 0666, NULL, &pops);
    if (proc_file == NULL) {
        proc_remove(proc_file);
        pr_info("proc_create error!\n");
        return -ENOMEM;
    }
    pr_info("Proc created: /proc/%s\n", PROC_NAME);

    hello_kobj = kobject_create_and_add(KOBJ_NAME, kernel_kobj);
    if (!hello_kobj)
        return -ENOMEM;

    retval = sysfs_create_group(hello_kobj, &group);
    if (retval) {
        kobject_put(hello_kobj);
        return retval;
    }

    return 0;
}

static void __exit hello_module_exit(void) {
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
    unregister_chrdev(major, DEVICE_NAME);
    
    proc_remove(proc_file);

    kobject_put(hello_kobj);

    pr_info("Goodbye, World!\n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);