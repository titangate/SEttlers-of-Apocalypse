#ifndef RENDERER_H
#define RENDERER_H
#include <string>
#include "core.h"

enum wrapmode {
    repeat,
    clamp,
};

enum wrapdirection{
    horz,
    vert,
};
enum alignmode{
    left,
    center,
    right,
};
enum blendmode{
    additive,
    alpha,
    subtractive,
    multiplicative,
}

class ImageData;  // Can be used to create/store Image
class PixelEffect; // Fragment shader

class Drawable{}; 
class Canvas:public Drawable{
    // This is supposed to be a frame buffer. Secondary objective, not immediately needed.
    void clear(); // clear the frame buffer
    ImageData * createImageData();
    wrapmode getWrap(wrapdirection d); // repeat or clamp
    void setWrap(wrapdirection,wrapmode);
    
};
class Font:public Drawable{
    int getHeight(); //Gets the height of the Font in pixels
    int getLineHeight(); //Gets the line height.
    int getWidth(const std::string &s);//Determines the horizontal size a line of text needs.
    int getWrap(const std::string &s);//Returns how many lines text would be wrapped to.
};
class Image:public Drawable{
    // identical to a Canvas, which is intended. You are welcome to finish this before bother with Canvas
    void clear(); // clear the frame buffer
    ImageData * createImageData();
    wrapmode getWrap(wrapdirection d); // repeat or clamp
    void setWrap(wrapdirection,wrapmode);
};

// Note:
// Coordinate system: from left top to right bottom, with pixel as unit.
// all rotation and scaling are expected to take (0,0) as their centre of operation.
// All angles are in radians.

class Renderer{
public:
    void update(double dt);
    void render();
    ImageData* newImageData(const std::string &s); // Create a image data which should contain the actual file data
    Image* newImage(const std::string &s); // Create a image through a file and destroy the file data afterwards
    Image* newImage(const ImageData *); // Create a image from a imagedata object. User is expected to decide
        // based on their specific situations.
    void draw(const Drawable* drawable,double x=0,double y=0,double r=0,double sx=1,double sy=1,double ox=0,double oy=0);
        // drawable: what you are supposed to draw on current target (can be canvas or screen)
        // x,y: position
        // r: rotation
        // sx,sy: scaleX/scaleY. if sy is not given, it is expected to be the same as given sx.
        // ox,oy: the rotation centre offset.
    void drawq(const Drawable* drawable,quad q,double x=0,double y=0,double r=0,double sx=1,double sy=1,double ox=0,double oy=0);
        // same as draw. quad is defined in core.h, where it specified which part of the picture should be drawn.
        // say the picture is a 2*2 tile, in total dimension of 128*128. I want to draw the bot right quarter,
        // I'd pass in a quad with pos(64,64),size(64,64)
    
    void setFont(Font *);
    Font * getFont(); // should be obvious
    Font * newFont(const std::string & fontfile,int size);
    // initialize a font with given size. use image font if you feel lazy
    void printf(const std::string & text,double x,double y,double limit,alignmode align);
    // x,y : position
    // limit : how many pixels does it take before the text breaks into multiple line
    // align : align style for every line
    
    void push(); // push transformation matrix
    void pop(); // pop transformation matrix
    void translate(double x,double y); //translate coordinate dimension
    void rotation(double r);// refer to the note above
    void scale(double x,double y);// refer to the note above
    
    void setColor(double r,double g,double r,double a=0); //should be obvious
    void resetColor(){setColor(255,255,255,255);}// set current color to (255,255,255,255)
    void setScissor(quad q);// restrict drawing operation in a square area on the screen. if pass in a quad with size
        // (0,0), the scissor should be canceled.
    void clear(double r,double g,double r,double a=0); //clear with given color
    
    // simple geometrix shape
    void dot(double x,double y);
    void line(double x1,double y1,double x2,double y2);
    void rectangle(quad q);
    void circle(double x,double y,double r,double a);// r is radius, a is sides of the circle
    void setLineWidth(double l);
    
    // blend mode
    void setBlendMode(blendmode);
    blendmode getBlendMode();
    
    // pixel effect, don't worry about it for now. doubt we'd ever will.
    PixelEffect * newPixelEffect(const string &);// initialize fragment shader from the given file
    PixelEffect * getPixelEffect();
    void setPixelEffect(PixelEffect *); // when 0, use default fragment shader
    
    
    Renderer();
protected:
    
};

#endif