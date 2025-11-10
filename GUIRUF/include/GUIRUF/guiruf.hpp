/**
 * @file guiruf.hpp
 * @author ToriStick (printf314@gmail.com)
 * @brief GUIRUF (GUI of Removed Unneeded Functions)
 * @version 1.0
 * @date 2025-11-10
 * 
 * @copyright Copyright (c) 2025 ToriStick
 * 
 */

#ifndef GUIRUF_HPP_
#define GUIRUF_HPP_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <vector>
#include <string>

/**
 * @brief GUIRUF class
 * @details 
 * This class provides the minimum necessary functionality of GUI.
 */
class GUIRUF{
    public:
        GUIRUF();
        GUIRUF(int width, int height);
        ~GUIRUF();
        void UpdateEvents();
        void FillWindow(bool erase=false);
        void DrawPoint(int x, int y, bool erase=false);
        void DrawLine(int x1, int y1, int x2, int y2, bool erase=false);
        bool IsMouseClicked();
        bool IsMouseReleased();
        std::vector<int> LocateMouse();
        bool IsKeyPressed();
        bool IsKeyPressed(int *keycode);
        bool IsKeyReleased();
        bool IsKeyReleased(int *keycode);

    private:
        Display *d = nullptr;
        Window wr;
        GC gc;
        XEvent event;
        unsigned long black, white;
        bool mouse_clicked = false, mouse_released = false;
        bool key_pressed = false, key_released = false;
        int mouse_x = 0, mouse_y = 0;
        int window_width = 500, window_height = 500;
        int got_keycode = 0;

        bool IsAutoRepeat();
};

#endif //!GUIRUF_HPP_