//デバッグモードの時は下のコメントアウトを外す
#define NUI_DEBUG

#include <iostream>

#include "lib/NodeUI/NodeUI.h"

int main() {
	if (nui::Draw::init()) return 1;

	while (true) {
		nui::Draw::clear();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		nui::Draw::setColor(0.0f, 0.5f, 0.78f, 1.0f);
		nui::Draw::box(
			nui::Mouse::getCursor().x - 100,
			nui::Mouse::getCursor().y - 100,
			nui::Mouse::getCursor().x + 100,
			nui::Mouse::getCursor().y + 100
		);


		nui::Draw::drawPoint(GL_LINE_STRIP);

		if (nui::Draw::render()) break;
	}

	nui::Draw::exit();
	return 0;
}