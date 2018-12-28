/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/* Modified: Mihnea Chirila for F18, 10/30/18                                                          */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include "Test.h"
/*** function declarations ***/

/* print a menu */
void PrintMenu();

/* Test all functions */
//void AutoTest(void);

int main()
{
	int rc ;


#ifdef DEBUG
	rc=AutoTest();
	if (rc==0){
		printf("Auto Test finished Successfully!\n");}
	if(rc!=0){
		printf("Auto Test failed, return code %d\n",rc);}
	rc = 0 ;

#else
	IMAGE *image=NULL;
		

	int option,rotoption,respercent;/* user input option */
	char fname[SLEN];		/* input file name */
	int brightness = -256;
	float angle,satpercent;
	int result;
	int prevoption=0;

	rc = 1 ;
	PrintMenu();
	printf("Please make your choice: ");
	scanf("%d", &option);
	
	while (option != EXIT) {
		if (option == 1) {
		   /* if(option==prevoption){
			DeleteImage(image);}*/
		    printf("Please input the file name to load: ");
		    scanf("%s", fname);
		    image = LoadImage(fname);	    
			
		     
		}
	

		/* menu item 2 - 8 requires image is loaded first */
        else if (option >= 2 && option <= 11) {
	    if (image==NULL){
		printf("No image to process\n");}
            
	else {
	switch (option) {
	  case 2:
	    printf("Please input the file name to save: ");
	    scanf("%s", fname);
	    result=SaveImage(fname, image);
	    DeleteImage(image);
	    image=NULL;
	    break;
	  case 3:
            image=BlackNWhite(image);
            printf("\"Black & White\" operation is done!\n");
            break;
	  case 4:
            image=Edge(image);
            printf("\"Edge\" operation is done!\n");
            break;
          case 5:
            image=Shuffle(image);
            printf("\"Shuffle\" operation is done!\n");
            break;
	  case 6:
	    while(brightness > 255 || brightness < -255){
	    printf("Enter brightness value (between -255 and 255):");
	    scanf("%d", &brightness);
						}
            image=Brightness(image, brightness);
            printf("\"brightness\" operation is done!\n");
            break;
	  case 7:
            image=HMirror(image);
            printf("\"Horizontally Mirror\" operation is done!\n");
            break;
          case 8:
            printf("Enter hue rotation angle:");
            scanf("%f", &angle);
            image=HueRotate(image, angle);
            printf("\"HueRotate\" operation is done!\n");
            break;
	  case 9:
	    printf("Enter 1 for Horizontal flip, 2 for vertical flip\n");
	    printf("3 for rotate right, or 4 for rotate left: ");
	    scanf("%d",&rotoption);
	    image=Rotate(image,rotoption);
	    printf("\"Rotate\" operation is done!\n");
	    break;

	  case 10:
	    printf("Enter the percentage you want to resize the image: ");
	    scanf("%d",&respercent);
	    image=Resize(image,respercent);
	    printf("\"Resize\" operation is done\n");
	    break;
	  
	  case 11:
	    printf("Enter the percentage of saturation you want: ");
	    scanf("%f",&satpercent);
	    image=Saturate(image,satpercent);
	    printf("\"Saturation\" operation is done\n");
	    break;
	
		
		

	    default:
		break;

				}
			}
		}

	else if (option == 12) {
            rc=AutoTest();
            rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }
	prevoption=option;

		/* Process finished, waiting for another input */
        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
	if(option==1 && prevoption==1){
		DeleteImage(image);
		image=NULL;}
	
	
	}



        if(image!=NULL){
	DeleteImage(image);
	image=NULL;}
    printf("You exit the program.\n");
#endif

	return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Sketch the edge of an image\n");
    printf(" 5: Shuffle an image\n");
    printf(" 6: Adjust the brightness of an image\n");
    printf(" 7: Mirror an image horizontally\n");
    printf(" 8: Adjust the hue of an image\n");
    printf(" 9: Rotate or flip the image\n");
    printf("10: Resize the image\n");
    printf("11: Saturate the image\n");
    printf("12: Test all functions\n");
    printf("13: Exit\n");
}


/* auto test*/


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
