#include "guiruf.hpp"

/**
 * @brief Construct a new GUIRUF::GUIRUF object
 * @details Generate a new window
 */
GUIRUF::GUIRUF() {
    d = XOpenDisplay(NULL);
    if (!d) {
        std::cerr << "Failed to Connect X server." << std::endl;
        return;
    }
    int screen_num = DefaultScreen(d);
    window_width = DisplayWidth(d, screen_num);
    window_height = DisplayHeight(d, screen_num);
    black = BlackPixel(d, screen_num);
    white = WhitePixel(d, screen_num);
    wr = XCreateSimpleWindow(
        d, RootWindow(d, screen_num), 0, 0, window_width, window_height, 1, black, white);
    XSelectInput(d, wr, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask);
    XMapWindow(d, wr);
    gc = XCreateGC(d, wr, 0, NULL);
    XFlush(d);
}

/**
 * @brief Construct a new GUIRUF::GUIRUF object
 * @details Generate a new window
 * 
 * @param width set window width
 * @param height set window height
 */
GUIRUF::GUIRUF(int width, int height) {
    window_width = (width < 1) ? 1 : width;
    window_height = (height < 1) ? 1 : height;
    d = XOpenDisplay(NULL);
    if (!d) {
        std::cerr << "Failed to Connect X server." << std::endl;
        return;
    }
    int screen_num = DefaultScreen(d);
    black = BlackPixel(d, screen_num);
    white = WhitePixel(d, screen_num);
    wr = XCreateSimpleWindow(
        d, RootWindow(d, screen_num), 0, 0, window_width, window_height, 1, black, white);
    XSelectInput(d, wr, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask);
    XMapWindow(d, wr);
    gc = XCreateGC(d, wr, 0, NULL);
    XFlush(d);
}

/**
 * @brief Destroy the GUIRUF::GUIRUF object
 * @details destroy the window.
 */
GUIRUF::~GUIRUF() {
    XFreeGC(d, gc);
    XFlush(d);
    XCloseDisplay(d);
}

/**
 * @brief Update events of mouse and keyboard.
 * @details To get mouse and keyboard events, need to execute this command in loop processing.
 */
void GUIRUF::UpdateEvents() {
    mouse_clicked = false;
    mouse_released = false;
    key_pressed = false;
    key_released = false;
    got_keycode = 0;

    while (XPending(d) > 0) {
        XNextEvent(d, &event);
        if (IsAutoRepeat()) {
            break;
        }
        switch (event.type) {
            case ButtonPress:
                mouse_clicked = true;
                mouse_x = event.xbutton.x;
                mouse_y = event.xbutton.y;
                break;
            case ButtonRelease:
                mouse_released = true;
                mouse_x = event.xbutton.x;
                mouse_y = event.xbutton.y;
                break;
            case KeyPress:
                key_pressed = true;
                got_keycode = event.xkey.keycode;
                break;
            case KeyRelease:
                key_released = true;
                got_keycode = event.xkey.keycode;
                break;
            default:
                break;
        }
    }
}

/**
 * @brief fill the window with black or white. 
 * 
 * @param erase Setting this to true will fill it with white.
 */
void GUIRUF::FillWindow(bool erase) {
    if(!d) return;
    XSetForeground(d, gc, erase ? white : black);
    XFillRectangle(d, wr, gc, 0, 0, window_width, window_height);
    if(d) XFlush(d);
}

/**
 * @brief draw a point on the window
 * 
 * @param x 
 * @param y 
 * @param erase Setting this to true will draw a white dot.
 */
void GUIRUF::DrawPoint(int x, int y, bool erase) {
    if(!d) return;
    XSetForeground(d, gc, erase ? white : black);
    XDrawPoint(d, wr, gc, x, y);
    if(d) XFlush(d);
}

/**
 * @brief draw a line on the window
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @param erase Setting this to true will draw a white line.
 */
void GUIRUF::DrawLine(int x1, int y1, int x2, int y2, bool erase) {
    if(!d) return;
    XSetForeground(d, gc, erase ? white : black);
    XDrawLine(d, wr, gc, x1, y1, x2, y2);
    if(d) XFlush(d);
}

bool GUIRUF::IsMouseClicked() {
    return mouse_clicked;
}

bool GUIRUF::IsMouseReleased() {
    return mouse_released;
}

/**
 * @brief return the mouse position.
 * 
 * @return std::vector<int> {x, y}
 */
std::vector<int> GUIRUF::LocateMouse() {
    return {mouse_x, mouse_y};
}

bool GUIRUF::IsKeyPressed() {
    return key_pressed;
}

bool GUIRUF::IsKeyPressed(int *keycode) {
    *keycode = got_keycode;
    return key_pressed;
}

bool GUIRUF::IsKeyReleased() {
    return key_released;
}

bool GUIRUF::IsKeyReleased(int *keycode) {
    *keycode = got_keycode;
    return key_released;
}

bool GUIRUF::IsAutoRepeat() {
    if (event.type == KeyRelease) {
        if (XEventsQueued(d, QueuedAfterReading)) {
            XEvent next_event;
            XPeekEvent(d, &next_event);
            if (next_event.type == KeyPress &&
                next_event.xkey.time == event.xkey.time &&
                next_event.xkey.keycode == event.xkey.keycode) {
                XNextEvent(d, &next_event); 
                return true;
            }
        }
    }
    return false;
}