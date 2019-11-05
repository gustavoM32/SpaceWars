#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <stdint.h>
#include <stdarg.h>
#include <errno.h>
#include <pthread.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xfuncs.h>
#include <X11/Xutil.h>

#include <X11/Xatom.h>
int _invalid_window_handler(Display *dsp, XErrorEvent *err) {
    return 0;
}

int main() 
{
    Display *display = XOpenDisplay(NULL); 
    int iError;
    KeySym k;
    int revert_to;
    Window window;
    XEvent event;
    Time time;
    XSetErrorHandler(_invalid_window_handler);
    XGetInputFocus(display, &window, &revert_to);
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask );
    iError = XGrabKeyboard(display, window,
                          KeyPressMask | KeyReleaseMask,
                          GrabModeAsync,
                          GrabModeAsync,
                          CurrentTime); 
    if (iError != GrabSuccess && iError == AlreadyGrabbed) {
        XUngrabPointer(display, CurrentTime);
        XFlush(display);
        printf("Already Grabbed\n");    
    } else if (iError == GrabSuccess) {
        printf("Grabbed\n");
    }
    while(1) {
          XNextEvent(display,&event);
          switch (event.type) {
              case KeyPress : printf("Key Pressed\n"); break;
              case KeyRelease : printf("Key Released\n"); break;
              case EnterNotify : printf("Enter\n"); break;
          }
    }
    XCloseDisplay(display);
    return 0;
}