#pragma once
#include "raygui.h"
#include <iostream>
#include <vector>
#include "objects/mouse.hpp"


namespace cheese {

	class IndexLayout {
	private:
		// Define controls variables



		int MacroListScrollIndex = 0;
		int MacroListActive = 0;            // ListView: ListView
		int screenWidth;
		int screenHeight;


		std::vector<Rectangle> layoutRecs;
		Vector2 anchor = { 0, 0 };            // ANCHOR ID:1
		/*Point<float> mouse{};*/
		Mouse mouse{};
		// methods


	public:
		// layout_name: controls initialization
		//----------------------------------------------------------------------------------
		// Const text
		std::string GroupText = "Macros";    // GROUPBOX: GroupBox000
		std::string RecordButtonText = "Record";    // BUTTON: RecordButton
		std::string MacroListText = "ONE;TWO;THREE";    // LISTVIEW: MacroList
		std::string StatusBarText = "#21# (0,0)";    // STATUSBAR: StatusBar
		std::string SaveButtonText = "Save";    // BUTTON: SaveButton
		std::string ReplayButtonText = "Replay";    // BUTTON: ReplayButton
		std::string LabelRecordText = "Record your mouse";    // LABEL: LabelRecord
		std::string LabelSaveText = "Save your recording";    // LABEL: LabelSave
		std::string DeleteButtonText = "Delete ";    // BUTTON: DeleteButton

		IndexLayout(int width, int height) : screenWidth(width), screenHeight(height) {
			this->layoutRecs = {
				{
					anchor.x + 0, anchor.y + 8, 616, 512
				},    // GroupBox: GroupBox000
				{
					anchor.x + 328, anchor.y + 184, 120, 24
				},    // Button: RecordButton
				{
					anchor.x + 0, anchor.y + 16, 184, 480
				},    // ListView: MacroList
				{
					anchor.x + 184, anchor.y + 16, 432, 24
				},    // StatusBar: StatusBar
				{
					anchor.x + 328, anchor.y + 256, 120, 24
				},    // Button: SaveButton
				{
					anchor.x + 0, anchor.y + 496, 88, 24
				},    // Button: ReplayButton
				{
					anchor.x + 328, anchor.y + 160, 120, 24
				},    // Label: LabelRecord
				{
					anchor.x + 328, anchor.y + 232, 144, 24
				},    // Label: LabelSave
				{
					anchor.x + 88, anchor.y + 496, 96, 24
				},    // Button: DeleteButton
			};


		}

		void draw();
		void update();
		// function buttons
		void recordButton();
		void saveButton();
		void replayButton();
		void deleteButton();
	};


}
