//
//  exampleUI.cpp
//  SEofASE
//
//  Created by Nanyi Jiang on 2012-11-02.
//
//

#include "exampleUI.h"
#include "example.h"
#include <math.h>
#include "Iw2D.h"

ExampleRenderer renderer;

void Button1::update(double dt){
    
    t += (dt/1000);

}

void Button1::render(){
    //renderer.drawBlackSquare(x, y, w, h);Iw2DSetColour(0xffffffff);
    
    // Render the text into a 100x100 region
    CIwSVec2 region(100, 100);
    
    // Centred on the centre of the surface
    CIwSVec2 topLeft((int16)(Iw2DGetSurfaceWidth()/2 - region.x/2),
                     (int16)(Iw2DGetSurfaceHeight()/2 - region.y/2));
    
    // Draw the string into the region
    Iw2DDrawString("Hello world from Iw2D", topLeft, region, IW_2D_FONT_ALIGN_CENTRE, IW_2D_FONT_ALIGN_CENTRE);
    
    renderer.printf("hahahaha", vec2(100,100));
    renderer.drawImage("Image.bmp",dimension.pos , 0,vec2(1,1));
    
    
    }


void REDButton::update(double dt){
    time += (dt/1000);
}

void REDButton::render(){
    //renderer.drawRedSquare(x, y, (cos(time)+1)*w, (cos(time)+1)*h);
}

