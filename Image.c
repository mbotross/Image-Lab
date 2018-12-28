#include "Image.h"
#include<stdlib.h>
#include<assert.h>
#include<stdio.h>
/* Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y){
	assert(image);
	
        return image->R[y*ImageWidth(image)+x];
}
unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y){
	assert(image);

        return image->G[y*ImageWidth(image)+x];
	

	}
unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y){
	assert(image);

        return image->B[y*ImageWidth(image)+x];

	}
/* Set the color intensity of the Red channel of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r){
	assert(image);
	assert(0<=r && r<=255);
	image->R[x+y*ImageWidth(image)]=r;		
	
	}



void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g){
	assert(image);  	
	assert(0<=g && g<=255);
	image->G[x+y*ImageWidth(image)]=g;
	
	}
void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b){
	assert(image);
	assert(0<=b && b<=255);
	image->B[x+y*ImageWidth(image)]=b;
	
	}

/* Return the image’s width in pixels */
unsigned int ImageWidth(const IMAGE *image){
	assert(image);
	return (unsigned int) image->W;
	}
/* Return the image’s height in pixels */
unsigned int ImageHeight(const IMAGE *image){
	assert(image);
	return (unsigned int) image->H;
	
	}


//Creates image based on certain width and height

IMAGE *CreateImage(unsigned int Width, unsigned int Height){ 
//4 malloc
	IMAGE *image;
	image=malloc(sizeof(IMAGE));
	image->R=malloc(sizeof(unsigned char)*Width*Height);
	image->G=malloc(sizeof(unsigned char)*Width*Height);
	image->B=malloc(sizeof(unsigned char)*Width*Height);
	

	if(!image){
		free(image);
		perror("Out of memory!\n");
		exit(10);
	}

	if(!image->R){
		free(image->R);
		perror("Red pixels out of range");
		exit(10);
	}
	if(!image->G){
		free(image->G);
                perror("Green pixels out of range");
                exit(10);
        }

	if(!image->B){
		free(image->B);
                perror("Blue pixels out of range");
                exit(10);
        }




	image->W=Width;
	image->H=Height;

	return image;}


//Deletes image
void DeleteImage(IMAGE *image){

        assert(image);
        free(image->R);
        free(image->G);
        free(image->B);
       
	//set R,G,B pointers to null
        image->R=NULL;
        image->G=NULL;
        image->B=NULL;
	
	free(image);
        	
}



