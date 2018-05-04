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

	if (argc < 2) {
		printf("tc_vcam -s ---Set the tc358743 config\n");
		printf("tc_vcam -c ---Stop the tc358743\n");

		return -1;
	}

	while ((ch = getopt(argc, argv, "sc")) != -1)
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
			default:
				printf("tc_vcam -s ---Set the tc358743 config\n");
				printf("tc_vcam -c ---Stop the tc358743\n");
				return 0;
		}
	}

	i2c_fd = open("/dev/i2c-0", O_RDWR);
	if (i2c_fd < 0) {
		printf("Can't open i2c device, error = %d\n", i2c_fd);
		return -1;
	}

	if (config == 1)
		start_camera_streaming(i2c_fd);
	else if (config == 0)
		stop_camera_streaming(i2c_fd);

	close(i2c_fd);

	return 0;
}
