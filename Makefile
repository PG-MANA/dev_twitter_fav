obj-m := dev_twitter_fav.o

RM := rm
CP := cp
CHMOD := chmod
MKNOD := mknod
INSMOD := insmod
RMMOD := rmmod

default:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

load:
	$(INSMOD) dev_twitter_fav.ko
	$(MKNOD) /dev/twitter_fav c 62 1
	$(CHMOD) 444 /dev/twitter_fav
	$(CP) fav_get /usr/local/bin/
	$(CHMOD) +x /usr/local/bin/fav_get
	$(CP) key /etc/dev_twitter_fav
unload:
	$(RMMOD) dev_twitter_fav.ko
	$(RM) -f /dev/twitter_fav
	$(RM) -f /usr/local/fav_get
	$(RM) -f /tmp/fav_id
	$(RM) -f /etc/dev_twitter_fav
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
