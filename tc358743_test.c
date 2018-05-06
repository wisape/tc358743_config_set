#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include "tc358743_init.h"

int main(int argc, char * argv[])
{
	int i2c_fd;
	int config = -1;
	int ch;
	char *dev_name = "/dev/i2c-0";

	if (argc < 2) {
		printf("tc_vcam -s -d /dev/i2c-0 ---Set the tc358743 config\n");
		printf("tc_vcam -c -d /dev/i2c-0 ---Stop the tc358743\n");

		return -1;
	}

	while ((ch = getopt(argc, argv, "scd:")) != -1)
	{
		switch (ch) 
		{
			case 's':
				printf("!!!To Set config tc358743!!\n");
				config = 1;

				break;
			case 'c':
				printf("!!!To Stop tc358743!!\n");
				config = 0;

				break;
			case 'd':
				dev_name = optarg;
				break;
			default:
				printf("tc_vcam -s -d /dev/i2c-0 ---Set the tc358743 config\n");
				printf("tc_vcam -c -d /dev/i2c-0 ---Stop the tc358743\n");
				return 0;
		}
	}

	i2c_fd = open(dev_name, O_RDWR);
	if (i2c_fd < 0) {
		printf("Can't open %s, error = %d\n", dev_name, i2c_fd);
		return -1;
	}

	if (config == 1)
		start_camera_streaming(i2c_fd);
	else if (config == 0)
		stop_camera_streaming(i2c_fd);

	close(i2c_fd);

	return 0;
}
