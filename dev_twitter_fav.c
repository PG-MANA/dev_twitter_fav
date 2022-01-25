#include <asm/current.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>

#define DRIVER_NAME "DEV_TWITTER_FAV"
#define DRIVER_MAJOR 62

static int open(struct inode *inode, struct file *file) { return 0; }

static int release(struct inode *inode, struct file *file) { return 0; }

static ssize_t read(struct file *file, char __user *buf, size_t count,
                    loff_t *f_pos) {
  char *argv[] = {"/usr/local/bin/fav_get"};
  char *envp[] = {"HOME=/", "TERM=linux",
                  "PATH=/sbin:/usr/sbin:/bin:/usr/bin:/usr/local/bin", NULL};
  char id_buffer[32];
  struct file *fp;
  ssize_t read_size;
  loff_t offset = 0;

  if (call_usermodehelper(argv[0], argv, envp, UMH_WAIT_PROC)) {
    printk(KERN_WARNING "Failed to get favorite id.\n");
    return 0;
  }

  fp = filp_open("/tmp/fav_id", O_RDONLY, 0);
  if (IS_ERR(fp)) {
    printk(KERN_WARNING "Failed to open favorite id file.\n");
    return 0;
  }

  read_size = kernel_read(fp, id_buffer, sizeof(id_buffer), &offset);
  if (read_size > count) {
    read_size = count;
  }

  if (copy_to_user(buf, id_buffer, read_size) != 0) {
    printk(KERN_WARNING "Failed to copy data.\n");
    read_size = 0;
  }

  filp_close(fp, NULL);
  return read_size;
}

static ssize_t dummy_write(struct file *file, const char __user *buf,
                           size_t count, loff_t *f_pos) {
  return 0;
}

struct file_operations fops = {
    .open = open,
    .release = release,
    .read = read,
    .write = dummy_write,
};

static int dev_twitter_fav_init(void) {
  printk(KERN_INFO "Starting dev_twitter_fav\n");
  register_chrdev(DRIVER_MAJOR, DRIVER_NAME, &fops);
  return 0;
}

static void dev_twitter_fav_exit(void) {
  printk(KERN_INFO "Removing dev_twitter_fav\n");
  unregister_chrdev(DRIVER_MAJOR, DRIVER_NAME);
}

module_init(dev_twitter_fav_init);
module_exit(dev_twitter_fav_exit);
MODULE_LICENSE("MIT");
