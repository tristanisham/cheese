//
// Created by Tristan on 8/27/2024.
//
#pragma once

#include <exception>
#include <string>

namespace cheese {
    class ErrUnsupportedPlatform : public std::exception {
    public:
        explicit ErrUnsupportedPlatform(const std::string &message) : message_(message) {}

        [[nodiscard]] const char *what() const noexcept override {
            return message_.c_str();
        }

    private:
        std::string message_;
    };

}
