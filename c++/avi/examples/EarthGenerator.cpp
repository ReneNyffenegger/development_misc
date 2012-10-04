/* 
   EarthGenerator.cpp


   g++ -I.. -I../../../windows/w -I../../../windows    ../AviMemDC.cpp  ../avi.cpp EarthGenerator.cpp ../../../windows/w/DibSection.cpp ../../../windows/w/MemoryDC.cpp  ../../../windows/w/bitmap.cpp ../../../windows/w/DC.cpp ../../../windows/w/Color.cpp  ../../../windows/w/Font.cpp  ../../../windows/Win32_LastError.cpp -o EarthGenerator.exe -lvfw32 -lgdi32

   An example on how to use AviMemDC.cpp

   Copyright (c) 1998-2003 Torben AE. Mogensen
   Copyright (c) 2004,2005 René Nyffenegger

   All algorithms and source code pertaining to generating a random earth surface
   are Copyright by Torben AE. Mogensen

   The rest, that is the movie functionality, was added by René Nyffenegger

   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.

   3. This notice may not be removed or altered from any source distribution.

   René Nyffenegger rene.nyffenegger@adp-gmbh.ch
*/

#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include <windows.h>

#include "AviMemDC.h"

int planet0(double x,double y,double z);
double planet1(double x,double y,double z);
double log_2(double x) { return(log(x)/log(2.0)); }
double rand2(double p,double q);

#define BLACK 0
#define WHITE 1
#define BLUE0 2

int altColors = 0;

int BLUE1, LAND0, LAND1, LAND2, LAND4;
int GREEN1, BROWN0, GREY0;

int BACK = BLACK;

int black_r = 0,    black_g = 0,    black_b = 0;
int white_r = 255,  white_g = 255,  white_b = 255;

#define MAXCOL  9
typedef int CTable[MAXCOL][3];

CTable  colors =
      {{0,0,255},      /* Dark blue depths      */
       {0,128,255},    /* Light blue shores     */
       {0,255,0},      /* Light green lowlands  */
       {64,192,16},    /* Dark green highlands  */
       {64,192,16},    /* Dark green Mountains  */
       {128,128,32},   /* Brown stoney peaks    */
       {255,255,255},  /* White - peaks         */
       {0,0,0},        /* Black - Space         */
       {0,0,0}};       /* Black - Lines         */

int nocols = 256;

int rtable[256], gtable[256], btable[256];

int lighter = 0; /* specifies lighter colours */


typedef enum ftype { bmp, ppm, xpm } ftype;
    
ftype file_type = bmp;

char* file_ext(ftype file_type) {
  switch (file_type)
  {
    case bmp:
      return (".bmp");
    case ppm:
      return (".ppm");
    case xpm:
      return (".xpm");
    default:
      return ("");
  }
}

/* Character table for XPM output */

char letters[64] = {
  '@','$','.',',',':',';','-','+','=','#','*','&','A','B','C','D',
  'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
  'U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j',
  'k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

#define PI 3.14159265358979
#define DEG2RAD 0.0174532918661 /* pi/180 */

/* these three values can be changed to change world characteristica */

double M  = -.02;   /* initial altitude (slightly below sea level) */
double dd1 = 0.4;   /* weight for altitude difference */
double dd2 = 0.03;  /* weight for distance */
double POW = 0.47;  /* power for distance function */

int Depth; /* depth of subdivisions */
double r1,r2,r3,r4; /* seeds */
double longi,lat,scale;
double vgrid, hgrid;

int latic = 0; /* flag for latitude based colour */

int Width = 80, Height = 60;

unsigned char **col;
int **heights;
int cl0[60][30];

int do_bw = 0;
int *outx, *outy;

int doshade = 0;
int shade;
unsigned char **shades;
double shade_angle = 150.0; /* angle of "light" on bumpmap */

double moll_table[] = {0.0, 0.0685055811, 0.1368109534, 0.2047150027,
           0.2720147303, 0.3385041213, 0.4039727534,
           0.4682040106, 0.5309726991, 0.5920417499,
           0.6511575166, 0.7080428038, 0.7623860881,
           0.8138239166, 0.8619100185, 0.9060553621,
           0.9453925506, 0.9783738403, 1.0};

double cla, sla, clo, slo;

int best = 500000;
int weight[30];

int min(int x, int y) { return(x<y ? x : y); }
int max(int x, int y) { return(x<y ? y : x); }

double fmin(double x,double y) { return(x<y ? x : y); }
double fmax(double x,double y) { return(x<y ? y : x); }


void setcolours() {
  int i;

  if (altColors) {
      
    if (nocols < 8)
      nocols = 8;
  
    /*
     *  This color table tries to follow the coloring conventions of
     *  several atlases.
     *
     *  The first two colors are reserved for black and white
     *  1/4 of the colors are blue for the sea, dark being deep
     *  3/4 of the colors are land, divided as follows:
     *   nearly 1/2 of the colors are greens, with the low being dark
     *   1/8 of the colors shade from green through brown to grey
     *   1/8 of the colors are shades of grey for the highest altitudes
     *
     *  The minimum color table is:
     *      0  Black
     *      1  White
     *      2  Blue
     *      3  Dark Green
     *      4  Green
     *      5  Light Green
     *      6  Brown
     *      7  Grey
     *  and doesn't look very good. Somewhere between 24 and 32 colors
     *  is where this scheme starts looking good. 256, of course, is best.
     */
    
    LAND0 = max(nocols / 4, BLUE0 + 1);
    BLUE1 = LAND0 - 1;
    GREY0 = nocols - (nocols / 8);
    GREEN1 = min(LAND0 + (nocols / 2), GREY0 - 2);
    BROWN0 = (GREEN1 + GREY0) / 2;
    LAND1 = nocols - 1;

    rtable[BLACK] = colors[7][0];
    gtable[BLACK] = colors[7][0];
    btable[BLACK] = colors[7][0];

    rtable[WHITE] = colors[6][0];
    gtable[WHITE] = colors[6][1];
    btable[WHITE] = colors[6][2];

    rtable[BLUE0] = colors[0][0];
    gtable[BLUE0] = colors[0][1];
    btable[BLUE0] = colors[0][2];

    for (i=BLUE0+1;i<=BLUE1;i++) {
      rtable[i] = (colors[0][0]*(BLUE1-i)+colors[1][0]*(i-BLUE0))/(BLUE1-BLUE0);
      gtable[i] = (colors[0][1]*(BLUE1-i)+colors[1][1]*(i-BLUE0))/(BLUE1-BLUE0);
      btable[i] = (colors[0][2]*(BLUE1-i)+colors[1][2]*(i-BLUE0))/(BLUE1-BLUE0);
    }
    for (i=LAND0;i<GREEN1;i++) {
      rtable[i] = (colors[2][0]*(GREEN1-i)+colors[3][0]*(i-LAND0))/(GREEN1-LAND0);
      gtable[i] = (colors[2][1]*(GREEN1-i)+colors[3][1]*(i-LAND0))/(GREEN1-LAND0);
      btable[i] = (colors[2][2]*(GREEN1-i)+colors[3][2]*(i-LAND0))/(GREEN1-LAND0);
    }
    for (i=GREEN1;i<BROWN0;i++) {
      rtable[i] = (colors[3][0]*(BROWN0-i)+colors[4][0]*(i-GREEN1))/(BROWN0-GREEN1);
      gtable[i] = (colors[3][1]*(BROWN0-i)+colors[4][1]*(i-GREEN1))/(BROWN0-GREEN1);
      btable[i] = (colors[3][2]*(BROWN0-i)+colors[4][2]*(i-GREEN1))/(BROWN0-GREEN1);
    }
    for (i=BROWN0;i<GREY0;i++) {
      rtable[i] = (colors[4][0]*(GREY0-i)+colors[5][0]*(i-BROWN0))/(GREY0-BROWN0);
      gtable[i] = (colors[4][1]*(GREY0-i)+colors[5][1]*(i-BROWN0))/(GREY0-BROWN0);
      btable[i] = (colors[4][2]*(GREY0-i)+colors[5][2]*(i-BROWN0))/(GREY0-BROWN0);
    }
    for (i=GREY0;i<nocols;i++) {
      rtable[i] = (colors[5][0]*(nocols-i)+(colors[6][0]+1)*(i-GREY0))/(nocols-GREY0);
      gtable[i] = (colors[5][1]*(nocols-i)+(colors[6][1]+1)*(i-GREY0))/(nocols-GREY0);
      btable[i] = (colors[5][2]*(nocols-i)+(colors[6][2]+1)*(i-GREY0))/(nocols-GREY0);
    }
  } else {
    rtable[BLACK] = 0;
    gtable[BLACK] = 0;
    btable[BLACK] = 0;
  
    rtable[WHITE] = 255;
    gtable[WHITE] = 255;
    btable[WHITE] = 255;
  
    while (lighter-->0) {
      int r, c;
      double x;

      for (r =  0; r < 7; r++)
  for (c = 0; c < 3; c++) {
    x = sqrt((double)colors[r][c]/256.0);
    colors[r][c] = (int)(240.0*x+16);
  }
    }
  
    BLUE1 = (nocols-4)/2+BLUE0;
    if (BLUE1==BLUE0) {
      rtable[BLUE0] = colors[0][0];
      gtable[BLUE0] = colors[0][1];
      btable[BLUE0] = colors[0][2];
    } else
      for (i=BLUE0;i<=BLUE1;i++) {
        rtable[i] = (colors[0][0]*(BLUE1-i)+colors[1][0]*(i-BLUE0))/(BLUE1-BLUE0);
        gtable[i] = (colors[0][1]*(BLUE1-i)+colors[1][1]*(i-BLUE0))/(BLUE1-BLUE0);
        btable[i] = (colors[0][2]*(BLUE1-i)+colors[1][2]*(i-BLUE0))/(BLUE1-BLUE0);
      }
    LAND0 = BLUE1+1; LAND2 = nocols-2; LAND1 = (LAND0+LAND2+1)/2;
    for (i=LAND0;i<LAND1;i++) {
      rtable[i] = (colors[2][0]*(LAND1-i)+colors[3][0]*(i-LAND0))/(LAND1-LAND0);
      gtable[i] = (colors[2][1]*(LAND1-i)+colors[3][1]*(i-LAND0))/(LAND1-LAND0);
      btable[i] = (colors[2][2]*(LAND1-i)+colors[3][2]*(i-LAND0))/(LAND1-LAND0);
    }
    if (LAND1==LAND2) {
      rtable[LAND1] = colors[4][0];
      gtable[LAND1] = colors[4][1];
      btable[LAND1] = colors[4][2];
    } else
      for (i=LAND1;i<=LAND2;i++) {
  rtable[i] = (colors[4][0]*(LAND2-i)+colors[5][0]*(i-LAND1))/(LAND2-LAND1);
  gtable[i] = (colors[4][1]*(LAND2-i)+colors[5][1]*(i-LAND1))/(LAND2-LAND1);
  btable[i] = (colors[4][2]*(LAND2-i)+colors[5][2]*(i-LAND1))/(LAND2-LAND1);
      }
    LAND4 = nocols-1;
    rtable[LAND4] = colors[6][0];
    gtable[LAND4] = colors[6][1];
    btable[LAND4] = colors[6][2];
  }
}

void makeoutline(int do_bw) {
  int i,j,k;

  outx = (int*)calloc(Width*Height,sizeof(int));
  outy = (int*)calloc(Width*Height,sizeof(int));
  k=0;
  for (i=1; i<Width-1; i++)
    for (j=1; j<Height-1; j++)
      if ((col[i][j] >= BLUE0 && col[i][j] <= BLUE1) &&
    (col[i-1][j] >= LAND0 || col[i+1][j] >= LAND0 ||
     col[i][j-1] >= LAND0 || col[i][j+1] >= LAND0 ||
     col[i-1][j-1] >= LAND0 || col[i-1][j+1] >= LAND0 ||
     col[i+1][j-1] >= LAND0 || col[i+1][j+1] >= LAND0)) {
  outx[k] = i; outy[k++] =j;
      }
  if (do_bw)
    for (i=0; i<Width; i++)
      for (j=0; j<Height; j++)
  if (col[i][j] != BLACK) col[i][j] = WHITE;
  while (k-->0) col[outx[k]][outy[k]] = BLACK;
}

void readmap()
{
  int i,j;
  double y;
  char c;

  Width = 47; Height = 21;
  for (j = 0; j < Height; j++) {
    y = 0.5*7.5*(2.0*j-Height+1);
    y = cos(DEG2RAD*y);
    weight[j] = (int)(100.0*y+0.5);
  }
  for (j = 0; j < Height; j+=2) {
    for(i = 0; i < Width ; i+=2) {
      c = getchar();
      switch (c) {
      case '.': cl0[i][j] = -8;
    break;
      case ',': cl0[i][j] = -4;
    break;
      case ':': cl0[i][j] = -2;
    break;
      case ';': cl0[i][j] = -1;
    break;
      case '-': cl0[i][j] = 0;
    break;
      case '*': cl0[i][j] = 1;
    break;
      case 'o': cl0[i][j] = 2;
    break;
      case 'O': cl0[i][j] = 4;
    break;
      case '@': cl0[i][j] = 8;
    break;
      default: printf("Wrong map symbol: %c\n",c);
      }
      if (i>0) cl0[i-1][j] = (cl0[i][j]+cl0[i-2][j])/2;
    }
    c = getchar(); if (c!='\n') printf("Wrong map format: %c\n",c);
  }
  for (j = 1; j < Height; j+=2)
    for(i = 0; i < Width ; i++)
      cl0[i][j] = (cl0[i][j-1]+cl0[i][j+1])/2;
}
void smoothshades() {
  int i,j;

  for (i=0; i<Width-2; i++)
    for (j=0; j<Height-2; j++)
      shades[i][j] = (4*shades[i][j]+2*shades[i][j+1]
          +2*shades[i+1][j]+shades[i+1][j+2]+4)/9;
}

void orthographic() {
  double x,y,z,x1,y1,z1,ymin,ymax,theta1,theta2,zz;
  int i,j;

  ymin = 2.0;
  ymax = -2.0;
  for (j = 0; j < Height; j++) {
    printf(".");
    
    for (i = 0; i < Width ; i++) {
      x = (2.0*i-Width)/Height/scale;
      y = (2.0*j-Height)/Height/scale;
      if (x*x+y*y>1.0) {
        col[i][j] = BACK;
        if (doshade) shades[i][j] = 255;
      } 
      else {

  z = sqrt(1.0-x*x-y*y);
  x1 = clo*x+slo*sla*y+slo*cla*z;
  y1 = cla*y-sla*z;
  z1 = -slo*x+clo*sla*y+clo*cla*z;
  if (y1 < ymin) ymin = y1;
  if (y1 > ymax) ymax = y1;
  col[i][j] = planet0(x1,y1,z1);
  if (doshade) shades[i][j] = shade;
      }
    }
  }
  if (hgrid != 0.0) { /* draw horisontal gridlines */
    for (theta1 = 0.0; theta1>-90.0; theta1-=hgrid);
    for (theta1 = theta1; theta1<90.0; theta1+=hgrid) {
      y = sin(DEG2RAD*theta1);
      if (ymin <= y && y <= ymax) {
  zz = sqrt(1-y*y);
  for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
    x = sin(theta2)*zz;
    z = cos(theta2)*zz;
    x1 = clo*x+slo*z;
    y1 = slo*sla*x+cla*y-clo*sla*z;
    z1 = -slo*cla*x+sla*y+clo*cla*z;
    if (0.0>=z1){
      i = static_cast<int> (0.5*(Height*scale*x1+Width));
      j = static_cast<int> (0.5*(Height*scale*y1+Height));
      if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
    }
  }
      }
    }
  }
  if (vgrid != 0.0) { /* draw vertical gridlines */
    for (theta2=-PI; theta2<PI; theta2+=0.5/Width/scale) {
      y = sin(theta2);
      if (ymin <= y && y <= ymax) {
  for (theta1 = 0.0; theta1<360.0; theta1+=vgrid) {
    x = sin(DEG2RAD*theta1)*cos(theta2);
    z = cos(DEG2RAD*theta1)*cos(theta2);
    x1 = clo*x+slo*z;
    y1 = slo*sla*x+cla*y-clo*sla*z;
    z1 = -slo*cla*x+sla*y+clo*cla*z;
    if (0.0>=z1){
      i = static_cast<int> (0.5*(Height*scale*x1+Width));
      j = static_cast<int> (0.5*(Height*scale*y1+Height));
      if (0<=i && i<Width && 0<=j && j<Height) col[i][j] = BLACK;
    }
  }
      }
    }
  }
}

int planet0(double x,double y,double z) {
  double alt;
  int colour;

  alt = planet1(x,y,z);

  if (altColors) {
    double snow = .125;
    double tree = snow * 0.5;
    double bare = (tree + snow) / 2.;
    
    if (latic) {
      snow -= (.13 * (y*y*y*y*y*y));
      bare -= (.12 * (y*y*y*y*y*y));
      tree -= (.11 * (y*y*y*y*y*y));
    }
    
    if (alt > 0) {        /* Land */
      if (alt > snow) {        /* Snow: White */
  colour = WHITE;
      } else if (alt > bare) {      /* Snow: Grey - White */
  colour = GREY0+(int)((1+LAND1-GREY0) *
            (alt-bare)/(snow-bare));
  if (colour > LAND1) colour = LAND1;
      } else if (alt > tree) {      /* Bare: Brown - Grey */
  colour = GREEN1+(int)((1+GREY0-GREEN1) *
            (alt-tree)/(bare-tree));
  if (colour > GREY0) colour = GREY0;
      } else {          /* Green: Green - Brown */
  colour = LAND0+(int)((1+GREEN1-LAND0) *
            (alt)/(tree));
  if (colour > GREEN1) colour = GREEN1;
      }
    } else {          /* Sea */
      alt = alt/2;
      if (alt > snow) {        /* Snow: White */
  colour = WHITE;
      } else if (alt > bare) {
  colour = GREY0+(int)((1+LAND1-GREY0) *
            (alt-bare)/(snow-bare));
  if (colour > LAND1) colour = LAND1;
      } else {
  colour = BLUE1+(int)((BLUE1-BLUE0+1)*(25*alt));
  if (colour<BLUE0) colour = BLUE0;
      }
    }
  } else {
  /* calculate colour */
    if (alt <=0.) { /* if below sea level then */
      if (latic && y*y+alt >= 0.98)
  colour = LAND4;   /* white if close to poles */
      else {
  colour = BLUE1+(int)((BLUE1-BLUE0+1)*(10*alt));    /* blue scale otherwise */
  if (colour<BLUE0) colour = BLUE0;
      }
    }
    else {
      if (latic) alt += 0.10204*y*y;  /* altitude adjusted with latitude */
      if (alt >= 0.1) /* if high then */
  colour = LAND4;
      else {
  colour = LAND0+(int)((LAND2-LAND0+1)*(10*alt));
        /* else green to brown scale */
  if (colour>LAND2) colour = LAND2;
      }
    }
  }
  return(colour);
}

double ssa,ssb,ssc,ssd, ssas,ssbs,sscs,ssds, ssax,ssay,ssaz, ssbx,ssby,ssbz, sscx,sscy,sscz, ssdx,ssdy,ssdz;

double planet(double a,double b,double c,double d, double as,double bs,double cs,double ds,
        double ax,double ay,double az, double bx,double by,double bz, double cx,double cy,double cz, double dx,double dy,double dz,
        double x,double y,double z, int level)
{
  double abx,aby,abz, acx,acy,acz, adx,ady,adz;
  double bcx,bcy,bcz, bdx,bdy,bdz, cdx,cdy,cdz;
  double lab, lac, lad, lbc, lbd, lcd;
  double ex, ey, ez, e, es, es1, es2, es3;
  double eax,eay,eaz, epx,epy,epz;
  double ecx,ecy,ecz, edx,edy,edz;
  double x1,y1,z1,x2,y2,z2,l1,tmp;

  if (level>0) {
    if (level==11) {
      ssa=a; ssb=b; ssc=c; ssd=d; ssas=as; ssbs=bs; sscs=cs; ssds=ds;
      ssax=ax; ssay=ay; ssaz=az; ssbx=bx; ssby=by; ssbz=bz;
      sscx=cx; sscy=cy; sscz=cz; ssdx=dx; ssdy=dy; ssdz=dz;
    }
    abx = ax-bx; aby = ay-by; abz = az-bz;
    acx = ax-cx; acy = ay-cy; acz = az-cz;
    lab = abx*abx+aby*aby+abz*abz;
    lac = acx*acx+acy*acy+acz*acz;

    if (lab<lac)
      return(planet(a,c,b,d, as,cs,bs,ds,
        ax,ay,az, cx,cy,cz, bx,by,bz, dx,dy,dz,
        x,y,z, level));
    else {
      adx = ax-dx; ady = ay-dy; adz = az-dz;
      lad = adx*adx+ady*ady+adz*adz;
      if (lab<lad)
  return(planet(a,d,b,c, as,ds,bs,cs,
          ax,ay,az, dx,dy,dz, bx,by,bz, cx,cy,cz,
          x,y,z, level));
      else {
  bcx = bx-cx; bcy = by-cy; bcz = bz-cz;
  lbc = bcx*bcx+bcy*bcy+bcz*bcz;
  if (lab<lbc)
    return(planet(b,c,a,d, bs,cs,as,ds,
      bx,by,bz, cx,cy,cz, ax,ay,az, dx,dy,dz,
      x,y,z, level));
  else {
    bdx = bx-dx; bdy = by-dy; bdz = bz-dz;
    lbd = bdx*bdx+bdy*bdy+bdz*bdz;
    if (lab<lbd)
      return(planet(b,d,a,c, bs,ds,as,cs,
        bx,by,bz, dx,dy,dz, ax,ay,az, cx,cy,cz,
        x,y,z, level));
    else {
      cdx = cx-dx; cdy = cy-dy; cdz = cz-dz;
      lcd = cdx*cdx+cdy*cdy+cdz*cdz;
      if (lab<lcd)
        return(planet(c,d,a,b, cs,ds,as,bs,
          cx,cy,cz, dx,dy,dz, ax,ay,az, bx,by,bz,
          x,y,z, level));
      else {
        es = rand2(as,bs);
        es1 = rand2(es,es);
        es2 = 0.5+0.1*rand2(es1,es1);
        es3 = 1.0-es2;
        if (ax==bx) { /* very unlikely to ever happen */
    ex = 0.5*ax+0.5*bx; ey = 0.5*ay+0.5*by; ez = 0.5*az+0.5*bz;
        } else if (ax<bx) {
    ex = es2*ax+es3*bx; ey = es2*ay+es3*by; ez = es2*az+es3*bz;
        } else {
    ex = es3*ax+es2*bx; ey = es3*ay+es2*by; ez = es3*az+es2*bz;
        }
        if (lab>1.0) lab = pow(lab,0.75);
        e = 0.5*(a+b)+es*dd1*fabs(a-b)+es1*dd2*pow(lab,POW);
        eax = ax-ex; eay = ay-ey; eaz = az-ez;
        epx =  x-ex; epy =  y-ey; epz =  z-ez;
        ecx = cx-ex; ecy = cy-ey; ecz = cz-ez;
        edx = dx-ex; edy = dy-ey; edz = dz-ez;
        if ((eax*ecy*edz+eay*ecz*edx+eaz*ecx*edy
       -eaz*ecy*edx-eay*ecx*edz-eax*ecz*edy)*
      (epx*ecy*edz+epy*ecz*edx+epz*ecx*edy
       -epz*ecy*edx-epy*ecx*edz-epx*ecz*edy)>0.0)
    return(planet(c,d,a,e, cs,ds,as,es,
            cx,cy,cz, dx,dy,dz, ax,ay,az, ex,ey,ez,
            x,y,z, level-1));
        else
    return(planet(c,d,b,e, cs,ds,bs,es,
            cx,cy,cz, dx,dy,dz, bx,by,bz, ex,ey,ez,
            x,y,z, level-1));
      }
    }
  }
      }
    } 
  }
  else {
    if (doshade) {
      x1 = 0.25*(ax+bx+cx+dx);
      x1 = a*(x1-ax)+b*(x1-bx)+c*(x1-cx)+d*(x1-dx);
      y1 = 0.25*(ay+by+cy+dy);
      y1 = a*(y1-ay)+b*(y1-by)+c*(y1-cy)+d*(y1-dy);
      z1 = 0.25*(az+bz+cz+dz);
      z1 = a*(z1-az)+b*(z1-bz)+c*(z1-cz)+d*(z1-dz);
    l1 = sqrt(x1*x1+y1*y1+z1*z1);
      if (l1==0.0) l1 = 1.0;
      tmp = sqrt(1.0-y*y);
      if (tmp<0.0001) tmp = 0.0001;
      x2 = x*x1+y*y1+z*z1;
      y2 = -x*y/tmp*x1+tmp*y1-z*y/tmp*z1;
      z2 = -z/tmp*x1+x/tmp*z1;
      shade =
  (int)((-sin(PI*shade_angle/180.0)*y2-cos(PI*shade_angle/180.0)*z2)
        /l1*48.0+128.0);
    if (shade<10) shade = 10;
    if (shade>255) shade = 255;
  }
    return((a+b+c+d)/4);
  }
}

double planet1(double x,double y,double z) {
  double abx,aby,abz, acx,acy,acz, adx,ady,adz, apx,apy,apz;
  double bax,bay,baz, bcx,bcy,bcz, bdx,bdy,bdz, bpx,bpy,bpz;

  abx = ssbx-ssax; aby = ssby-ssay; abz = ssbz-ssaz;
  acx = sscx-ssax; acy = sscy-ssay; acz = sscz-ssaz;
  adx = ssdx-ssax; ady = ssdy-ssay; adz = ssdz-ssaz;
  apx = x-ssax; apy = y-ssay; apz = z-ssaz;
  if ((adx*aby*acz+ady*abz*acx+adz*abx*acy
       -adz*aby*acx-ady*abx*acz-adx*abz*acy)*
      (apx*aby*acz+apy*abz*acx+apz*abx*acy
       -apz*aby*acx-apy*abx*acz-apx*abz*acy)>0.0){
    /* p is on same side of abc as d */
    if ((acx*aby*adz+acy*abz*adx+acz*abx*ady
   -acz*aby*adx-acy*abx*adz-acx*abz*ady)*
  (apx*aby*adz+apy*abz*adx+apz*abx*ady
   -apz*aby*adx-apy*abx*adz-apx*abz*ady)>0.0){
      /* p is on same side of abd as c */
      if ((abx*ady*acz+aby*adz*acx+abz*adx*acy
     -abz*ady*acx-aby*adx*acz-abx*adz*acy)*
    (apx*ady*acz+apy*adz*acx+apz*adx*acy
     -apz*ady*acx-apy*adx*acz-apx*adz*acy)>0.0){
  /* p is on same side of acd as b */
  bax = -abx; bay = -aby; baz = -abz;
  bcx = sscx-ssbx; bcy = sscy-ssby; bcz = sscz-ssbz;
  bdx = ssdx-ssbx; bdy = ssdy-ssby; bdz = ssdz-ssbz;
  bpx = x-ssbx; bpy = y-ssby; bpz = z-ssbz;
  if ((bax*bcy*bdz+bay*bcz*bdx+baz*bcx*bdy
       -baz*bcy*bdx-bay*bcx*bdz-bax*bcz*bdy)*
      (bpx*bcy*bdz+bpy*bcz*bdx+bpz*bcx*bdy
       -bpz*bcy*bdx-bpy*bcx*bdz-bpx*bcz*bdy)>0.0){
    /* p is on same side of bcd as a */
    /* Hence, p is inside tetrahedron */
    return(planet(ssa,ssb,ssc,ssd, ssas,ssbs,sscs,ssds,
      ssax,ssay,ssaz, ssbx,ssby,ssbz,
      sscx,sscy,sscz, ssdx,ssdy,ssdz,
      x,y,z, 11));
  }
      }
    }
  } /* otherwise */
  return(planet(M,M,M,M,
    /* initial altitude is M on all corners of tetrahedron */
    r1,r2,r3,r4,
         /* same seed set is used in every call */
    0.0, 0.0, 3.01,
    0.0, sqrt(8.0)+.01*r1*r1, -1.02+.01*r2*r3,
    -sqrt(6.0)-.01*r3*r3, -sqrt(2.0)-.01*r4*r4, -1.02+.01*r1*r2,
    sqrt(6.0)-.01*r2*r2, -sqrt(2.0)-.01*r3*r3, -1.02+.01*r1*r3,
    /* coordinates of vertices */
         x,y,z,
         /* coordinates of point we want colour of */
    Depth));
    /* subdivision depth */
}

double rand2(double p,double q) {
  double r;
  r = (p+3.14159265)*(q+3.14159265);
  return(2.*(r-(int)r)-1.);
}

char *nletters(int n, int c) {
  int i;
  static char buffer[8];
  
  buffer[n] = '\0';

  for (i = n-1; i >= 0; i--)
  {
    buffer[i] = letters[c & 0x001F];
    c >>= 5;
  }
  
  return buffer;
}

int main() {
  int i;
  double rseed;

  rseed = 0.123;
  r1 = rseed;

  r1 = rand2(r1,r1);
  r2 = rand2(r1,r1);
  r3 = rand2(r1,r2);
  r4 = rand2(r2,r3);

  longi = 0.0;
  lat   = 0.0;
  scale = 1.0;
  vgrid = hgrid = 0.0;

  AviMemDC a(Width, Height, "GeneratedEarth.avi", 5);
  printf("1\n");
  for (double r_longi = 0; r_longi< 360; r_longi+=1) {

    printf("r_longi: %f\n", r_longi);

    longi = r_longi;
    lat   = r_longi/2;
  
    if (longi>180) longi -= 360;
    longi = longi*DEG2RAD;
    lat = lat*DEG2RAD;

    sla = sin(lat); cla = cos(lat);
    slo = sin(longi); clo = cos(longi);

    col = (unsigned char**)calloc(Width,sizeof(unsigned char*));
    if (col == 0) {
      fprintf(stderr, "Memory allocation failed.");
      exit(1);
    }
    for (i=0; i<Width; i++) {
      col[i] = (unsigned char*)calloc(Height,sizeof(unsigned char));
      if (col[i] == 0) {
        fprintf(stderr, "Memory allocation failed at %d out of %d cols\n", i+1,Width);
        exit(1);
      }
    }

    if (doshade) {
      shades = (unsigned char**)calloc(Width,sizeof(unsigned char*));
      if (shades == 0) {
        fprintf(stderr, "Memory allocation failed.");
        exit(1);
      }
      for (i=0; i<Width; i++) {
        shades[i] = (unsigned char*)calloc(Height,sizeof(unsigned char));
        if (shades[i] == 0) {
          fprintf(stderr, "Memory allocation failed at %d out of %d shades\n", i,Width);
          exit(1);
        }
      }
    }

    setcolours();

    Depth = 3*((int)(log_2(scale*Height)))+6;

    orthographic();

    bool do_outline = 0;
    do_bw=1;
    if (do_outline) makeoutline(do_bw);

    if (doshade) smoothshades();
    for (int j=Height-1; j>=0; j--) {
      for (int i=0; i<Width; i++) {
        a.GetDibSection().PixelAt(i,j,rtable[col[i][j]]+256*gtable[col[i][j]]+256*256*btable[col[i][j]]);
      }
      printf("  %d\n", j);
    }
    a.AddFrame();
  }
  return 0;
}
