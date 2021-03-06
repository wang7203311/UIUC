#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mp8.h"


/*
 * basicFlood -- wrapper for flood filling recursively from a point until
 *               reaching black or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
/*clear the marking array first and then go to the recurse function to mark the pixel.
THen fill the pixel with color row by row*/
void
basicFlood (int32_t width, int32_t height,
	    const uint8_t* inRed, const uint8_t* inGreen,
	    const uint8_t* inBlue,
	    int32_t startX, int32_t startY,
	    uint8_t floodR, uint8_t floodG, uint8_t floodB,
	    uint8_t* outRed, uint8_t* outGreen,
	    uint8_t* outBlue)
{
		int i; //height
		int j; //Width
	 memset(outRed, 0, width*height*sizeof(outRed[0])); //clear the array for marking
	 basicRecurse(width, height, inRed, inGreen, inBlue, startX , startY, outRed); //go to recurse function
	 	//after marking and fill every pixel
   for(i = 0; i < height; i++)			//check the height
	 	{
			for(j = 0; j < width; j++)		//check the width
			 {
				 if(outRed[j + i*width] == 1)   //check if the pixel is marked, if yes, fill the flood color
				 {
					 outRed[j + i*width] = floodR;			//fill the floodR
					 outGreen[j + i*width] = floodG;		//fill the floodG
					 outBlue [j + i*width] = floodB;		//fill the floodB
				 }
				 else		//if the pixel is not marked. fill the original color
				 {
					outRed[j + i*width] = inRed[j + i*width];		//fill the original red
				  outGreen[j + i*width] = inGreen[j + i*width];	//fill the original green
					outBlue [j + i*width] = inBlue[j + i*width]; //fill the orginal blue
				 }
			 }
		}
}


/*
 * colorsWithinDistSq -- returns 1 iff two colors are within Euclidean
 *                       distance squared of one another in RGB space
 * INPUTS: r1 -- red component of color 1
 *         g1 -- green component of color 1
 *         b1 -- blue component of color 1
 *         r2 -- red component of color 2
 *         g2 -- green component of color 2
 *         b2 -- blue component of color 2
 *         distSq -- maximum distance squared for the check
 * RETURN VALUE: 1 if the sum of the squares of the differences in the
 *               three components is less or equal to distSq; 0 otherwise
 * SIDE EFFECTS: none
 */
/*calculate the distance square and then compare it with distSq, if it is smaller than distSq means
it is close to that color*/
int32_t
colorsWithinDistSq (uint8_t r1, uint8_t g1, uint8_t b1,
                    uint8_t r2, uint8_t g2, uint8_t b2, uint32_t distSq)
{
		uint32_t red_dist = r1 - r2;  //find the diffrence in red component
		uint32_t green_dist = g1 - g2;	//find the difference in green component
		uint32_t blue_dist = b1- b2;	// find the difference in blue component
		uint32_t sum = red_dist*red_dist + green_dist*green_dist +blue_dist*blue_dist;	//find the sum distance square
		if (sum <= distSq)	//compare with distSq
		   {
				 return 1;		//if it is smaller than distSq return 1
			 }
		else
		  {
				return 0;			// if not, return 0
			}
}


/*
 * greyFlood -- wrapper for flood filling recursively from a point until
 *              reaching near-black pixels or the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 *         distSq -- maximum distance squared between black and boundary
 *                   pixel color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
 /*clear the marking array first and then go to the recurse function to mark the pixel.
 THen fill the pixel with color row by row*/
void
greyFlood (int32_t width, int32_t height,
	   const uint8_t* inRed, const uint8_t* inGreen,
	   const uint8_t* inBlue,
	   int32_t startX, int32_t startY,
	   uint8_t floodR, uint8_t floodG, uint8_t floodB, uint32_t distSq,
	   uint8_t* outRed, uint8_t* outGreen,
	   uint8_t* outBlue)
{
		int i; //height
		int j; //width
		memset(outRed, 0, width*height*sizeof(outRed[0])); //clear the array for marking
		greyRecurse(width, height, inRed, inGreen, inBlue, startX, startY,distSq, outRed); // go to recurese function
		//after marking, go to recurse function
		for(i =0; i < height; i++)			//check the height
		{
			for(j =0; j < width; j++)			//check the width
			{
				if(outRed[j+i*width] == 1) //if the pixel is marked, fill the flood color
				 {
					 outRed[j+i*width] =floodR;	//fill with floodR
					 outGreen[j+i*width] = floodG;	//fill with floodG
					 outBlue[j+i*width] = floodB;		//fill with floodG
				 }
				 else //if not, fill the original color
				 {
					 outRed[j+i*width] =inRed[j+i*width]; 		//fill original red
					 outGreen[j+i*width] = inGreen[j+i*width];//fill original green
					 outBlue[j+i*width] = inBlue[j+i*width]; //fill original blue
				 }
			}
		}
}


/*
 * limitedFlood -- wrapper for flood filling recursively from a point until
 *                 reaching pixels too different (in RGB color) from the
 *                 color at the flood start point, too far away
 *                 (> 40 pixels), or beyond the image border
 * INPUTS: width -- width of the input image
 *         height -- height of the input image
 *         inRed -- pointer to the input red channel (1-D array)
 *         inGreen -- pointer to the input green channel (1-D array)
 *         inBlue -- pointer to the input blue channel (1-D array)
 *         startX -- starting x position of the flood
 *         startY -- starting y position of the flood
 *         floodR -- red component of the flood color
 *         floodG -- green component of the flood color
 *         floodB -- blue component of the flood color
 *         distSq -- maximum distance squared between pixel at origin
 *                   and boundary pixel color
 * OUTPUTS: outRed -- pointer to the output red channel (1-D array)
 *          outGreen -- pointer to the output green channel (1-D array)
 *          outBlue -- pointer to the output blue channel (1-D array)
 * RETURN VALUE: none
 * SIDE EFFECTS: none
 */
 /*clear the marking array first and then go to the recurse function to mark the pixel.
 THen fill the pixel with color row by row*/
void
limitedFlood (int32_t width, int32_t height,
	      const uint8_t* inRed, const uint8_t* inGreen,
	      const uint8_t* inBlue,
	      int32_t startX, int32_t startY,
	      uint8_t floodR, uint8_t floodG, uint8_t floodB, uint32_t distSq,
	      uint8_t* outRed, uint8_t* outGreen,
	      uint8_t* outBlue)
{
	int i;//height
	int j;//width
	memset(outRed, 0, width*height*sizeof(outRed[0])); //clear the array for marking
	limitedRecurse(width, height, inRed, inGreen, inBlue, startX, startY, startX, startY,distSq, outRed); //go to recurse function
	//after marking, fill the pixel color
	for(i =0; i < height; i++)		//check the height
	 {
		 for(j =0; j <width; j++)   //check the width
		 {
			 if(outRed[j+i*width] == 1)		//check if the pixel is marked, if yes, fill flood color
			 {
				 outRed[j+i*width] = floodR;		//fill floodR
				 outGreen[j+i*width] = floodG; //fill floodG
				 outBlue[j+i*width] = floodB; //fill floodB
			 }
			 else				//if not, fill the original color
			 {
				 outRed[j+i*width] = inRed[j+i*width];  //fill original red
				 outGreen[j+i*width] = inGreen[j+i*width]; //fill original green
				 outBlue[j+i*width] = inBlue[j+i*width]; // fill original blue
			 }
		 }

		 }
}
