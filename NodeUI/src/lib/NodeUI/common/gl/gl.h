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

#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <string>
#include <functional>

#include "window.h"
#include "mouse.h"
#include "keyboard.h"

namespace nui {
	class GLManagement {
	public:
		static bool init() {
			// GLFW������
			if (glfwInit() == GL_FALSE) return 1;

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL Version 4.x���w��
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // OpenGL Version x.5���w��
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true); // �Â��@�\���g���Ȃ�����			
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // �R�A�v���t�@�C���w��		
			glfwWindowHint(GLFW_SAMPLES, 4); // �A���`�G�C���A�X��L����

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
			if (Mouse::loop()) return 1;

			return 0;
		}
		static void exit() {
			glfwTerminate();
		}
	};
}