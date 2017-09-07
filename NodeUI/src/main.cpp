//デバッグモードの時は下のコメントアウトを外す
#define NUI_DEBUG

#include <Windows.h>
#include <iostream>

#include "lib/NodeUI/NodeUI.h"

int main(int argc, LPSTR argv[]) {
	nui::GLManagement::init();

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