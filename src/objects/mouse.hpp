//
// Created by Tristan on 8/27/2024.
//
#pragma once

#include <memory>
#include <string>
#include "errors.hpp"
#include "nlohmann/json.hpp"
#include <vector>
using json = nlohmann::json;
#include <chrono>

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
	private:
		class TimePoint {

			long long timestamp;
			Point<float> coords;
		public:
			TimePoint(Point<float> p) : coords(p) {
				const auto init = std::chrono::system_clock::now();
				this->timestamp = std::chrono::duration_cast<std::chrono::seconds>(init.time_since_epoch()).count();
			}

			json serialize();
		};

		std::vector<TimePoint> buffer{};


	public:
		float x;
		float y;



		Point<float> pos() const {
			return Point<float>{this->x, this->y};
		}

		// LeftClick clicks the left button of the mouse at its current position.
		void leftClick() const;

		// RightClick clicks the right button of the mouse at its current position.
		void rightClick() const;

		void save();

		json serialize();


	};


}