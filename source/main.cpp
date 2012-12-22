#include "example.h"
#include "exampleUI.h"
#include "s3e.h"
#include "Iw2D.h"
#include "IwGx.h"
#include "anim.h"
#include "button.h"
#include "structure.h"
#include "game.h"

#include <vector>

CIw2DFont *g_Font;
int main()
{
    
    // Initialise Marmalade graphics system and Iw2D module
    IwGxInit();
    Iw2DInit();

    // Set the default background clear colour
    IwGxSetColClear(0x00, 0x00, 0x00, 0);
    
    
    IwResManagerInit();
    
    // Load the group containing the "arial14" font
    IwGetResManager()->LoadGroup("Iw2DStrings.group");
    
    // Prepare the iwgxfont resource for rendering using Iw2D
    g_Font = Iw2DCreateFontResource("arial14");
    Iw2DSetFont(g_Font);
    uint32 sw = IwGxGetScreenWidth(); // returns 176
    uint32 sh = IwGxGetScreenHeight();
    Widget * base = new Widget(0,vec2(0,0),vec2(sw,sh));
    Panel * p = new Panel(base,vec2(50,50),vec2(256,256));
    Game * g = new Game();
    g->initDemo(base);
    p->generateButton("button1");
    p->generateButton("button2");
        //Button * b = new Button(p,vec2(100,100),vec2(200,50)); b->setText("adsfasdf");
   
    // Initialise Marmalade graphics system and Iw2D module
    //std::vector<Widget *> v;
    //v.push_back(b);
    uint32 timer = (uint32)s3eTimerGetMs();
    // Main Game Loop
    while (!s3eDeviceCheckQuitRequest())
    {
        // Update keyboard system
        s3eKeyboardUpdate();
        if (s3eKeyboardGetState(s3eKeyAbsBSK) & S3E_KEY_STATE_DOWN)    // Back key is used to exit on some platforms
            break;
        double delta = s3eTimerGetMs() - timer;
        timer += delta;
        
        // Make sure the delta-time value is safe
        if (delta < 0)
            delta = 0;
        if (delta > 100)
            delta = 100;
        delta /= 1000.0;
        
        // Update pointer system
        s3ePointerUpdate();
        
        // Clear the screen
        IwGxClear(IW_GX_COLOUR_BUFFER_F | IW_GX_DEPTH_BUFFER_F);
        
        // Update the game
        Anim<Panel>::getInstance().update(delta);
        //printf("%.2f",delta);
        base->update(delta);
        g->update(delta);
        base->render();
        g->render();
        // Show the surface
        Iw2DSurfaceShow();
        
        // Yield to the operating system
        s3eDeviceYield(0);
    }

    return 0;
}
