#include "renderer.h"
#include <string>
#include "Iw2D.h"

class ImageData {
private:
	CIw2DImage *img;
public:
	ImageData(const std::string &s){
		img = Iw2DCreateImage(s.c_str());
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////Renderer Class/////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

//Implementation class
class Renderer::impl{
	friend class Renderer;
private:
	void update(double dt){

	}

	void render(){

	}

	ImageData* newImageData(const std::string &s){
		
	}

    Image* newImage(const std::string &s){
		
	}

    Image* newImage(const ImageData *){
		
	}

    void draw(const Drawable* drawable,double x=0,double y=0,double r=0,double sx=1,double sy=1,double ox=0,double oy=0){
		
	}
    void drawq(const Drawable* drawable,quad q,double x=0,double y=0,double r=0,double sx=1,double sy=1,double ox=0,double oy=0){
		
	}
    
    void setFont(Font *){
		
	}

    Font * getFont(){
		
	}

    Font * newFont(const std::string &fontfile,int size){
		
	}

    void printf(const std::string &text,double x,double y,double limit,alignmode align){
		
	}
    
    void push(){
		
	}

    void pop(){
		
	}

    void translate(double x,double y){
		
	}

    void rotation(double r){
		
	}

    void scale(double x,double y){
		
	}
    
    void setColor(double r,double g,double b,double a=0){
		
	}

    void setScissor(quad q){
		
	}

    void clear(double r,double g,double b,double a=0){
		
	}

    void dot(double x,double y){
		
	}

    void line(double x1,double y1,double x2,double y2){
		
	}

    void rectangle(quad q){
		
	}

    void circle(double x,double y,double r,double a){
		
	}

    void setLineWidth(double l){
		
	}
    
    void setBlendMode(blendmode){
		
	}

    blendmode getBlendMode(){
		
	}

    PixelEffect *newPixelEffect(const std::string &s){
		
	}

    PixelEffect *getPixelEffect(){
		
	}

    void setPixelEffect(PixelEffect *pe){
		
	}
    impl();
	~impl();
};

//Constructor and destructor refer to implementation pointer
Renderer::Renderer(){
	pImpl = new impl();
}
Renderer::~Renderer(){
	delete pImpl;
}

//All functions defined with regards to implementation pointer
void Renderer::update(double dt){pImpl->update(dt);}
void Renderer::render(){pImpl->render();}
ImageData* Renderer::newImageData(const std::string &s){return pImpl->newImageData(s);}
Image* Renderer::newImage(const std::string &s){return pImpl->newImage(s);}
Image* Renderer::newImage(const ImageData *id){return pImpl->newImage(id);}
void Renderer::draw(const Drawable* drawable,double x=0,double y=0,double r=0,double sx=1,double sy=1,double ox=0,double oy=0){pImpl->draw(drawable, x, y, r, sx, sy, ox, oy);}
void Renderer::drawq(const Drawable* drawable,quad q,double x=0,double y=0,double r=0,double sx=1,double sy=1,double ox=0,double oy=0){pImpl->drawq(drawable, q, x, y, r, sx, sy, ox, oy;}
void Renderer::setFont(Font *font){pImpl->setFont(font);}
Font *Renderer::getFont(){return pImpl->getFont();}
Font *Renderer::newFont(const std::string &fontfile, int size){return pImpl->newFont(fontfile, size);}
void Renderer::printf(const std::string &text,double x,double y,double limit,alignmode align){pImpl->printf(text, x, y, limit, align);}
void Renderer::push(){pImpl->push();}
void Renderer::pop(){pImpl->pop();}
void Renderer::translate(double x,double y){pImpl->translate(x, y);}
void Renderer::rotation(double r){pImpl->rotation(r);}
void Renderer::scale(double x,double y){pImpl->scale(x,y);}
void Renderer::setColor(double r,double g,double b,double a=0){pImpl->setColor(r, g, b, a);}
void Renderer::resetColor(){setColor(255,255,255,0);}
void Renderer::setScissor(quad q){pImpl->setScissor(q);}
void Renderer::clear(double r,double g,double b,double a=0){pImpl->clear(r, g, b, a);}
void Renderer::dot(double x,double y){pImpl->(dot(x, y);}
void Renderer::line(double x1,double y1,double x2,double y2){pImpl->line(x1, y1, x2, y2);}
void Renderer::rectangle(quad q){pImpl->rectangle(q);}
void Renderer::circle(double x,double y,double r,double a){pImpl->circle(x, y, r, a);}
void Renderer::setLineWidth(double l){pImpl->setLineWidth(l);}
void Renderer::setBlendMode(blendmode b){pImpl->setBlendMode(b);}
blendmode Renderer::getBlendMode(){return pImpl->getBlendMode();}
PixelEffect *Renderer::newPixelEffect( const std::string &s){return pImpl->newPixelEffect(s);}
PixelEffect *Renderer::getPixelEffect(){return pImpl->getPixelEffect();}
void Renderer::setPixelEffect(PixelEffect *pe){pImpl->setPixelEffect(pe);}

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////Font Class/////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

//Implementation class
class Font::impl{
	friend class Font;
private:
	int getHeight(){

	}

    int getLineHeight(){

	}

    int getWidth(const std::string &s){

	}

    int getWrap(const std::string &s){

	}

	impl();
	~impl();
};

//Constructor and destructor refer to implementation pointer
Font::Font(){
	pImpl = new impl();
}

Font::~Font(){
	delete pImpl;
}

//All functions defined w.r.t. implementation pointer
int Font::getHeight(){return pImpl->getHeight();}
int Font::getLineHeight(){return pImpl->getLineHeight();}
int Font::getWidth(const std::string &s){return pImpl->getWidth(s);}
int Font::getWrap(const std::string &s){return pImpl->getWrap(s);}

///////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////Image Class////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

//Implementation class
class Image::impl{
	friend class Image;
private:
	void clear(){

	}

    ImageData * createImageData(){

	}

    wrapmode getWrap(wrapdirection d){

	}

    void setWrap(wrapdirection,wrapmode){

	}

	impl();
	~impl();
};

//Constructor and Destructor refer to implementation pointer
Image::Image(){
	pImpl = new impl();
}

Image::~Image(){
	delete pImpl;
}

//All functions defined w.r.t. implementation pointer
void Image::clear(){pImpl->clear();}
ImageData *Image::createImageData(){pImpl->clear();}
wrapmode Image::getWrap(wrapdirection d){pImpl->clear();}
void Image::setWrap(wrapdirection,wrapmode){pImpl->clear();}

