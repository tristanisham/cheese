#pragma once
#include "raygui.h"

#include <iostream>
#include <vector>
#include "objects/mouse.hpp"
namespace cheese {

    class IndexLayout {
    private:
        // Define controls variables
        Rectangle ScrollPanelScrollView = {0, 0, 0, 0};
        Vector2 ScrollPanelScrollOffset = {0, 0};
        Vector2 ScrollPanelBoundsOffset = {0, 0};            // ScrollPanel: ScrollPanel
        int ListViewScrollIndex = 0;
        int ListViewActive = 0;            // ListView: ListView
        int screenWidth;
        int screenHeight;

        std::vector<Rectangle> layoutRecs;
        Vector2 anchor01 = {0, 0};            // ANCHOR ID:1
        Point<float> mouse{};
        // methods


    public:
        std::string groupBoxText = "Controls";
        std::string recordButtonText = "Record";
        std::string listViewText = "A;B;C";
        std::string statusBarText = "Sample Text";
        std::string scrollPanelText = "Scroll Text";

        IndexLayout(int width, int height): screenWidth(width), screenHeight(height) {
            this->layoutRecs = {

                    {anchor01.x + 240, anchor01.y + 48, 840,  695},    // ScrollPanel: ScrollPanel

                    {anchor01.x + 0,   anchor01.y + 8,  1080, 720},    // GroupBox: GroupBox

                    {anchor01.x + 960, anchor01.y + 25, 120,  24},    // Button: RecordButton

                    {anchor01.x + 3,   anchor01.y + 24, 238,  720},    // ListView: ListView

                    {anchor01.x + 840, anchor01.y + 25, 120,  24},    // StatusBar: StatusBar
            };
        }

        void draw();
        void update();
        void recordButton();
    };


}

void RecordButton();