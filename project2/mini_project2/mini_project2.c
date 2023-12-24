#include<avr/io.h>
#include<avr/interrupt.h>
#include"util/delay.h"
//function prototype
void display(void);
//Global variables
unsigned char sec1=0,sec2=0,min1=0,min2=0,hour1=0,hour2=0;
//Timer1
void Timer1_CTC_Init(void){

	TCCR1A=(1<<FOC1A);
	TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10);
	TCNT1=0;
	OCR1A=1000;
	TIMSK|=(1<<OCIE1A);
	SREG|=(1<<7);//Global interrupt enable


}
ISR(TIMER1_COMPA_vect){
	sec1++; //sec1 increment;
	if(sec1==10){
		sec2++;
		sec1=0;
	}
	if(sec2==6){
		min1++;
		sec2=0;
	}
	if(min1==10){
		min2++;
		min1=0;
	}
	if(min2==6){
		hour1++;
		min2=0;
	}
	if(hour1==10){
		hour2++;
		hour1=0;
	}
	if(hour2==99){
		sec1=0,sec2=0,min1=0,min2=0,hour1=0,hour2=0;
	}
}
//ex_interrupt 0

void INT0_Init(void){
	DDRD&=~(1<<2);//PIN push button INT0
	PORTD|=(1<<2);//enable internal pull up

	//Falling
	MCUCR|=(1<<ISC01);
	MCUCR&=~(1<<ISC00);
	GICR|=(1<<INT0);//enable external interrupt 0
	SREG  |= (1<<7);//I bit
}
ISR(INT0_vect){
	//reset
	sec1=0,sec2=0,min1=0,min2=0,hour1=0,hour2=0;
}
//ex_interrupt 1

void INT1_Init(void){
	DDRD&=~(1<<3);
	//rising
	MCUCR|=(1<<ISC11)|(1<<ISC10);
	GICR|=(1<<INT1);
	SREG  |= (1<<7);
}
ISR(INT1_vect){
	//stop
	TCCR1B&=~(1<<CS12)&~(1<<CS10);
	while((PIND&(1<<PD3))==1){}
}

//ex_interrupt2

void INT2_Init(void){
	DDRB&=~(1<<2);//PIN push button INT2
	PORTB|=(1<<2);//enable internal pull up

	//Falling
	MCUCSR&=~(1<<ISC2);
	GICR|=(1<<INT2);//enable extrnal inturrupt 2
	SREG  |= (1<<7);//I bit
}
ISR(INT2_vect){
	//resume
	TCCR1B|=(1<<CS12)|(1<<CS10);
}

int main(void){
	DDRC|=0x0F;//PORTC 0,1,2,3 FOR THE 7 SEGMENT
	PORTA|=0x3F;//TURN ON ALL THE 7 SEGMENTS
	//SREG|=(1<<7);//Global interrupt enable
	//Interrupts
	Timer1_CTC_Init();
	INT0_Init();
	INT1_Init();
	INT2_Init();

	while(1){
		display();
	}

}
//Display function
void display(void){
	//Display PA0(sec1)on the 7 segment
	PORTA = 0x00 ;
	PORTA |= (1<< PA0) ;
	PORTC = (PORTC & 0xF0) | (sec1 & 0x0F);
	_delay_ms(2);

	//Display PA1(sec2)on the 7 segment
	PORTA = 0x00 ;
	PORTA |= (1<< PA1) ;
	PORTC = (PORTC & 0xF0) | (sec2 & 0x0F);
	_delay_ms(2);

	//Display PA2(min1)on the 7 segment
	PORTA = 0x00 ;
	PORTA |= (1<< PA2) ;
	PORTC = (PORTC & 0xF0) | (min1 & 0x0F);
	_delay_ms(2);

	//Display PA3(min2)on the 7 segment
	PORTA = 0x00 ;
	PORTA |= (1<< PA3) ;
	PORTC = (PORTC & 0xF0) | (min2 & 0x0F);
	_delay_ms(2);

	//Display PA4(hour1)on the 7 segment
	PORTA = 0x00 ;
	PORTA |= (1<< PA4) ;
	PORTC = (PORTC & 0xF0) | (hour1 & 0x0F);
	_delay_ms(2);

	//Display PA0(hour2)on the 7 segment
	PORTA = 0x00 ;
	PORTA |= (1<< PA5) ;
	PORTC = (PORTC & 0xF0) | (hour2 & 0x0F);
	_delay_ms(2);
}
