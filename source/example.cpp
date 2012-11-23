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
#include "IwResManager.h"

ExampleRenderer::ExampleRenderer()
{
    // Initialise Marmalade graphics system and Iw2D module
    //IwGxInit();
    //Iw2DInit();
    _matrixStack.push(CIwMat2D::g_Identity);
};

void ExampleRenderer::render(){
    
    IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
};

CIw2DImage * ExampleRenderer::getImage(const string& s){
    if (_images.find(s)==_images.end())
        _images[s] = Iw2DCreateImage(s.c_str());
    return _images[s];
};

void ExampleRenderer::drawImage(const string &s,vec2 pos,double angle,vec2 scale,vec2 origin){
    drawImage(getImage(s), pos, angle,scale,origin);
}

void ExampleRenderer::drawImage(CIw2DImage * image,vec2 pos,double angle,vec2 scale,vec2 origin){
    CIwSVec2 centre = CIwSVec2(pos.x,pos.y);
    
    CIwSVec2 topleft = CIwSVec2(pos.x-origin.x,pos.y-origin.y);
    //printf("%f\n",angle);
    iwfixed Fangle = angle*IW_FIXED(1/(M_PI*2));
    push();
    CIwMat2D rot = _matrixStack.top();
    rot.SetRot(Fangle,(CIwVec2)centre);
    
    Iw2DSetTransformMatrix(rot);
    Iw2DDrawImage(image,centre,CIwSVec2(image->GetWidth()*scale.x,image->GetHeight()*scale.y));
    Iw2DSetTransformMatrix(CIwMat2D::g_Identity);
    //pop();
};

void ExampleRenderer::push(){
    //_matrixStack.push(_matrixStack.top());
}
void ExampleRenderer::pop(){
    //_matrixStack.pop();
    //Iw2DSetTransformMatrix(_matrixStack.top());
}

void ExampleRenderer::printf(const string &s, vec2 pos,CIw2DFontAlign horzAlign,CIw2DFontAlign vertAlign,vec2 size){
    Iw2DDrawString(s.c_str(),CIwSVec2(pos.x,pos.y),CIwSVec2(size.x,size.y),horzAlign,vertAlign);
}
void ExampleRenderer::terminate(){
    
    Iw2DTerminate();
    IwGxTerminate();
};