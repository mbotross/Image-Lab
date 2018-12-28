#include "Advanced.h"
#include "Image.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
/* Adjust the brightness of an image */
IMAGE *Brightness(IMAGE *image, int brightness) {
	assert(image);
	unsigned int height,width;
	unsigned char pixelR,pixelG,pixelB;
	height=ImageHeight(image);
	width=ImageWidth(image);
//get pixel from original
	for (int i=0; i<width; i++){
		for (int j=0; j<height; j++){
			pixelR=GetPixelR(image,i,j);
			pixelG=GetPixelG(image,i,j);
			pixelB=GetPixelB(image,i,j);

			//see if new pixel is within the bounds of R,G,B
			//and set the pixel back into the R,G,B  pointers
			if (pixelR + brightness > 255){
				SetPixelR(image,i,j,255); 
			}else if(pixelR + brightness < 0){
				SetPixelR(image,i,j,0);
			}else{
				SetPixelR(image,i,j,pixelR+brightness);
				
			}

			if (pixelG + brightness > 255){
				SetPixelG(image,i,j,255);

			}else if(pixelG + brightness < 0){
				SetPixelG(image,i,j,0);

			}else{
				SetPixelG(image,i,j,pixelG+brightness);

			
			}

			if (pixelB + brightness > 255){
				SetPixelB(image,i,j,255);

			
			}
			else if(pixelB + brightness < 0){
				SetPixelB(image,i,j,0);

			}else{
				SetPixelB(image,i,j,pixelB+brightness);
	
			
			}
		}
	}

	return image;
}

/* Mirror an image horizontally */
IMAGE *HMirror(IMAGE *image){
	assert(image);
	unsigned int height,width;
	int x, y;
	unsigned char pixelR,pixelG,pixelB;
	//get image height and width from pointer
	height=ImageHeight(image);
	width=ImageWidth(image);
    for (y = 0; y < height; y++) {
        for (x = 0; x < width/ 2; x++) {
		pixelR=GetPixelR(image,x,y);
                pixelG=GetPixelG(image,x,y);
                pixelB=GetPixelB(image,x,y);
		//Mirror half of the image
		SetPixelR(image,width-1-x,y,pixelR);
		SetPixelG(image,width-1-x,y,pixelG);
		SetPixelB(image,width-1-x,y,pixelB);


			
		}
	}
	return image;
}

void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3])
{
	/* Memory for result */
	float result[3] = {0, 0, 0};

	/* Perform multiplication */
	result[0] = matrix[0][0]*vector[0] + matrix[0][1]*vector[1] + matrix[0][2]*vector[2];
	result[1] = matrix[1][0]*vector[0] + matrix[1][1]*vector[1] + matrix[1][2]*vector[2];
	result[2] = matrix[2][0]*vector[0] + matrix[2][1]*vector[1] + matrix[2][2]*vector[2];

	/* Copy result into other stack's memory */
	vector[0] = result[0];
	vector[1] = result[1];
	vector[2] = result[2];
}

IMAGE *HueRotate(IMAGE *image, float angle)
{	assert(image);
	/* Matrix to transform normalized
	// RGB color vector from the RGB
	// color space to the YIQ color space */
	unsigned int height,width;
	unsigned char pixelR,pixelG,pixelB;
	static const float RGBtoYIQMatrix[3][3] = {{0.299,  0.587,  0.114},
								  			   {0.596, -0.274, -0.321},
								  			   {0.211, -0.523,  0.311}};

	/* Matrix to transform normalized
	// YIQ color vector from the YIQ
	// color space to the RGB color space */
	static const float YIQtoRGBMatrix[3][3] = {{1.000,  0.956,  0.621},
								  			   {1.000, -0.272, -0.647},
								  			   {1.000, -1.107,  1.705}};

	const float cs = cos(angle), ss = sin(angle);

	/* Matrix to perform a hue
	// rotation on a normalized
	// YIQ color vector*/
	const float XYPlaneVectorRotateMatrix[3][3] = {{1.000, 0.000, 0.000},
												   {0.000, cs, -ss},
												   {0.000, ss, cs}};

	/* Image variables */
	float temp[3];
	
	height=ImageHeight(image);
	width=ImageWidth(image);
	for(unsigned int i = 0; i < width; i++)
	{
		for(unsigned int j = 0; j < height; j++)
		{
			/* Create a normalized RGB color
			// vector fro the current pixel
			// in the image */
			pixelR=GetPixelR(image,i,j);
			pixelG=GetPixelG(image,i,j);
			pixelB=GetPixelB(image,i,j);

			temp[0] = (float)pixelR/255;
			temp[1] = (float)pixelG/255;
			temp[2] = (float)pixelB/255;

			/* Transform the RGB vector
			// to a YIQ vector */
			matrix_3_3multiplyVector_3(temp, RGBtoYIQMatrix);

			/* Perform the DIP */
			matrix_3_3multiplyVector_3(temp, XYPlaneVectorRotateMatrix);

			/* Transform back to RGB */
			matrix_3_3multiplyVector_3(temp, YIQtoRGBMatrix);

			/* Denormalize and store back into the image */
			temp[0] = temp[0] * 255;
			temp[0] = temp[0] < 0 ? 0 : temp[0];
			temp[0] = temp[0] > 255 ? 255 : temp[0];
			temp[1] = temp[1] * 255;
			temp[1] = temp[1] < 0 ? 0 : temp[1];
			temp[1] = temp[1] > 255 ? 255 : temp[1];
			temp[2] = temp[2] * 255;
			temp[2] = temp[2] < 0 ? 0 : temp[2];
			temp[2] = temp[2] > 255 ? 255 : temp[2];


			SetPixelR(image,i,j,(unsigned char)temp[0]);
			SetPixelG(image,i,j,(unsigned char)temp[1]);
			SetPixelB(image,i,j,(unsigned char)temp[2]);
		
		}
	}
	return image;
}

//Saturate the image to a certain percentage
IMAGE *Saturate(IMAGE *image, float percent){

	assert(image);
	int x, y;
        float tmpr,tmpg,tmpb; 
	float newr,newg,newb;
        unsigned int width, height;
        height=ImageHeight(image);
        width=ImageWidth(image);
        unsigned char pixelR,pixelG,pixelB;
        
        for (y = 0; y < height; y++) {
   		for (x = 0; x < width; x++) {  
			pixelR=GetPixelR(image,x,y);
                        pixelG=GetPixelG(image,x,y);
                        pixelB=GetPixelB(image,x,y);
                        tmpr = (pixelR + pixelG + pixelB) / 3;
			tmpg=tmpr;
			tmpb=tmpr;
			tmpr=pixelR-tmpr;
			tmpg=pixelG-tmpg;
			tmpb=pixelB-tmpb;
			//saturate calculation	
			newr=pixelR+(tmpr*percent/100.00);
			newg=pixelG+(tmpg*percent/100.00);
			newb=pixelB+(tmpb*percent/100.00);
			
			//Check bounds
			if(newr<0){
				newr=0;}
			if(newr>MAX_PIXEL){
				newr=MAX_PIXEL;}
			if(newg<0){
                                newg=0;}
                        if(newg>MAX_PIXEL){
                                newg=MAX_PIXEL;}
			if(newb<0){
                                newb=0;}
                        if(newb>MAX_PIXEL){
                                newb=MAX_PIXEL;}		
		
			//type cast to unsigned char		
                        SetPixelR(image, x, y,(unsigned char) newr);
                        SetPixelG(image, x, y,(unsigned char) newg);
                        SetPixelB(image, x, y,(unsigned char) newb);
   }}

	return image;
	}

//Resize the image to a certain percentage

IMAGE *Resize(IMAGE *image, int percentage){
	assert(image);
        int widthnew,heightnew,widthold,heightold;
        unsigned char pixelR,pixelG,pixelB;
	//unsigned char newR,newG,newB;
	float avgR=0,avgG=0,avgB=0,sumR=0,sumG=0,sumB=0;
	int oldx,oldy;
	int x,y,x1,x2,y1,y2;   
	widthold=ImageWidth(image);
	heightold=ImageHeight(image);
        if(percentage==100){
		return image;
	
	}
	IMAGE *outputImage = NULL;
	

	if(percentage>100){
		
		widthnew=widthold*(percentage/100.00);
		heightnew=heightold*(percentage/100.00);
		
		outputImage=CreateImage(widthnew,heightnew);
		
	        for (y = 0; y < heightnew; y++) {
		        for (x = 0; x < widthnew; x++) {
				//Duplicate some pixels from old image to new image
				oldx=x/(percentage/100.00);
				oldy=y/(percentage/100.00);

							
			        pixelR=GetPixelR(image,oldx,oldy);
				pixelG=GetPixelG(image,oldx,oldy);
				pixelB=GetPixelB(image,oldx,oldy);
				
				
				SetPixelR(outputImage,x,y,pixelR);
				SetPixelG(outputImage,x,y,pixelG);
				SetPixelB(outputImage,x,y,pixelB);
			}
		}

		DeleteImage(image);
		image=NULL;
		return outputImage;

		}

	if(percentage<100){
		

                widthnew=widthold*(percentage/100.00);
                heightnew=heightold*(percentage/100.00);

		outputImage=CreateImage(widthnew,heightnew);

                
                for (y = 0; y < heightnew; y++) {

                        for (x = 0; x < widthnew; x++) {

				x1=x/(percentage/100.00);
				y1=y/(percentage/100.00);
				x2=(x+1)/(percentage/100.00);
				y2=(y+1)/(percentage/100.00);

				//Loop through the range of old x and y to average the				      //pixels for new smaller image
				for(int h=y1;h<y2;h++){
					for(int z=x1;z<x2;z++){
					

						pixelR=GetPixelR(image,z,h);
						sumR=sumR+pixelR;
						pixelG=GetPixelG(image,z,h);
                                                sumG=sumG+pixelG;

						pixelB=GetPixelB(image,z,h);
                                                sumB=sumB+pixelB;
						
					        
						}
					}
				avgR=sumR/((x2-x1)*(y2-y1));
				avgG=sumG/((x2-x1)*(y2-y1));
				avgB=sumB/((x2-x1)*(y2-y1));

				sumR=0;
                                sumG=0;
                                sumB=0;


	


				SetPixelR(outputImage,x,y,(unsigned char)avgR);
				SetPixelG(outputImage,x,y,(unsigned char)avgG);
				SetPixelB(outputImage,x,y,(unsigned char)avgB);

	
		
                                
                        }
                }
		DeleteImage(image);
		image=NULL;
		return outputImage;
	}
	else{
		return image;}
	
}
//Rotate the image	
IMAGE *Rotate(IMAGE *image, int option){
	assert(image);
	unsigned char pixelR,pixelG,pixelB;
		
        unsigned int width, height;
        height=ImageHeight(image);
        width=ImageWidth(image);
	
	IMAGE *outputImage = NULL;
        
//Horizontal flip
	if (option==1){	
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width/2; x++) {

		               pixelR=GetPixelR(image,x,y);
			       pixelG=GetPixelG(image,x,y);
			       pixelB=GetPixelB(image,x,y);

			       SetPixelR(image,x,y,GetPixelR(image,width-1-x,y));
			       SetPixelG(image,x,y,GetPixelG(image,width-1-x,y));
			       SetPixelB(image,x,y,GetPixelB(image,width-1-x,y));

			      
			       SetPixelR(image,width-1-x,y,pixelR);
			       SetPixelG(image,width-1-x,y,pixelG);
			       SetPixelB(image,width-1-x,y,pixelB);

				}
			}
		return image;
	}			
	
//Vertical Flip
	else if(option==2){

                for (int y = 0; y < height/2; y++) {
                        for (int x = 0; x < width; x++) {

                               pixelR=GetPixelR(image,x,y);
                               pixelG=GetPixelG(image,x,y);
                               pixelB=GetPixelB(image,x,y);

                               SetPixelR(image,x,y,GetPixelR(image,x,height-1-y));
                               SetPixelG(image,x,y,GetPixelG(image,x,height-1-y));
                               SetPixelB(image,x,y,GetPixelB(image,x,height-1-y));


                               SetPixelR(image,x,height-1-y,pixelR);
                               SetPixelG(image,x,height-1-y,pixelG);
                               SetPixelB(image,x,height-1-y,pixelB);

                                }
                        }


                

	return image;
	}


//Rotate right
        else if (option==3){

                outputImage = CreateImage(height,width);
                for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                                pixelR=GetPixelR(image,x,y);
                                pixelG=GetPixelG(image,x,y);
                                pixelB=GetPixelB(image,x,y);



                                SetPixelR(outputImage,height-1-y,x,pixelR);
                                SetPixelG(outputImage,height-1-y,x,pixelG);
                                SetPixelB(outputImage,height-1-y,x,pixelB);



                                }
                        }
                DeleteImage(image);
                image=NULL;
                return outputImage;
		}
//Rotate left
	else if (option==4){
		
		outputImage = CreateImage(height,width);	
                for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                                pixelR=GetPixelR(image,x,y);
                                pixelG=GetPixelG(image,x,y);
                                pixelB=GetPixelB(image,x,y);

				

                                SetPixelR(outputImage,y,width-1-x,pixelR);
				SetPixelG(outputImage,y,width-1-x,pixelG);
				SetPixelB(outputImage,y,width-1-x,pixelB);

                        

                                }
                        }
		DeleteImage(image);
		image=NULL;
		return outputImage;
	
	}

		
	else{return image;}
	//return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
