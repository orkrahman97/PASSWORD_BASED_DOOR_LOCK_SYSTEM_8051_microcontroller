#include <reg51.h>



sbit r1 = P2 ^ 0;       // Setting  Row 1 of keypad
sbit r2 = P2 ^ 1;				//  Setting  Row 2 of keypad
sbit r3 = P2 ^ 2;				//  Setting  Row 3 of keypad
sbit r4 = P2 ^ 3;				//  Setting  Row 4 of keypad

sbit c1= P3 ^ 0;				//  Setting  column 1 of keypad
sbit c2 = P3 ^ 1;				//  Setting  column 2 of keypad
sbit c3 = P3 ^ 2;				//  Setting  column 3 of keypad


sbit motorpin1 = P3 ^ 3;			// setting motorpin 1
sbit motorpin2 = P3 ^ 4;			// setting motorpin 2


sbit rs = P3 ^ 5;							//  setting the regstr select pin
sbit rw = P3 ^ 6;							//  setting the read/write pin
sbit en = P3 ^ 7;							//  setting the enable  pin


unsigned char default_pin[] = {"737271"}; // Predefined Pin 
unsigned char user_pin[6];  // Pin entered by the user will be stored in this array



void delay(unsigned int j)    
{
    int a, b;
    for (a = 0; a < j; a++)
    {
        for (b = 0; b < 8; b++)
            {
              }
    }
}


void lcdCommand(unsigned char A)
{
    P1 = A;					// Port 1 will take A as input
    rs = 0;
		rw = 0;				// writingdata of p1 in LCD
    en = 1;
    delay(1000);
    en = 0;
}

void lcdData(unsigned char i)
{
    P1 = i;			// // Port 1 will take i as input
    rs = 1;			
    rw = 0;		// writingdata of port 1 in LCD
    en = 1;		
    delay(1000);
    en = 0;
}


void display(unsigned char *q)
{
    int k;
    for (k = 0; q[k] != '\0'; k++)  // Until q reaches end of line display the string stored in character pointer
    {
        lcdData(q[k]);
    }
    delay(1000);
}

char keypadInput()
{
    int x = 0;
    while (x == 0)
    {
        r1 = 0;   // Selecting row 0
        r2 = 1;
        r3 = 1;
        r4 = 1;
        if (c1 == 0)    // selecting element in row 0 and col 0 of keypad
        {
            lcdData('*'); 
            delay(1000);
            x = 1;
            return '1';
        }
        if (c2 == 0)  // selecting element in row 0 and col 0 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '2';
        }
        if (c3 == 0)  // selecting element in row 0 and col 0 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '3';
        }
        r1 = 1;
        r2 = 0;			// Selecting row 1
        r3 = 1;
        r4 = 1;

        if (c1 == 0) // selecting element in row 1 and col 0 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '4';
        }
        if (c2 == 0)  // selecting element in row 1 and col 1 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '5';
        }
        if (c3 == 0)  // selecting element in row 1 and col 2 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '6';
        }

        r1 = 1;
        r2 = 1;
        r3 = 0;			// Selecting row 2
        r4 = 1;
        if (c1 == 0)  // selecting element in row 2 and col 0 of keypad
        {
            lcdData('*');  
            delay(1000);
            x = 1;
            return '7';
        }
        if (c2 == 0)  // selecting element in row 2 and col 1 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '8';
        }
        if (c3 == 0) // selecting element in row 2 and col 2 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '9';
        }

        r1 = 1;
        r2 = 1;
        r3 = 1;   
        r4 = 0;  // Selecting row 3

        if (c1 == 0)    // selecting element in row 3 and col 0 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '*';
        }
        if (c2 == 0)   // selecting element in row 3 and col 1 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '0';
        }
        if (c3 == 0) // selecting element in row 3 and col 2 of keypad
        {
            lcdData('*');
            delay(1000);
            x = 1;
            return '#';
        }
    }
}

void passwordCheck() 
{
    if (default_pin[0] == user_pin[0] && default_pin[1] == user_pin[1] && default_pin[2] == user_pin[2] && default_pin[3] == user_pin[3] && default_pin[4] == user_pin[4] && default_pin[5] == user_pin[5]) // checking whether the default password matches with the password user has entered
    {
        delay(1000);
        lcdCommand(0x01); // Clearing the display
        lcdCommand(0x80); //  displaying line 1 of lcd 
        
        display("Access Granted");
        delay(1000);
        motorpin1 = 1;  // Motor will be on and move in clockwise direction once
        motorpin2 = 0;
        lcdCommand(0xc0);		//  displaying line 2 of lcd 	
        display("DOOR OPENED");
				motorpin1 = 1;  // Motor will be on and move in clockwise direction once
        motorpin2 = 0;
        lcdCommand(0x01);		// Clearing the display					
    }
    else
    {
        lcdCommand(0x01);				// Clearing the display
        lcdCommand(0x80); 			//  selecting line 1 of lcd 
        display("Access denied");
        delay(1000);
        lcdCommand(0x01);      // Clearing the display
    }
}



void main()
{
    lcdCommand(0x0F);							// Turning the LCD on
    lcdCommand(0x38); 						// 2 lines will be displayed in the lcd
    lcdCommand(0x01); 						// Clearing the display

    while(1)
    {
        unsigned int i = 0;
        lcdCommand(0x80);    //  displaying line 1 of lcd 
        display("Enter your pin");
        delay(1000);
        lcdCommand(0xc0);  //  displaying line 2 of lcd 
        while (default_pin[i] != '\0') // Reading default pin untill it reaches end of line
        {
            user_pin[i] = keypadInput(); // KeypadInput is stored in user_pin array
            delay(1000);
            i++;
        }
        passwordCheck(); // Checking the default pin and user input pin
    }
}