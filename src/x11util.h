// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef __X11_UTIL_H__
#define __X11_UTIL_H__

#include <X11/Xlib.h>
#include <iostream>

class X11Util 
{
public:
    X11Util() :m_display(NULL)
    {
        m_display = XOpenDisplay(NULL);
        if (m_display) m_dest_w = XRootWindow(m_display, 0);
    }

    ~X11Util() 
    {
        if (m_display) XCloseDisplay(m_display); m_display = NULL;
    }

    void SetCursorPos(int x, int y) 
    {
        if (m_display == NULL) {
            std::cout << "ERROR: fail to open display" << std::endl;
            return;
        }

        XSelectInput(m_display, m_dest_w, KeyReleaseMask);
        // http://tronche.com/gui/x/xlib/input/XWarpPointer.html
        XWarpPointer(m_display, None, m_dest_w, 0, 0, 0, 0, x, y);
        XFlush(m_display);
    } 

private:
    Display* m_display;
    Window m_dest_w;
};

#endif // __X11_UTIL_H__
