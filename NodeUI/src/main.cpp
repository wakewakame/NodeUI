//デバッグモードの時は下のコメントアウトを外す
#define NUI_DEBUG

#include <iostream>

#include "lib/NodeUI/NodeUI.h"

int main() {
	if (nui::Draw::init()) return 1;

	while (!nui::Draw::draw()) {

	}

	nui::Draw::exit();

	return 0;
}