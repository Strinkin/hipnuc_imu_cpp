//serial_imu.cpp
#include <iostream>
#include <stdio.h>

#ifdef __cplusplus 
extern "C"{
#endif

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <poll.h>

#include "hipnuc.h"

#define GRA_ACC      (9.8)
#define DEG_TO_RAD   (0.01745329)
#define BUF_SIZE     1024


#define ACC_FACTOR   (0.0048828)
#define GYR_FACTOR	 (0.001)
#define EUL_FACTOR	 (0.001)
#define QUA_FACTOR   (0.0001)



#ifdef __cplusplus
}
#endif


int n = 0;
int rev = 0;
struct pollfd p;
int rpoll;

void read_imu(int fd)
{
	static hipnuc_raw_t raw;
	static uint8_t buf[BUF_SIZE];
	// rpoll = poll(&p, 1, 5); // 监听1个串口，超时时间为5ms

	// if(rpoll == 0)
	// 	return ;
	n = read(fd, buf, sizeof(buf));

	if(n > 0)
	{
		for(int i = 0; i < n; i++)
		{
			rev = hipnuc_input(&raw, buf[i]); // 处理完一个数据包后，rev置1
			if(rev)
			{
				std::cout << raw.hi91.yaw << std::endl;
				rev = 0;
			}

		}
	}
}

int open_port(std::string port_device, int baud)
{
	const char* port_device1 = port_device.c_str();
	int fd = open(port_device1, O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (fd == -1)
	{
		perror("open_port: Unable to open SerialPort");
		puts("Please check the usb port name!!!");
		exit(0);
	}

	if(fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		printf("fcntl failed\n");
	else
		fcntl(fd, F_SETFL,  O_NONBLOCK);
  
	if(isatty(STDIN_FILENO) == 0)
		printf("standard input is not a terminal device\n");
	else 
		printf("isatty success!\n");

	struct termios options;
	tcgetattr(fd, &options);
	
	switch(baud)
	{
		case 115200:
			cfsetispeed(&options, B115200);
			cfsetospeed(&options, B115200);
		break;
		case 460800:
			cfsetispeed(&options, B460800);
			cfsetospeed(&options, B460800);
		break;
		case 921600:
			cfsetispeed(&options, B921600);
			cfsetospeed(&options, B921600);
		break;
		default:
		printf("SERIAL PORT BAUD RATE ERROR");
	}


	options.c_cflag &= ~PARENB; 
	options.c_cflag &= ~CSTOPB; 
	options.c_cflag &= ~CSIZE;  
	options.c_cflag |= HUPCL;   
	options.c_cflag |= CS8;     
	options.c_cflag &= ~CRTSCTS; 
	options.c_cflag |= CREAD | CLOCAL; 

	options.c_iflag &= ~(IXON | IXOFF | IXANY); 
	options.c_iflag &= ~(INLCR|ICRNL); 

	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	options.c_oflag &= ~OPOST; 
	options.c_oflag &= ~(ONLCR|OCRNL); 

	options.c_cc[VMIN] = 0;  
	options.c_cc[VTIME] = 0; 

	tcsetattr(fd, TCSANOW, &options);
	return (fd);
}

int main()
{

	int baud_rate = 115200;
	std::string imu_serial = "/dev/HIPNUC_IMU";
	int fd = 0;

	fd = open_port(imu_serial, baud_rate);
	
	p.fd = fd;
	p.events = POLLIN;

	while(1)
	{
		rpoll = poll(&p, 1, 5); // 监听1个串口，超时时间为5ms
		if(rpoll == 0) { continue; }
		read_imu(fd);
	}
	
	return 0;
}


