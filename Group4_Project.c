/** \anchor form0
 *
 * @brief Form recognition. 
 *
 * @file

 Example of form recognition and print the result on UART and the LCD Screen.

 * @author Foucault Alisson
 */

#include <pob-eye.h>

// Include bitmap list and dictionnary of forms
#include "Bitmap.h" 
#include "pattern.h"
#include "pad.h"

int main (void)
{	
	UInt8 i=0,Nb_Identify=0;
	
	// List of form
	Form ListOfForm[MAX_OF_FORM];

	// Struct of three pointers on the RGB components
	UInt8 * FrameFromCam;

	//The pixels will be stocked in the LCD buffer
	UInt8 LCD_Buffer [LCD_WIDTH*LCD_HEIGHT*BITS] ;
	GraphicBuffer ScreenBuffer ;

	// System and LCD screen initialization
	InitPobeye2();
	InitI2C(I2C_100_KHZ);
	InitCameraPobeye2();
	InitLCD();	
	
     //
     InitPobProto();
     SwitchOnAllServo();	
	
	// Get the pointer of the red,green and blue video buffer
	FrameFromCam = GetRGBFrame();
		
	// Init the Graphic buffer with 128 per 64, one pixel per bit and LCD_Buffer
	InitGraphicBuffer( &ScreenBuffer, LCD_WIDTH,LCD_HEIGHT,ONE_BIT,LCD_Buffer);

	// clear the graphic buffer
	ClearGraphicBuffer(&ScreenBuffer);
	
	// set Robot facing down
	SetServoMotor(0, 30);
	
	UInt8 Right_Turn_Time=0;
	UInt8 Left_Turn_Time=0;
	UInt8 turned=0;
	
	
	while(1)
	{		
		
		// grab the RGB components
		GrabRGBFrame();				
		
		// Binary the three RGB Buffer
		BinaryRGBFrame(FrameFromCam); 
		
		// Try to identify the forms and make a list of it
		Nb_Identify=IdentifyForm(FrameFromCam,ListOfForm,pattern);	

		for (i=0;i<Nb_Identify;i++)
		{	
			Right_Turn_Time=0;
			Left_Turn_Time=0;

			switch (ListOfForm[i].id)
			{
			case IDP_0_CROSS:
				// Draw bitmap on the buffer and the LCD screen
				DrawBitmap(0,0,IDB_CROSS,bitmap,&ScreenBuffer);
				DrawLCD(&ScreenBuffer);
				MoveBot(RUN);
				turned = 0;
			break;
				
			case IDP_2_KING:
				DrawBitmap(0,0,IDB_KING,bitmap,&ScreenBuffer);
				DrawLCD(&ScreenBuffer);
				MoveBot(STOP);
			break;

			case IDP_4_TREFLE:
				DrawBitmap(0,0,IDB_BIGA,bitmap,&ScreenBuffer);
				DrawLCD(&ScreenBuffer);
				MoveBot(RIGHT);
				turned = 1;
				
				//WaitMs(2000);
				//MoveBot(STOP);
			break;
			
			case IDP_5_TRIANGLE:
				DrawBitmap(0,0,IDB_TRIANGLE,bitmap,&ScreenBuffer);
				DrawLCD(&ScreenBuffer);
				MoveBot(LEFT);
				//WaitMs(2000);	
				//MoveBot(STOP);
				turned =2;
			break;
			default:
				Right_Turn_Time=0;
				Left_Turn_Time=0;

			break;
			}
		}				
	
	if (Nb_Identify == 0)
		{
		DrawBitmap(0,0,IDB_NOFORMS,bitmap,&ScreenBuffer);
		DrawLCD(&ScreenBuffer);
		
		if(turned==2){
			MoveBot(LEFT);
		}
		else if(turned==1) {
			MoveBot(RIGHT);
		}
		else {
		
		if(Right_Turn_Time==0&&Left_Turn_Time==0){
       		Right_Turn_Time=500;
        		MoveBot(RIGHT);
        		WaitMs(Right_Turn_Time);
        		MoveBot(STOP);
       		WaitMs(100);
        	}
        
		else if(Right_Turn_Time>=Left_Turn_Time){
        		Left_Turn_Time=Right_Turn_Time+Left_Turn_Time+500;
        		MoveBot(LEFT);
        		WaitMs(Left_Turn_Time);
        		MoveBot(STOP);
        		WaitMs(100);
        	}
        
		else if(Left_Turn_Time>Right_Turn_Time){
        		Right_Turn_Time=Right_Turn_Time+Left_Turn_Time+500;
        		MoveBot(RIGHT);
        		WaitMs(Right_Turn_Time);
        		MoveBot(STOP);
        		WaitMs(100);
		}
		
	     else if(Right_Turn_Time==2000&&Left_Turn_Time==2000){
        	break;
          }
          
          }

		}
			
	}
		
	return 0;
}

