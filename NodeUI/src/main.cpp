//デバッグモードの時は下のコメントアウトを外す
#define NUI_DEBUG

#include <iostream>

#include "lib/NodeUI/NodeUI.h"

int main() {
	if (nui::Draw::init()) return 1;

	while (true) {
		nui::Draw::clear();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		nui::Draw::setColor(1.0f, 0.0f, 0.0f, 1.0f);
		nui::Draw::addPoint(0.0f, 0.0f);
		nui::Draw::setColor(0.0f, 1.0f, 0.0f, 1.0f);
		nui::Draw::addPoint((float)nui::Window::getSize().x, 0.0f);
		nui::Draw::setColor(0.0f, 0.0f, 1.0f, 1.0f);
		nui::Draw::addPoint((float)nui::Window::getSize().x - 100.0f, (float)nui::Window::getSize().y - 100.0f);
		nui::Draw::setColor(1.0f, 1.0f, 0.0f, 1.0f);
		nui::Draw::addPoint(0.0f, (float)nui::Window::getSize().y);

		nui::Draw::addPoint((float)nui::Window::getSize().x, (float)nui::Window::getSize().y);

		nui::Draw::drawPoint(GL_LINE_STRIP);

		if (nui::Draw::render()) break;
	}

	nui::Draw::exit();
	return 0;
}