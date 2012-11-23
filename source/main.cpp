#include "example.h"
#include "exampleUI.h"
#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"
#include "anim.h"

#include <vector>

CIw2DFont *g_Font;
int main()
{
    
    // Initialise Marmalade graphics system and Iw2D module
    IwGxInit();
    Iw2DInit();

    // Set the default background clear colour
    IwGxSetColClear(0x40, 0x40, 0x40, 0);
    
    
    IwResManagerInit();
    
    // Load the group containing the "arial14" font
    IwGetResManager()->LoadGroup("Iw2DStrings.group");
    
    // Prepare the iwgxfont resource for rendering using Iw2D
    g_Font = Iw2DCreateFontResource("arial14");
    Iw2DSetFont(g_Font);
    
    
    Button1 * b = new Button1();
    b->x = 10;
    b->y = 10;
    b->w = 50;
    b->h = 30;
    Anim::getInstance().animate(b,&Widget::setX,10,100,2,"quadIn");
    // Initialise Marmalade graphics system and Iw2D module
    std::vector<Widget *> v;
    v.push_back(b);
    uint32 timer = (uint32)s3eTimerGetMs();
    // Main Game Loop
    while (!s3eDeviceCheckQuitRequest())
    {
        // Update keyboard system
        s3eKeyboardUpdate();
        if (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)    // Back key is used to exit on some platforms
            break;
        int delta = uint32(s3eTimerGetMs()) - timer;
        timer += delta;
        
        // Make sure the delta-time value is safe
        if (delta < 0)
            delta = 0;
        if (delta > 100)
            delta = 100;
        Anim::getInstance().update(delta/1000.0);
        //UpdateInput(delta);
        
        // Update pointer system
        s3ePointerUpdate();
        
        // Clear the screen
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
        
        // Update the game
        for (int i=0; i<v.size(); i++) {
            v[i]->update(delta);
        }
        
        // Render the games view
        for (int i=0; i<v.size(); i++) {
            v[i]->render();
        }
        
        // Show the surface
        Iw2DSurfaceShow();
        
        // Yield to the operating system
        s3eDeviceYield(0);
    }

    return 0;
}
