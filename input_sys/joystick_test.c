/*
  * 参考内核文档 joystick-api.txt
  * author: ningci dev date: 2017-06-02 18:00
  */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct js_event {        
	unsigned int   time;      /* event timestamp in milliseconds */        
	unsigned short value;     /* value */        
	unsigned char  type;      /* event type */        
	unsigned char  number;    /* axis/button number */    
};
 
int main(int argc, char **argv)
{
	struct js_event e;
	int fd = open("/dev/input/js0", O_RDONLY);
	while(1)
	{
		if(0 < read (fd, &e, sizeof(e)))
		{
			printf("value:0x%x type:0x%x number:0x%x \n", e.value, e.type, e.number);
		}
	}
	close(fd);
	return 0;
}
