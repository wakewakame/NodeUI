//デバッグモードの時は下のコメントアウトを外す
#define NUI_DEBUG

#include <iostream>

#include "lib/NodeUI/NodeUI.h"

int main() {
	if (nui::GLManagement::init()) return 1;

	while (!nui::GLManagement::loop()) {
		//バッファに描画
		glFlush();

		//カラーバッファを入れ替える
		glfwSwapBuffers(nui::Window::getGLFWHwnd());
	}

	nui::GLManagement::exit();
	std::cout << "finish" << std::endl;
	std::getchar();
	return 0;
}