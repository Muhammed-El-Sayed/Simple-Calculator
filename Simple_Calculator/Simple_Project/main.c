/*
 * main.c
 *
 *  Created on: Nov 3, 2020
 *      Author: g.version
 */


#include"keypad.h"
#include"lcd.h"


#define INPUT_MAX_LENGTH 17

uint8 check_input_correct(uint8 * const input);



int main(void)
{

	LCD_init();
	uint8 input[INPUT_MAX_LENGTH]={};


    uint8 i=0;

	while(1)
	{


		do{
			_delay_ms(250);
			 input[i]= KeyPad_getPressedKey();
			 if(input[i]==0||input[i]==1||input[i]==2||input[i]==3||input[i]==4||input[i]==5||input[i]==6||input[i]==7||input[i]==8||input[i]==9)
			 {
				 LCD_displayCharacter(input[i]+48);

			 }
			 else
			 {
				 LCD_displayCharacter(input[i]);
			 }
			 ++i;
		}while( (input[i-1] != '=') && (i<= INPUT_MAX_LENGTH) );


		int j=0;
		while(input[j]!='=')
		{
			if(input[j]>=0 && input[j]<=9)
			input[j]+=48;

			++j;
		}



		if(check_input_correct(input))
		{

           uint8 s=0;
           uint8 operations_count=0;
           uint8 numbers_count=0;
           while(input[s]!='\0')
           {

        	   if(input[s]=='+'||input[s]=='-'||input[s]=='*'||input[s]=='/')
        	   {
        		   ++operations_count;
        	   }

        	   ++s;
           }
           numbers_count=operations_count+1;

           sint16 *operations_array =(sint16*)malloc(operations_count*sizeof(sint16));
           sint16 *numbers_array =(sint16*)malloc(numbers_count*sizeof(sint16));

           s=0;
           uint8 h=0;
           uint8 m=0;
           while(input[s]!='\0')
           {

        	   while(input[s]>='0' && input[s]<='9')
        	   {
        		   numbers_array[h]=(numbers_array[h]*10) +(input[s]-48);
        		   ++s;
        	   }
        	   ++h;
        	   if(input[s]=='+'||input[s]=='-'||input[s]=='*'||input[s]=='/')
        	   {
        		   operations_array[m]=input[s];
        		   ++m;
        	   }

        	   ++s;
           }


           sint16 result=numbers_array[0];
           for(sint16 i=0;i<operations_count;i++)
           {
        	   switch(operations_array[i])
        	   {
        	   case '+' : result +=numbers_array[i+1];
        	              break;
        	   case '-' : result -=numbers_array[i+1];
        	              break;
        	   case '*' : result *=numbers_array[i+1];
        	              break;
        	   case '/' : result /=numbers_array[i+1];
        	              break;

        	   }
           }


             LCD_intgerToString(result);
		}
		else
		{

			 LCD_displayStringRowColumn(1,0,"ERROR INPUT");

		}

		 while(KeyPad_getPressedKey() != 13);
			 LCD_init();



		i=0;
	}

}







uint8 check_input_correct(uint8 * const input)
{

	uint8 j=0;
	while(input[j] != '\0')
	{
		uint8 l=0;
		while(input[l] !='\0')
		{
			if(input[l]!='=' && input[l+1]=='\0')
			{
				return 0;
			}
			++l;
		}

		uint8 m=0;
		uint8 flag=1;
		while(input[m] !='\0')
		{
			if((input[m] == '+' || input[m] == '-' ||input[m] == '*' ||input[m] == '/') )
			{
				flag=0;
			}
			++m;
		}
		if(flag==1)
		{
			return 0;
		}

		if( (input[j] == '+' || input[j] == '-' ||input[j] == '*' ||input[j] == '/') &&(input[j+1] == '+' || input[j+1] == '-' ||input[j+1] == '*' ||input[j+1] == '/' || input[j+1]=='=') && (input[j+1]!='\0'))
		{
			return 0;
		}

		if((input[j] == '+' || input[j] == '-' ||input[j] == '*' ||input[j] == '/') && (j==0 || j==15))
		{
			return 0;
		}

		if(input[j] == '=')
		{
			if(j==0 || j==1 || j==2)
			{
				return 0;
			}
		}

		++j;
	}
	return 1;
}
