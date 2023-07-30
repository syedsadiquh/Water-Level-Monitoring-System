#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mraa.h>
#include <mraa/uart.h>
#include <sys/time.h>

#define trigPin 13
#define echoPin 14

#define uartPort "/dev/ttyS3"
#define uartBaudrate 38400

#define MQTT_SERVER_HOST "dev.rightech.io"
#define MQTT_CLIENT_ID "mqtt-syedsadiquh-vza3v6"
#define MQTT_TOPIC "SDI/GIFT/WATER-LEVEL"
#define MQTT_TOPIC_REQ "SDI/GIFT/WATER-REQ"

void wifi_init();
void mqtt_init();
void uart_init();
void gpio_init();
float distance();
void mqtt_pub_tank_stats(char *);
void mqtt_pub_tank_req(char *);

static mraa_gpio_context trig, echo;
static mraa_uart_context wifi;
static char buffer[100];

int main(int argc, char *argv[])
{
	// Initilize MRAA
	mraa_init();

	// Initialize Ultrasonic sensor (i.e. GPIO)
        gpio_init();

	//Initialize UART serial Communication
	uart_init();

	// Initialize Wifi
	wifi_init();

	sleep(1);
	
	// Initialize MQTT
	mqtt_init();
	
	// Then in loop do the following steps:-
	// run distance code repetitively and check for water level percentage
	// If the water is at 0%, 25%, 75% or 100%, Publish that on Rightech Cloud.
	
	float tankHeight = atoi(argv[1]);
	while(1)
	{
		float dist = distance();
		float percentage = ((tankHeight - dist) / tankHeight) * 100;

		char p[100];
		
		if(percentage > 23 && percentage < 27)
		{
			sprintf(p, "Tank Left = %.2f", percentage);
			printf("%s\n", p);
	                mqtt_pub_tank_stats(p);
			sprintf(p, "Order New Tank");
			mqtt_pub_tank_req(p);
			
		}
		else if(percentage > 48 && percentage < 52)
		{
			sprintf(p, "Tank Left = %.2f", percentage);
                        printf("%s\n", p);
                        mqtt_pub_tank_stats(p);
			sprintf(p, "Tank at 50 percent.");
			mqtt_pub_tank_req(p);
			
		}
		else if(percentage > 73 && percentage < 77)
		{
			sprintf(p, "Tank Left = %.2f", percentage);
                        printf("%s\n", p);
                        mqtt_pub_tank_stats(p);
			sprintf(p, "Tank at 75 percent.");
			mqtt_pub_tank_req(p);

		}
		else if(percentage > 97)
		{
			sprintf(p, "Tank Left = %.2f", percentage);
                        printf("%s\n", p);
                        mqtt_pub_tank_stats(p);
			sprintf(p, "Tank Full.");
			mqtt_pub_tank_req(p);
		}
		else if(percentage < 5 && percentage >= 0)
		{
			sprintf(p, "Tank Left = %.2f", percentage);
                        printf("%s\n", p);
                        mqtt_pub_tank_stats(p);
			sprintf(p, "New tank Req. (Urgent)");
			mqtt_pub_tank_req(p);	
		}
		else if(percentage < 0)
		{
			// Percentage is negative means Sensor data is error.
			sprintf(p, "Tank Left = ERROR!");
			printf("%s\n", p);
			mqtt_pub_tank_stats(p);
		}
		
	}

	mraa_deinit();

	return 0;
}

void uart_init()
{
	wifi = mraa_uart_init_raw(uartPort);
	mraa_uart_set_baudrate(wifi, uartBaudrate);
	mraa_uart_set_mode(wifi, 8, MRAA_UART_PARITY_NONE, 1);
	mraa_uart_set_flowcontrol(wifi, 0, 0);
}

void gpio_init()
{
	trig = mraa_gpio_init(trigPin);
	echo = mraa_gpio_init(echoPin);

	mraa_gpio_dir(trig, MRAA_GPIO_OUT);
	mraa_gpio_dir(echo, MRAA_GPIO_IN);
}

void wifi_init()
{
    sprintf(buffer, "CMD+FACRESET\r\n");
	mraa_uart_write(wifi, buffer, sizeof(buffer));
	
	sleep(2);
	
	sprintf(buffer, "CMD+UARTCONF=38400,8,1,0,0,1\r\n");
	mraa_uart_write(wifi, buffer, sizeof(buffer));

	sleep(1);

	sprintf(buffer, "CMD+WIFIMODE=1\r\n");
	mraa_uart_write(wifi, buffer, sizeof(buffer));
	sleep(1);

	// SSID, Password (here, the network is open)
	sprintf(buffer, "CMD+CONTOAP=realmesyed,\r\n");
	mraa_uart_write(wifi, buffer, sizeof(buffer));

	sleep(6);

	printf("Wifi code executed\n");
}

void mqtt_init()
{
	sprintf(buffer, "CMD+MQTTNETCFG=%s,1883\r\n", MQTT_SERVER_HOST);
        mraa_uart_write(wifi, buffer, sizeof(buffer));

	sleep(1);

	mraa_uart_read(wifi, buffer, sizeof(buffer));

	sprintf(buffer, "CMD+MQTTCONCFG=3,%s,,,,,,,,,\r\n", MQTT_CLIENT_ID);
	mraa_uart_write(wifi, buffer, sizeof(buffer));
	
	sleep(1);

	mraa_uart_read(wifi, buffer, sizeof(buffer));

	sprintf(buffer, "CMD+MQTTSTART=1\r\n");
        mraa_uart_write(wifi, buffer, sizeof(buffer));
	
	sleep(1);

	mraa_uart_read(wifi, buffer, sizeof(buffer));
	printf("Start: %s\n", buffer);

	sleep(1);

	sprintf(buffer, "CMD+MQTTSUB=%s\r\n", MQTT_TOPIC);
	mraa_uart_write(wifi, buffer, sizeof(buffer));

	sleep(1);

	mraa_uart_read(wifi, buffer, sizeof(buffer));

	sprintf(buffer, "CMD+MQTTSUB=%s\r\n", MQTT_TOPIC_REQ);
	mraa_uart_write(wifi, buffer, sizeof(buffer));

	sleep(1);

	mraa_uart_read(wifi, buffer, sizeof(buffer));
}

void mqtt_pub_tank_stats(char *pu)
{
	sprintf(buffer, "CMD+MQTTPUB=%s,%s\r\n", MQTT_TOPIC, pu);
        mraa_uart_write(wifi, buffer, sizeof(buffer));
	usleep(500000);
	mraa_uart_read(wifi, buffer, sizeof(buffer));
}

void mqtt_pub_tank_req(char *pu)
{
	sprintf(buffer, "CMD+MQTTPUB=%s,%s\r\n", MQTT_TOPIC_REQ, pu);
	mraa_uart_write(wifi, buffer, sizeof(buffer));
	usleep(500000);
	mraa_uart_read(wifi, buffer, sizeof(buffer));
}

float distance()
{	
	struct timeval startTime, stopTime;
	double time_taken;

	mraa_gpio_write(trig, 0);
	usleep(2);

	mraa_gpio_write(trig, 1);
	usleep(10);
	mraa_gpio_write(trig, 0);

	while(mraa_gpio_read(echo) == 0);

	gettimeofday(&startTime, NULL);

	while(mraa_gpio_read(echo) == 1);

	gettimeofday(&stopTime, NULL);

	time_taken = (double) (stopTime.tv_sec - startTime.tv_sec) * 1000000 + (stopTime.tv_usec - startTime.tv_usec);
	float dist = (time_taken * 0.0344)/2;

	printf("distance = %f\t\t Time Taken = %f\n", dist, time_taken);
	 
	usleep(300000);

	return dist;
}
