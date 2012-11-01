#ifndef RENDERER_H
#define RENDERER_H
#include <string>

enum wrapmode {
    repeat,
    clamp,
};

enum wrapdirection{
    horz,
    vert,
};

class ImageData;  // Can be used to create/store Image

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

class Renderer{
public:
    void update(double dt);
    void render();
    ImageData* newImageData(const std::string &s); // Create a image data which should contain the actual file data
    Image* newImage(const std::string &s); // Create a image through a file and destroy the file data afterwards
    Image* newImage(const ImageData *); // Create a image from a imagedata object. User is expected to decide
        // based on their specific situations.
    
    
    Renderer();
protected:
    
};

#endif