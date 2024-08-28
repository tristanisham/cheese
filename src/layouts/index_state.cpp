#include "index.hpp"
#include <format>
#include <memory>
#include "objects/mouse.hpp"


void cheese::IndexLayout::recordButton() {}

void cheese::IndexLayout::update() {
    try {
        auto winMp = cheese::winMousePos();
        this->mousePos.y = winMp.y;
        this->mousePos.x = winMp.x;
    } catch (std::exception& err) {
        // TODO: add better support for Linux and MacOS
        auto genMP = GetMousePosition();
        std::cerr << err.what() << std::endl;
        this->mousePos.y = genMP.y;
        this->mousePos.x = genMP.x;
    }

//    std::cout << this->ListViewActive << std::endl;
}

void cheese::IndexLayout::draw() {
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    GuiScrollPanel(
            {this->layoutRecs[0].x, this->layoutRecs[0].y, this->layoutRecs[0].width - this->ScrollPanelBoundsOffset.x,
             this->layoutRecs[0].height - this->ScrollPanelBoundsOffset.y}, this->scrollPanelText.c_str(),
            this->layoutRecs[0],
            &ScrollPanelScrollOffset, &ScrollPanelScrollView);

    GuiGroupBox(this->layoutRecs[1], this->groupBoxText.c_str());

    if (GuiButton(this->layoutRecs[2], this->recordButtonText.c_str())) this->recordButton();

    GuiListView(this->layoutRecs[3], this->listViewText.c_str(), &ListViewScrollIndex, &ListViewActive);

    GuiStatusBar(this->layoutRecs[4], this->statusBarText.c_str());



    this->statusBarText = std::format("X: {}, Y: {}", this->mousePos.x, this->mousePos.y);
}