/*

[GLManagement�N���X]
	[�}�N��]
		NUI_DEBUG����`����Ă���ƁA�E�B���h�E�Ƃ͕ʂɃR���\�[�����\�������

	[�֐�]
		init()
			�������֐�
			�ق��̊֐����g�p����O�ɂ��̊֐������s����

		loop()
			���t���[�����s���ׂ��֐�

		exit()
			�I�����Ɏ��s���ׂ��֐�

*/


#pragma once

//�R���\�[����\����
#ifndef NUI_DEBUG
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

#include "common.h"

namespace nui {
	class GLManagement {
	public:
		static bool init() {
			// GLFW������
			if (glfwInit() == GL_FALSE) return 1;

			// OpenGL Version 4.3���w��
			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

			// �E�B���h�E����
			if (Window::createWindow()) return 1;

			// GLEW������
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK) return 1;
			
			// �E�B���h�E�T�C�Y�w��
			Window::setSize(Window::SIZE(640, 480));

			// ���������̃^�C�~���O��҂�
			glfwSwapInterval(1);

			// �f�t�H���g�Ńu�����h���[�h�L����
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // �A���t�@�u�����h�K�p

			// �f�t�H���g�ŃA���`�G�C���A�X�K��
			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // �_�̃A���`�G�C���A�X���x�ő剻
			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // ���̃A���`�G�C���A�X���x�ő剻
			glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST); // �ʂ̃A���`�G�C���A�X���x�ő剻
			glEnable(GL_POINT_SMOOTH); // �_
			glEnable(GL_LINE_SMOOTH); // ��
			glEnable(GL_POLYGON_SMOOTH); // ��

			return 0;
		}
		static bool loop() {
			// �E�B���h�E���J���Ă���ԌJ��Ԃ�
			if (glfwWindowShouldClose(Window::getGLFWHwnd()) != GL_FALSE) return 1;

			// nui����loop�֐������ׂĎ��s
			if (Window::loop()) return 1;
			// �}�E�X�C�x���g�擾
			Mouse::loop();

			// �C�x���g����������܂őҋ@
			glfwPollEvents();

			return 0;
		}
		static void exit() {
			glfwTerminate();
		}
	};
}