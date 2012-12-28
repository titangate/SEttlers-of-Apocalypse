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
#include <iostream>

void ParticleSystem::update(double dt){
    if (particles.size()) {
        if (particles.begin()->life <= 0) particles.pop_front();
        for (deque<Particle>::iterator i=particles.begin(); i!=particles.end(); i++) {
            i->life -=dt;
        }
    }
    
    if (life >= 0) {
        life -= dt;
        double emissiondelta = 1.0/emissionrate;
        dt = dt + this->dt;
        while (dt > emissiondelta) {
            dt -= emissiondelta;
            emit();
        }
        this->dt = dt;
    }
    
}

void ParticleSystem::emit(){
    if (particles.size()<max_count) {
        //printf("%d\n",particles.size());
        particles.push_back(Particle(pos,particlelife));
    }
}

void ParticleSystem::render(){
    //printf("%d\n",particles.size());
    //for (deque<Particle>::iterator i=particles.begin(); i!=particles.end(); i++) {
    for (unsigned int i=0;i<particles.size();i++){
        double scale = deltasize.y-(deltasize.y-deltasize.x)*particles[i].life/particlelife;
        ExampleRenderer::getInstance().drawImage(image, particles[i].pos, 0,vec2(scale,scale),origin);
    }
}

ExampleRenderer::ExampleRenderer()
{
    // Initialise Marmalade graphics system and Iw2D module
    //IwGxInit();
    //Iw2DInit();
    _matrixStack.push(CIwMat2D::g_Identity);
    
}

void ExampleRenderer::render(){
    
    IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
}

void ExampleRenderer::setFont(const string& s){
    Iw2DSetFont(getFont(s));
}

void ExampleRenderer::setFont(CIw2DFont* f){
    Iw2DSetFont(f);
}

CIw2DFont * ExampleRenderer::getCurrentFont(){
    return Iw2DGetFont();
}

CIw2DImage * ExampleRenderer::getImage(const string& s){
    if (_images.find(s)==_images.end()){
        _images[s] = Iw2DCreateImage(s.c_str());
    }
    return _images[s];
};

CIw2DFont * ExampleRenderer::getFont(const string& s){
    if (_fonts.find(s)==_fonts.end())
        //IwGetResManager()->LoadGroup("Iw2DStrings.group");
    
    // Prepare the iwgxfont resource for rendering using Iw2D
        _fonts[s] = Iw2DCreateFontResource(s.c_str());
    return _fonts[s];
}

void ExampleRenderer::drawImage(const string &s,vec2 pos,double angle,vec2 scale,vec2 origin){
    drawImage(getImage(s), pos, angle,scale,origin);
}

void ExampleRenderer::drawImageQ(const string &s,quad q,vec2 pos,double angle,vec2 scale,vec2 origin){
    drawImageQ(getImage(s),q, pos, angle,scale,origin);
}

void ExampleRenderer::drawImage(CIw2DImage * image,vec2 pos,double angle,vec2 scale,vec2 origin){
    
    
    CIwMat2D m(1);
    CIwSVec2 centre = CIwSVec2(pos.x,pos.y);
    
    m.SetRot(IW_FIXED(angle/(M_PI*2)));
    m.SetTrans(centre);
    m = m*_matrixStack.top();
    Iw2DSetTransformMatrix(m);
    Iw2DDrawImage(image,CIwSVec2(-origin.x*scale.x,-origin.y*scale.y),CIwSVec2(image->GetWidth()*scale.x,double(image->GetHeight())*scale.y));
    Iw2DSetTransformMatrix(_matrixStack.top());
};


void ExampleRenderer::drawImageQ(CIw2DImage * image,quad q,vec2 pos,double angle,vec2 scale,vec2 origin){
    
    /*CIwMat2D m;
    CIwSVec2 centre = CIwSVec2(pos.x,pos.y);
    
    m.SetRot(IW_FIXED(angle/(M_PI*2)));
    m.SetTrans(centre);
    
    m.m[0][0] = IW_FIXED_MUL(m.m[0][0], IW_FIXED(scale.x));
    m.m[1][0] = IW_FIXED_MUL(m.m[1][0], IW_FIXED(scale.x));
    m.m[0][1] = IW_FIXED_MUL(m.m[0][1], IW_FIXED(scale.y));
    m.m[1][1] = IW_FIXED_MUL(m.m[1][1], IW_FIXED(scale.y));
    //rot+=CIwSVec2(-origin.x,-origin.y);
    m = m*_matrixStack.top();
    Iw2DSetTransformMatrix(m);
    Iw2DDrawImageRegion(image,
                  CIwSVec2(-origin.x,-origin.y),
                  //CIwSVec2(q.size.x*scale.x,q.size.y*scale.y),
                  CIwSVec2(q.pos.x,q.pos.y),
                  CIwSVec2(q.size.x,q.size.y)
                        );
    Iw2DSetTransformMatrix(_matrixStack.top());*/
    //pop();
    
    CIwMat2D m(1);
    CIwSVec2 centre = CIwSVec2(pos.x,pos.y);
    
    m.SetRot(IW_FIXED(angle/(M_PI*2)));
    m.SetTrans(centre);
    m = m*_matrixStack.top();
    Iw2DSetTransformMatrix(m);
    Iw2DDrawImageRegion(image,CIwSVec2(-origin.x*scale.x,-origin.y*scale.y),
                        CIwSVec2(q.size.x*scale.x,q.size.y*scale.y),
                        CIwSVec2(q.pos.x,q.pos.y),
                        CIwSVec2(q.size.x,q.size.y));
    Iw2DSetTransformMatrix(_matrixStack.top());
};


void ExampleRenderer::push(){
    _matrixStack.push(_matrixStack.top());
}
void ExampleRenderer::pop(){
    _matrixStack.pop();
    Iw2DSetTransformMatrix(_matrixStack.top());
}

void ExampleRenderer::scale(vec2 scale){
    iwfixed sx = IW_FIXED(scale.x);
    iwfixed sy = IW_FIXED(scale.y);
    _matrixStack.top().m[0][0] = IW_FIXED_MUL(_matrixStack.top().m[0][0],sx);
    _matrixStack.top().m[0][1] = IW_FIXED_MUL(_matrixStack.top().m[0][1],sx);
    _matrixStack.top().m[1][0] = IW_FIXED_MUL(_matrixStack.top().m[1][0],sy);
    _matrixStack.top().m[1][1] = IW_FIXED_MUL(_matrixStack.top().m[1][1],sy);
    //_matrixStack.top().ScaleRot(IW_FIXED(scale));
}

void ExampleRenderer::rotate(double angle){
    //iwfixed fangle = IW_FIXED(angle);
    iwfixed c = IW_FIXED(cos(angle)),s=IW_FIXED(sin(angle));
    iwfixed m0=_matrixStack.top().m[0][0],m1=_matrixStack.top().m[0][1],
    m4=_matrixStack.top().m[1][0],m5=_matrixStack.top().m[1][1];
    _matrixStack.top().m[0][0] = IW_FIXED_MUL(m0,c) + IW_FIXED_MUL(m1,s);
    _matrixStack.top().m[0][1] = IW_FIXED_MUL(m0,-s) + IW_FIXED_MUL(m1,c);
    _matrixStack.top().m[1][0] = IW_FIXED_MUL(m4,c) + IW_FIXED_MUL(m5,s);
    _matrixStack.top().m[1][1] = IW_FIXED_MUL(m4,-s) + IW_FIXED_MUL(m5,c);
    //_matrixStack.top().RotateVec(CIwVec2(0,0));
}

void ExampleRenderer::translate(vec2 pos){
    _matrixStack.top().t+=CIwVec2(pos.x,pos.y);
}

void ExampleRenderer::printf(const string &s, vec2 pos,CIw2DFontAlign horzAlign,CIw2DFontAlign vertAlign,vec2 size){
    Iw2DDrawString(s.c_str(),CIwSVec2(pos.x,pos.y),CIwSVec2(size.x,size.y),horzAlign,vertAlign);
}
void ExampleRenderer::terminate(){
    
    Iw2DTerminate();
    IwGxTerminate();
};