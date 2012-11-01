#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"
#include "Renderer.h"
#include "Game.h"

int main()
{
    // Initialise Marmalade graphics system and Iw2D module
    IwGxInit();
    Iw2DInit();
    
    Iw2DTerminate();
    IwGxTerminate();
    
    return 0;
}
