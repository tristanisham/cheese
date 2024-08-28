#include "mouse.hpp"


json cheese::Mouse::TimePoint::serialize() {
    json j = {
            {"t", this->timestamp},
            {"x", this->coords.x},
            {"y", this->coords.y},
    };

    return j;
}

json cheese::Mouse::serialize() {
    json j{};
    for (TimePoint &tp: this->buffer) {
        j.push_back(tp.serialize());
    }

    return j;
}

void cheese::Mouse::save() {
    auto tp = TimePoint{this->pos()};
    this->buffer.push_back(tp);
}