//�f�o�b�O���[�h�̎��͉��̃R�����g�A�E�g���O��
#define NUI_DEBUG

#include <iostream>

#include "lib/NodeUI/NodeUI.h"

int main() {
	if (nui::GLManagement::init()) return 1;

	while (!nui::GLManagement::loop()) {
		//�o�b�t�@�ɕ`��
		glFlush();

		//�J���[�o�b�t�@�����ւ���
		glfwSwapBuffers(nui::Window::getGLFWHwnd());
	}

	nui::GLManagement::exit();
	std::cout << "finish" << std::endl;
	std::getchar();
	return 0;
}