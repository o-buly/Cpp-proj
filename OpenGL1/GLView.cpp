// GlView.cpp: implementation of the CGlView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlView.h"

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGlView::CGlView(CWnd *pclWnd)
{
	m_pclWnd = pclWnd;
	m_hDC = ::GetDC(pclWnd->m_hWnd);
	BOOL bSuccess;

	RECT rect;
	m_pclWnd->GetClientRect(&rect);
	int iWidth = rect.right - rect.left;
	int iHeight = rect.bottom - rect.top;

	bSuccess = bSetWindowPixelFormat(m_hDC);
	ASSERT(&bSuccess);

	bSuccess = bCreateViewGLContext(m_hDC);
	ASSERT(&bSuccess);

	vInitGl(iWidth, iHeight);

	generateTextureFromImageFile();
}

// +
// *****************************************************************************
//   Module      :  CGlView::~CGlView()
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is the one and only destructor. It provides
//									clean up and performs any needed shutdown procedures
//
//   Notes       :  None
// *****************************************************************************
// -

CGlView::~CGlView()
{
	// make the rendering context not current
	if (wglGetCurrentContext() != NULL)
		wglMakeCurrent(NULL, NULL);

	// delete the Context
	if (m_hGLContext != NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}
}


// +
// *****************************************************************************
//   Module      :  void CGlView::DrawGLScene()	
//   Access      :  Public
//   Input       :  None
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function is called contiously to provide realtime OpenGl
//									drawing
//
//   Notes       :  Place all reatime rendering code here
// *****************************************************************************
// -
void CGlView::vDrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
	//Disable Colors On The Object
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);

	//Background
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, idTexture[2]);
	glPushMatrix();
	glTranslatef(0, 0, -50);
	glScalef(3, 3, 3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-19.9, -11.5, -5.4);
	glTexCoord2f(0.0, 1.0);	glVertex3f(-19.9, 10.0, -5.4);
	glTexCoord2f(1.0, 1.0); glVertex3f(19.9, 10.0, -5.4);
	glTexCoord2f(1.0, 0.0);	glVertex3f(19.9, -11.5, -5.4);
	glEnd();
	glPopMatrix();


	//Enable Colors On The Object
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//Define Lighting To The Object
	GLUquadricObj* obj;
	obj = gluNewQuadric();

	//Movement & Rotation
	glTranslatef(Movex, Movey, -5 + Movez);
	glRotatef(Rotx, 1, 0, 0);
	glRotatef(Roty, 0, 1, 0);
	glRotatef(Rotz, 0, 0, 1);
	glRotatef(roll, 0, 0, 1);

	//Adjust Aircraft Starting Location
	glRotatef(106, 1, 0, 0);
	glTranslatef(0, -11, 5);
	glRotatef(-12, 0, 1, 0);
	glRotatef(180, 0, 0, 1);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glColor3f(0, 0, 1);
	glRotatef(90, 0, 1, 0);
	glTranslatef(3, 0, -4);

	//Aircraft Body
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(obj, true);
	glBindTexture(GL_TEXTURE_2D, idTexture[1]);
	gluCylinder(obj, 0.25, 0.8, 3, 32, 32);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);
	glTranslatef(0, 0, 0);
	gluDisk(obj, 0, 0.2, 8,10);
	glPopMatrix();


	glTranslatef(0, 0, 3);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(obj, true);
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);
	gluCylinder(obj, 0.8, 0.8, 3, 32, 32);
	glTranslatef(0, 0, 3);
	gluCylinder(obj, 0.8, 0.4, 3, 32, 32);
	glDisable(GL_TEXTURE_2D);

	//Aircraft Back 1
	glPushMatrix();
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(obj, true);
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, 3);
	gluCylinder(obj, 0.4, 0.2, 1, 32, 32);
	glPopMatrix();

	//plane back Fire
	glPushMatrix();
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(obj, true);
	glBindTexture(GL_TEXTURE_2D, idTexture[3]);
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, 4);
	gluCylinder(obj, 0.2, 0, 2, 32, 32);
	glPopMatrix();

	//Aircraft Back 2
	glPushMatrix();
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(obj, true);
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);
	glColor3f(1, 1, 1);
	glTranslatef(0, 0, 3);
	gluCylinder(obj, 0.4, 0.0, 1, 32, 32);
	glPopMatrix();

	//Right Wing
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-2.4, 0, 0.4);
	gluCylinder(obj, 0.4, 0.1, 1.85, 3, 3);
	glPushMatrix();
	glTranslatef(0, 0, 1.5);
	gluDisk(obj, 0, 0.1, 3, 3);
	glPopMatrix();

	//Left Wing
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-2.4, 0, -2.3);
	gluCylinder(obj, 0.1, 0.4, 1.85, 3, 3); 
	glPushMatrix();
	gluDisk(obj, 0, 0.1, 3, 3);
	glPopMatrix();

	//Top Wing
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(obj, true);
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);
	glRotatef(90, 0, 1, 0);
	glScalef(1.1, 0.4, 1.3);
	glTranslatef(-2.4, 0, 0);
	gluCylinder(obj, 0.8, 0, 2, 3, 3); //top
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();

	//Main Wings
	glPushMatrix();
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(obj, true);
	glBindTexture(GL_TEXTURE_2D, idTexture[0]);
	glRotatef(90, 0, 1, 0);
	glTranslatef(3, 0.9, 0.4);
	glScalef(0.25, 2.2, 1.3);
	//Right Main Wing
	gluCylinder(obj, 1, 0.4, 4, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 4);
	gluDisk(obj, 0, 0.7, 6, 6);

	//Left Main Wing
	glPopMatrix();
	glTranslatef(0, 0, -4.4);
	glPushMatrix();
	gluCylinder(obj, 0.4, 1, 4, 10, 10);
	gluDisk(obj, 0, 0.7, 6, 6);

	glPopMatrix();
	glPopMatrix();

	//Rockets 1
	   glPushMatrix();
	   glTranslatef(0, rockets, 0);
	   glColor3f(1.0f, 1.0f, 1.0f);
	   glEnable(GL_TEXTURE_2D);
	   gluQuadricTexture(obj, true);
	   glBindTexture(GL_TEXTURE_2D, idTexture[5]);
	   //Right Side
	   glTranslatef(2.7, 1, -2.62);
	   glRotatef(90, 1, 0, 0);
	   gluCylinder(obj, 0.3, 0.3, 1, 32, 32);
	   glPushMatrix();
	   gluCylinder(obj, 0.4, 0.2, 2, 32, 32);
	   glPopMatrix();
	   glPopMatrix();
	   //Missels 1
	   glPushMatrix();
	   glTranslatef(0, rockets, 0);
	      glPushMatrix();
	      glColor3f(1.0f, 1.0f, 1.0f);
	      glEnable(GL_TEXTURE_2D);
	      gluQuadricTexture(obj, true);
	      glBindTexture(GL_TEXTURE_2D, idTexture[5]);

	      //LeftSide Side
	      glTranslatef(-2.7, 1, -2.62);
	      glRotatef(90, 1, 0, 0);
	      gluCylinder(obj, 0.3, 0.3, 1, 32, 32);
	      glPushMatrix();
	      gluCylinder(obj, 0.4, 0.2, 2, 32, 32);
	      glPopMatrix();
	      glPopMatrix();


	   glColor3f(1.0f, 1.0f, 1.0f);
	   glEnable(GL_TEXTURE_2D);
	   gluQuadricTexture(obj, true);
	   glBindTexture(GL_TEXTURE_2D, idTexture[6]);
	   //Right Side
	   glTranslatef(2.7, -1, -2.62);
	   glRotatef(90, 1, 0, 0);
	   gluCylinder(obj, 0.2, 0, 1, 32, 32);
	   glPopMatrix();
	   glPopMatrix();
	   //Missels 2
	   glPushMatrix();
	   glTranslatef(0, rockets, 0);
	   glPushMatrix();
	   glColor3f(1.0f, 1.0f, 1.0f);
	   glEnable(GL_TEXTURE_2D);
	   gluQuadricTexture(obj, true);
	   glBindTexture(GL_TEXTURE_2D, idTexture[6]);
	   //Left Side
	   glTranslatef(-2.7, -1, -2.62);
	   glRotatef(90, 1, 0, 0);
	   gluCylinder(obj, 0.2, 0, 1, 32, 32);
	   glPopMatrix();
	   glPopMatrix();





	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(obj);

	// swap the buffer
	SwapBuffers(m_hDC);

}



// +
// *****************************************************************************
//   Module      :  BOOL CGlView::SetWindowPixelFormat(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required pixelformat descriptor
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bSetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags =

		PFD_DRAW_TO_WINDOW |// Format Must Support Window
		PFD_SUPPORT_OPENGL |// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,	// Must Support Double Buffering
		PFD_TYPE_RGBA,		// Request An RGBA Format
		32,					// Select A 16Bit Color Depth
		0, 0, 0, 0, 0, 0,	// Color Bits Ignored (?)
		0,					// No Alpha Buffer
		0,					// Shift Bit Ignored (?)
		0,					// No Accumulation Buffer
		0, 0, 0, 0,			// Accumulation Bits Ignored (?)
		16,					// 16Bit Z-Buffer (Depth Buffer)  
		0,					// No Stencil Buffer
		0,					// No Auxiliary Buffer (?)
		PFD_MAIN_PLANE,		// Main Drawing Layer
		0,					// Reserved (?)
		0, 0, 0;			// Layer Masks Ignored (?)

	int iGLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	ASSERT(&iGLPixelIndex);

	if (SetPixelFormat(hDC, iGLPixelIndex, &pixelDesc))
		return false;

	return TRUE;
}



// +
// *****************************************************************************
//   Module      :  BOOL CGlView::CreateViewGLContext(HDC hDC)
//   Access      :  Private
//   Input       :  hDC - Handle to the GL windwos device context
//   Output      :  None
//   Return Val  :  TRUE  - success
//									FALSE - failure
//   Exceptions  :  None
//   Desc        :  This function sets up the required GLContext
//
//   Notes       :  None
// *****************************************************************************
// -
BOOL CGlView::bCreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL)
		return FALSE;

	if (wglMakeCurrent(hDC, m_hGLContext) == FALSE)
		return FALSE;

	return TRUE;
}

// +
// *****************************************************************************
//   Module      :  void CGlView::InitGl(int iWidth, int iHeigth)
//   Access      :  Private
//   Input       :  iWidth  - width of the window
//									iHeight - height of the window
//   Output      :  None
//   Return Val  :  None
//   Exceptions  :  None
//   Desc        :  This function initializes all OpenGL rendering specifics
//
//   Notes       :  None
// *****************************************************************************
// -
void CGlView::vInitGl(int iWidth, int iHeigth)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glViewport(0, 0, iWidth, iHeigth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)iWidth / (GLfloat)iHeigth, 0.45f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CGlView::generateTextureFromImageFile()
{
	glGenTextures(SIZE, idTexture);

	const char* imageFileName[SIZE] = { "images\\body.bmp",  "images\\head.bmp", "images\\background.bmp","images\\fire.bmp","images\\fire.bmp","images\\rockets.bmp","images\\missels.bmp" };

	for (int i = 0; i < SIZE; i++)
	{
		texture = auxDIBImageLoad(imageFileName[i]);//loads the width, height, colors from the image file (*.bmp) into opengl structure (AUX_RGBImageRec).

		if (texture)
		{
			glBindTexture(GL_TEXTURE_2D, idTexture[i]);//working on idTexture[i]
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//if the target is smaller than the source then minimize it using LINEAR algorithm.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//if the target is bigger than the source then maximize it using LINEAR algorithm.
			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture->sizeX, texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);//save texture in memory.
			free(texture);
			texture = NULL;
		}
	}
}


