#include "control.h"

//Simple structure to track touches

bool g_UseMultiTouch = false;
//Button* g_MultiTouchButton = 0;
char g_TouchEventMsg[128] = {0};

#define MAX_TOUCHES 10
CTouch g_Touches[MAX_TOUCHES];

//Colour to render touch in
uint8 g_TouchColours[3*MAX_TOUCHES] =
{
    0xff, 0x00, 0x00,
    0x00, 0xff, 0x00,
    0x00, 0x00, 0xff,
    0xff, 0x00, 0xff,
    0x00, 0xff, 0xff,
    0xff, 0xff, 0x00,
    0x80, 0x00, 0x00,
    0x00, 0x80, 0x00,
    0x00, 0x00, 0x80,
    0x80, 0x00, 0x80,
};

//Find an active touch with the specified id, or allocate a free one from the list
CTouch* GetTouch(int32 id)
{
    CTouch* pInActive = NULL;
    
    for (uint32 i = 0; i < MAX_TOUCHES; i++)
    {
        if (id == g_Touches[i].id)
            return &g_Touches[i];
        if (!g_Touches[i].active)
            pInActive = &g_Touches[i];
    }
    
    //Return first inactive touch
    if (pInActive)
    {
        pInActive->id = id;
        return pInActive;
    }
    
    //No more touches, give up.
    return NULL;
}


void MultiTouchButtonCB(s3ePointerTouchEvent* event)
{
    CTouch* touch = GetTouch(event->m_TouchID);
    if (touch)
    {
        touch->active = event->m_Pressed != 0;
        touch->x = event->m_x;
        touch->y = event->m_y;
    }
    if (event->m_Pressed)
        Control::getInstance().pointerPressed(event->m_x,event->m_y,S3E_POINTER_BUTTON_SELECT,event->m_TouchID);
    else
        Control::getInstance().pointerReleased(event->m_x,event->m_y,S3E_POINTER_BUTTON_SELECT,event->m_TouchID);
    sprintf(g_TouchEventMsg, "`x666666Touch %u %s",event->m_TouchID, event->m_Pressed ? "PRESSED" : "RELEASED");
}

void MultiTouchMotionCB(s3ePointerTouchMotionEvent* event)
{
    CTouch* touch = GetTouch(event->m_TouchID);
    if (touch)
    {
        touch->x = event->m_x;
        touch->y = event->m_y;
    }
    Control::getInstance().pointerMotion(event->m_x, event->m_y, event->m_TouchID);
}

void SingleTouchButtonCB(s3ePointerEvent* event)
{
    g_Touches[0].active = event->m_Pressed != 0;
    g_Touches[0].x = event->m_x;
    g_Touches[0].y = event->m_y;
    if (event->m_Pressed)
        Control::getInstance().pointerPressed(event->m_x,event->m_y,event->m_Button,0);
    else
        Control::getInstance().pointerReleased(event->m_x,event->m_y,event->m_Button,0);
    sprintf(g_TouchEventMsg, "`x666666Touch %s", event->m_Pressed ? "PRESSED" : "RELEASED");
}

void SingleTouchMotionCB(s3ePointerMotionEvent* event)
{
    g_Touches[0].x = event->m_x;
    g_Touches[0].y = event->m_y;
}

void ExampleInit()
{
    // An OS which supports multi-touch will return TOUCH_EVENTs if they are registered for.
    // An OS which does not will only raise standard pointer events.
    g_UseMultiTouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;
    
    if (g_UseMultiTouch)
    {
        //Register for multi touch events on platforms where the functionality is available.
        s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, NULL);
        s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, NULL);
        //g_MultiTouchButton = NewButton("Disable Multitouch");
    }
    else
    {
        //Register for standard pointer events
        s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);
        s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB, NULL);
    }
}

void ExampleTerm()
{
    //Clear up
    if (g_UseMultiTouch)
    {
        s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB);
        s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB);
    }
    else
    {
        s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB);
        s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB);
    }
}

bool ExampleUpdate()
{
    if(0){
        if (g_UseMultiTouch)
        {
            //g_MultiTouchButton = NewButton("Enable Multitouch");
            s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB);
            s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB);
            //Register for standard pointer events
            s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB, NULL);
            s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB, NULL);
        }
        else
        {
           // g_MultiTouchButton = NewButton("Disable Multitouch");
            s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)SingleTouchButtonCB);
            s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)SingleTouchMotionCB);
            //Register for multi touch events.
            s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)MultiTouchButtonCB, NULL);
            s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)MultiTouchMotionCB, NULL);
        }
        
        g_UseMultiTouch = !g_UseMultiTouch;
    }
    return true;
}

void Control::registerDelegate(controlDelegate * del){
    delegate = del;
}
void Control::unregisterDelegate(){
    delegate = 0;
}
