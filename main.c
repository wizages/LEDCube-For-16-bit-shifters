/*
 * GccApplication3.c
 *
 * Created: 4/19/2016 3:13:16 PM
 * Author : 7198653
 */ 
#define F_CPU 16000000

#define dataPin1 1 // 0 shift
#define dataPin2 16 // 4 shift
#define dataPin3 32 // 5 shift
#define dataPin4 64 // 6 shift
#define dataPin5_D 4 // 2 shift
#define dataPin6_D 8 // 3 shift
#define dataPin7_D 16 // 4 shift
#define dataPin8_D 32 // 5 shift
#define dataPin9_D 64 // 6 shift
#define clockPin 2 // 1 shift
#define chipPin 8 // 3 shift
#define latchPin 4 // 2 shift

#include <avr/io.h>
#include <util/delay.h>

void registerWrite(int data1, int data2, int data3, int data4, int data5, int data6, int data7, int data8, int data9);

int main(void)
{
	DDRB = 0xff;
	DDRD = 0xff;
	PORTB = 0;
    /* Replace with your application code */
    while (1) 
    {
		registerWrite(2, 10, 2, 10, 2, 10, 2, 10, 2);
		_delay_ms(1000);
		registerWrite(10, 2, 10, 2, 10, 2, 10, 2, 10);
		_delay_ms(1000);
    }
}

void registerWrite(int data1, int data2, int data3, int data4, int data5, int data6, int data7, int data8, int data9)
{
	//Allow writing
	PORTB &= ~(chipPin);
	PORTB &= ~(latchPin);

	//Write data to the chips ahhhhhh yeah!
	for (int i = 0; i < 16; i++)  {
		PORTB &= ~(dataPin1);
		PORTB &= ~(dataPin2);
		PORTB &= ~(dataPin3);
		PORTB &= ~(dataPin4);
		
		PORTD &= ~(dataPin5_D);
		PORTD &= ~(dataPin6_D);
		PORTD &= ~(dataPin7_D);
		PORTD &= ~(dataPin8_D);
		PORTD &= ~(dataPin9_D);
		
		PORTB |= ((data1 >> (15-i)) & 1);
		PORTB |= ((data2 >> (15-i)) & 1) << 4;
		PORTB |= ((data3 >> (15-i)) & 1) << 5;
		PORTB |= ((data4 >> (15-i)) & 1) << 6;

		PORTD |= ((data5 >> (15-i)) & 1) << 2;
		PORTD |= ((data6 >> (15-i)) & 1) << 3;
		PORTD |= ((data7 >> (15-i)) & 1) << 4;
		PORTD |= ((data8 >> (15-i)) & 1) << 5;
		PORTD |= ((data9 >> (15-i)) & 1) << 6;
		
		PORTB |= clockPin;
		PORTB &= ~(clockPin);
	}
	//Allow reading
	PORTB |= latchPin;
	PORTB |= chipPin;
}

