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

#include "InputGestureX.hpp"

#include <list>
using namespace tuio;

//--------------------------------------------------------------
void testApp::Setup(){
    j = new tuio::Juego();
}

//--------------------------------------------------------------
void testApp::Update(){
    j->Process();
}

//--------------------------------------------------------------
void testApp::Draw(){
    j->Draw();
}

//--------------------------------------------------------------
void testApp::WindowResized(int w, int h){

}
