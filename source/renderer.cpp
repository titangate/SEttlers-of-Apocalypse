#include "renderer.h"
#include "Iw2D.h"

class ImageData {
private:
	CIw2DImage *img;
public:
	ImageData(const std::string &s){
		img = Iw2DCreateImage(s.c_str());
	}
};