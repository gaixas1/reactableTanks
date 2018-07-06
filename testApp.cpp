/*
*********************************************
** UPF/ETIS - Taller de Sistemes Interactius I, Curso 2010/2011
**
** Practica 1
** Sergio Leon Gaixas - NIA 100750
** Albert Rodríguez Franco - NIA 103117
*********************************************
*/
#include "testApp.h"
#include "CursorFeedback.hpp"
#include "FigureFeedback.hpp"
#include "TapFeedback.hpp"
#include "Calibrator.hpp"

#include <list>
using namespace tuio;

//--------------------------------------------------------------
void testApp::Setup(){
	ofSetFrameRate(60);
    j = new tuio::Juego();
}

//--------------------------------------------------------------
void testApp::Update(){
    j->Process();
}

//--------------------------------------------------------------
void testApp::Draw(){
	/*
   glMatrixMode(GL_PROJECTION);
   gluPerspective(60.0f,(GLfloat)(1024/768),0.01f,10000.0f);
   gluLookAt(0,0,50,0,0,0,0.0f,-10.0f,0.0f);
    glMatrixMode(GL_MODELVIEW);
	*/
	j->Draw();
}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){

}
