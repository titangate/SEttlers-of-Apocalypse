//
//  example.cpp
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-11-02.
//
//

#include "example.h"
// Marmalade headers
#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"

ExampleRenderer::ExampleRenderer()
{
    // Initialise Marmalade graphics system and Iw2D module
    //IwGxInit();
    //Iw2DInit();
};

void ExampleRenderer::update(double dt){
    
};


void ExampleRenderer::render(){
    
    IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
};

void ExampleRenderer::drawBlackSquare(int x0, int y0, int w, int h){
    Iw2DSetColour(0xffffffff);
    Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
    Iw2DFillRect(CIwSVec2(x0, y0), CIwSVec2(w, h));
    Iw2DSetColour(0xffffffff);
    Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
}


void ExampleRenderer::drawRedSquare(int x0, int y0, int w, int h){
    Iw2DSetColour(0xff0000ff);
    Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
    Iw2DFillRect(CIwSVec2(x0, y0), CIwSVec2(w, h));
    Iw2DSetColour(0xffffffff);
    Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
}

void ExampleRenderer::terminate(){
    
    Iw2DTerminate();
    IwGxTerminate();
};