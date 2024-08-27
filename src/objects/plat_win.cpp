//
// Created by Tristan on 8/27/2024.
//
#if defined(_WIN32)

#include <Windows.h>

#endif

#include "mouse.hpp"


#if defined(_WIN32)
std::string cheese::getLastErrorAsString() {
    // Get the error code
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return {}; // No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;
    // Use FormatMessage to get the message string from the error code
    size_t size = FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            errorMessageID,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR) &messageBuffer,
            0,
            nullptr
    );

    std::string message(messageBuffer, size);

    // Free the buffer allocated by FormatMessage
    LocalFree(messageBuffer);

    return message;
}

// winMousePos find the position of the mouse on Windows. Should eventually be made private and wrapped
// into a single mousePos function.
cheese::Point<float> cheese::winMousePos() {
    Point<float> mouse{};
    // This way Cheese can get the cursor position outside of the window's bounds.
    std::unique_ptr<POINT> point = std::make_unique<POINT>();
    if (!GetCursorPos(point.get())) {
        throw std::exception(cheese::getLastErrorAsString().c_str());
    }

    mouse.x = static_cast<float>(point->x);
    mouse.y = static_cast<float>(point->y);
    return mouse;
}

void cheese::winMouseClick() {

}
#endif

cheese::Point<float> cheese::Mouse::pos() {
#if defined(_WIN32)
    return winMousePos();
#else
    throw cheese::ErrUnsupportedPlatform("This function is only available on Windows");
#endif
}


void cheese::Mouse::LeftClick() const {
#if defined(_WIN32)
    SetCursorPos(static_cast<int>(this->x), static_cast<int>(this->y));
    // Set up the input structure
    INPUT inputs[2] = {};

    // Set up the mouse down event (left button down)
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    // Set up the mouse up event (left button up)
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;

    // Send the input events to the system
    SendInput(2, inputs, sizeof(INPUT));
#else
    throw cheese::ErrUnsupportedPlatform("This function is only available on Windows");
#endif
}

void cheese::Mouse::RightClick() const {
#if defined(_WIN32)
    SetCursorPos(static_cast<int>(this->x), static_cast<int>(this->y));

    INPUT inputs[2] = {};

    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    SendInput(2, inputs, sizeof(INPUT));
#else
    throw cheese::ErrUnsupportedPlatform("This function is only available on Windows");
#endif
}