#ifndef foundation_h
#define foundation_h

#include "linearalgebra.h"
#include <qgl.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qimage.h>
#include <qapplication.h>
#include <stdlib.h>				// defines rand() function
#include <iostream>
#include <qmessagebox.h>
#include <qradiobutton.h>
#include <qcolordialog.h>
#include <QMouseEvent>
#define EPSILON 0.00001
#define SEP << " " <<
#define NL  << "\n"


// I can't seem to make the -LANG:bool=ON switch work so :

//---------------------------------------------------------------------------
// if C++ type `bool' is not defined with compiler being used ...

#ifdef NOBOOL
typedef int bool;

#define true  1
#define false 0
#endif

//---------------------------------------------------------------------------

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <qgl.h>

//const double M_PI = 3.1415925;
const  int  X = 0;
const  int  Y = 1;
const  int  Z = 2;

#endif

