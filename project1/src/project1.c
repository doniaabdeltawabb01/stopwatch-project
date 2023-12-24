/*
 ============================================================================
 Name        : project1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
//prototype
void speed_data(char traffic_light);
void AC_temp(float room_temp);
void control_temp(float engine_temp);
void menu(char menu_choice);
void display(void);

//globle sturct
typedef struct {
	char set_menu,color,ask_user,speed;
	float tempRoom,tempEngine;
}engine;
//define the struct variable
engine var;
//global enum
enum state{
	off,on,quit
};
enum state AC=off,controller=off,motor=off;

int main(void) {
	//variables
	while(motor==off){
		printf("If you want to turn on the vehicle engine,choose 'a'\n");
		printf("If you want to turn off the vehicle engine,choose 'b'\n");
		printf("If you want to quit the system,choose 'c'\n");
		fflush(stdout);
		scanf(" %c",&var.ask_user);
		switch(var.ask_user){
		//Turn on the vehicle engine
		case 'a':
			motor=on;
			while(motor==on){
				//menu print
				printf("Sensors set menu\n");
				printf("to turn off the engine,enter 'a'\n");
				printf("to set  the traffic light color,enter 'b'\n");
				printf("to set the room temperature,enter 'c'\n");
				printf("to set the engine temperature,enter 'd'\n");
				fflush(stdout);
				scanf(" %c",&var.set_menu);
				//sensors set menu
				menu(var.set_menu);

			//Display
			display();

			}//end of while engine is on

//end break of case 1
		break;
		//Turn off the vehicle engine
		case 'b':
			motor=off;
		break;
		//Quit the system
		case 'c':
			motor=quit;
		break;
		default:
			printf("Error\n");

		}
	}

	return 0;
}
//menu
void menu(char menu_choice){
	// Turn off the engine
	if(menu_choice=='a'){
		motor=off;
	}
	//Set the traffic light color.
	else if(menu_choice=='b'){
		printf("enter traffic light color: ");
		fflush(stdout);
		scanf(" %c",&var.color);
		speed_data(var.color);

	}
	//Set the room temperature
	else if(menu_choice=='c'){

		printf("Enter the room temperature: ");
		fflush(stdout);
		scanf("%f",&var.tempRoom);
		AC_temp(var.tempRoom);

	}
	//Set the engine temperature
	else if(menu_choice=='d'){

		printf("Enter the engine temperature: ");
		fflush(stdout);
		scanf("%f",&var.tempEngine);
		control_temp(var.tempEngine);
	}
	//default
	else{printf("Error\n");}
	//speed checker
	//speed=30
	if(var.speed==30){
		//controller and engine temp at speed 30
		controller=on;
		var.tempEngine=(var.tempEngine)*(5.0/4.0)+1;
		//AC and room temp at speed 30
		AC=on;
		var.tempRoom=(var.tempRoom)*(5.0/4.0)+1;
	}
}

//traffic light data
void speed_data(char traffic_light){
	if (traffic_light=='G'){
		var.speed=100;
	}
	else if(traffic_light=='O'){
		var.speed=30;
	}
	else if(traffic_light=='R'){
			var.speed=0;
		}
	else{var.speed=-1;}

}
//Based on room temperature data
void AC_temp(float room_temp){

	if(room_temp<10||room_temp>30){
		var.tempRoom=20;
		AC=on;
	}
	else {AC=off;}
}
//Based on engine temperature data
void control_temp(float engine_temp){
	if(engine_temp<100||engine_temp>150){
			var.tempEngine=125;
			controller=on;
		}
	else{controller=off;}
}
void display(void){
	//Engine state:
	if(motor==off){
		printf("Engine state:off\n");
	}
	else{
		printf("Engine state:On\n");
	}
	//AC:
	if(AC==on){
		printf("AC:On\n");
	}
	else{
		printf("AC:Off\n");
	}
	//Vehicle Speed.
	printf("Vehicle Speed= %d km/h\n",var.speed);
	//Room Temperature.
	printf("Room Temperature: %f\n",var.tempRoom);
	//Engine Temperature Controller State.
	if(controller==on){
		printf("Engine Temperature Controller:On\n");
	}
	else{
		printf("Engine Temperature Controller:Off\n");
	}
	// Engine Temperature.
	printf("Engine Temperature: %f\n",var.tempEngine);

}
