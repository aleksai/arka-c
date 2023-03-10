#include "DEV_Config.h"
#include "LCD_1in3.h"
#include "GUI_Paint.h"
// #include "GUI_BMP.h"

#include "main.h"

#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

void initScreen(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1in3_LCD);
    
    /* Module Init */
	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }
	
    /* LCD Init */
	printf("1.3inch LCD demo...\r\n");
	LCD_1in3_Init(HORIZONTAL);
	LCD_1in3_Clear(BLACK);
    
    UWORD *BlackImage;
    UDOUBLE Imagesize = LCD_HEIGHT*LCD_WIDTH*2;
    printf("Imagesize = %d\r\n", Imagesize);
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // printf("size = %d\r\n",sizeof(BlackImage) / sizeof(UWORD));
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_WIDTH, LCD_HEIGHT, 0, BLACK, 16);
    Paint_Clear(BLACK);

    // /* GUI */
    // printf("drawing...\r\n");
    // /*2.Drawing on the image*/
    // Paint_DrawLine(20, 10, 70, 60, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    // Paint_DrawLine(70, 10, 20, 60, RED, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    // Paint_DrawLine(170, 15, 170, 55, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    // Paint_DrawLine(150, 35, 190, 35, RED, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

    // Paint_DrawRectangle(20, 10, 70, 60, BLUE, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    // Paint_DrawRectangle(85, 10, 130, 60, BLUE, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    // Paint_DrawCircle(170, 35, 20, GREEN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    // Paint_DrawCircle(170, 85, 20, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    // Paint_DrawString_EN(5, 70, "hello world", &Font16, WHITE, BLACK);
    // Paint_DrawString_EN(5, 90, "waveshare", &Font20, RED, IMAGE_BACKGROUND);

    // Paint_DrawNum(20, 200, 123456789, &Font20, BLUE, IMAGE_BACKGROUND);
        
    // /*3.Refresh the picture in RAM to LCD*/
    LCD_1in3_Display(BlackImage);
    // DEV_Delay_ms(20);

    free(BlackImage);
    BlackImage = NULL;
}

void playSequence(char* sequence)
{
    size_t f;
    for (f = 0; f < 24; f++) {
        // LCD_1in3_Clear(BLACK);
        
        UWORD *BlackImage;
        UDOUBLE Imagesize = LCD_HEIGHT*LCD_WIDTH*2;
        printf("Imagesize = %d\r\n", Imagesize);
        if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
            printf("Failed to apply for black memory...\r\n");
            exit(0);
        }

        Paint_NewImage(BlackImage, LCD_WIDTH, LCD_HEIGHT, 0, BLACK, 16);
        Paint_Clear(BLACK);

        size_t i;
        for (i = 576 * f; i < 576 * (f + 1); i++) {
            int row;
            row = (i - 576 * f) / 24;
            int col;
            col = (i - 576 * f) % 24;
            printf("%c", sequence[i]);
            Paint_DrawRectangle(2 + col * 10, 2 + row * 10, 10 + col * 10, 10 + row * 10, sequence[i] == '1' ? WHITE : BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
        }

        LCD_1in3_Display(BlackImage);
        DEV_Delay_ms(40);

        free(BlackImage);
        BlackImage = NULL;
    }

    playSequence(sequence);
}

void stopScreen(void)
{
    DEV_ModuleExit();
}














// #include "DEV_Config.h"
// #include "LCD_1in3.h"
// #include "GUI_Paint.h"
// #include "KEY_APP.h"

// #include "main.h"

// #include <stdio.h>      //printf()
// #include <stdlib.h>     //exit()
// #include <signal.h>     //signal()
// #include <time.h>  

// /************************************
// When using the button
// Please execute
//     sudo nano /boot/config.txt
// Add at the end
//     gpio=6,19,5,26,13,21,20,16=pu
// *************************************/
// void KEY_1in3_test(void)
// {
//     // Exception handling:ctrl + c
//     signal(SIGINT, Handler_1in3_LCD);
    
//     /* Module Init */
//     if(DEV_ModuleInit() != 0){
//         DEV_ModuleExit();
//         exit(0);
//     }
//     printf("Use this routine to add gpio=6,19,5,26,13,21,20,16=pu at the end of /boot/config.txt\r\n");

    
//     /* LCD Init */
//     printf("1.3inch LCD KEY demo...\r\n");
//     LCD_1in3_Init(HORIZONTAL);
//     LCD_1in3_Clear(WHITE);
    
//     UWORD *BlackImage;
    
//     UWORD Imagesize = LCD_HEIGHT*LCD_WIDTH;
//     if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
//         printf("Failed to apply for black memory...\r\n");
//         exit(0);
//     }

//     /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
//     printf("LCD_WIDTH = %d   LCD_HEIGHT  = %d\r\n", LCD_WIDTH , LCD_HEIGHT);
    
//     Paint_NewImage(BlackImage, LCD_WIDTH, LCD_HEIGHT, 0, WHITE, 16);
//     Paint_Clear(WHITE);
   
//     /* Monitor button */
//     printf("Listening KEY\r\n");
//     KEY_Listen(BlackImage);
    
//     /* Module Exit */
//     free(BlackImage);
//     BlackImage = NULL;
//     DEV_ModuleExit();
// }
