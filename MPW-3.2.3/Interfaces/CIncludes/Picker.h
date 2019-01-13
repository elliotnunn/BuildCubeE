/************************************************************

Created: Friday, October 20, 1989 at 9:00 AM
	Picker.h
	C Interface to the Macintosh Libraries


	Copyright Apple Computer, Inc.	1987-1989
	All rights reserved

************************************************************/


#ifndef __PICKER__
#define __PICKER__

#ifndef __QUICKDRAW__
#include <Quickdraw.h>
#endif

enum {MaxSmallFract = 0x0000FFFF};  /*Maximum small fract value, as long*/


/* A SmallFract value is just the fractional part of a Fixed number,
which is the low order word.  SmallFracts are used to save room,
and to be compatible with Quickdraw's RGBColor.  They can be
assigned directly to and from INTEGERs. */

typedef unsigned short SmallFract;	/* Unsigned fraction between 0 and 1 */

/* For developmental simplicity in switching between the HLS and HSV
models, HLS is reordered into HSL.	Thus both models start with
hue and saturation values; value/lightness/brightness is last. */



struct HSVColor {
	SmallFract hue; 				/*Fraction of circle, red at 0*/
	SmallFract saturation;			/*0-1, 0 for gray, 1 for pure color*/
	SmallFract value;				/*0-1, 0 for black, 1 for max intensity*/
};

typedef struct HSVColor HSVColor;
/* For developmental simplicity in switching between the HLS and HSVmodels, HLS
 is reordered into HSL.  Thus both models start with hue and saturation values;
 value/lightness/brightness is last. */
struct HSLColor {
	SmallFract hue; 				/*Fraction of circle, red at 0*/
	SmallFract saturation;			/*0-1, 0 for gray, 1 for pure color*/
	SmallFract lightness;			/*0-1, 0 for black, 1 for white*/
};

typedef struct HSLColor HSLColor;
struct CMYColor {
	SmallFract cyan;
	SmallFract magenta;
	SmallFract yellow;
};

typedef struct CMYColor CMYColor;
#ifdef __cplusplus
extern "C" {
#endif
pascal SmallFract Fix2SmallFract(Fixed f)
	= {0x3F3C,0x0001,0xA82E};
pascal Fixed SmallFract2Fix(SmallFract s)
	= {0x3F3C,0x0002,0xA82E};
pascal void CMY2RGB(const CMYColor *cColor,RGBColor *rColor)
	= {0x3F3C,0x0003,0xA82E};
pascal void RGB2CMY(const RGBColor *rColor,CMYColor *cColor)
	= {0x3F3C,0x0004,0xA82E};
pascal void HSL2RGB(const HSLColor *hColor,RGBColor *rColor)
	= {0x3F3C,0x0005,0xA82E};
pascal void RGB2HSL(const RGBColor *rColor,HSLColor *hColor)
	= {0x3F3C,0x0006,0xA82E};
pascal void HSV2RGB(const HSVColor *hColor,RGBColor *rColor)
	= {0x3F3C,0x0007,0xA82E};
pascal void RGB2HSV(const RGBColor *rColor,HSVColor *hColor)
	= {0x3F3C,0x0008,0xA82E};
pascal Boolean GetColor(Point where,ConstStr255Param prompt,const RGBColor *inColor,
	RGBColor *outColor)
	= {0x3F3C,0x0009,0xA82E};
#ifdef __cplusplus
}
#endif

#endif
