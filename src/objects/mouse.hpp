//
// Created by Tristan on 8/27/2024.
//
#pragma once

#include <memory>
#include <string>
#include "errors.hpp"

namespace cheese {

    template<typename T>
    class Point {
    public:
        T x;
        T y;

        Point(T X, T Y) : x(X), y(Y) {};

        Point() = default;
    };
// TODO: refactor this for cleaner platform specific code.
#if defined(_WIN32)

    Point<float> winMousePos();

    void winMouseClick();

    std::string getLastErrorAsString();

#endif

    class Mouse {
    public:
        float x;
        float y;


        static Point<float> pos();

        // LeftClick clicks the left button of the mouse at its current position.
        void LeftClick() const;

        // RightClick clicks the right button of the mouse at its current position.
        void RightClick() const;

    };


}