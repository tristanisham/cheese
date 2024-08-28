#include "index.hpp"
#include <format>
#include <memory>
#include "objects/mouse.hpp"


void cheese::IndexLayout::recordButton() {}
void cheese::IndexLayout::saveButton() {}
void cheese::IndexLayout::replayButton() {}
void cheese::IndexLayout::deleteButton() {}

void cheese::IndexLayout::update() {
	try {
		auto winMp = cheese::winMousePos();
		this->mouse.y = winMp.y;
		this->mouse.x = winMp.x;
	}
	catch (std::exception& err) {
		// TODO: add better support for Linux and MacOS
		auto genMP = GetMousePosition();
		std::cerr << err.what() << std::endl;
		this->mouse.y = genMP.y;
		this->mouse.x = genMP.x;
	}

	//    std::cout << this->ListViewActive << std::endl;
}

void cheese::IndexLayout::draw() {
	ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

	// raygui: controls drawing
			//----------------------------------------------------------------------------------
			// Draw controls
	GuiGroupBox(layoutRecs[0], GroupText.c_str());

	if (GuiButton(layoutRecs[1], RecordButtonText.c_str())) recordButton();

	GuiListView(layoutRecs[2], MacroListText.c_str(), &MacroListScrollIndex, &MacroListActive);

	GuiStatusBar(layoutRecs[3], StatusBarText.c_str());

	if (GuiButton(layoutRecs[4], SaveButtonText.c_str())) saveButton();

	if (GuiButton(layoutRecs[5], ReplayButtonText.c_str())) replayButton();

	GuiLabel(layoutRecs[6], LabelRecordText.c_str());
	GuiLabel(layoutRecs[7], LabelSaveText.c_str());

	if (GuiButton(layoutRecs[8], DeleteButtonText.c_str())) deleteButton();


	this->StatusBarText = std::format("#21# ({},{})", this->mouse.x, this->mouse.y);
}