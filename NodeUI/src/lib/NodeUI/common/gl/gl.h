/*

[GLManagement�N���X]
	[�}�N��]
		NUI_DEBUG����`����Ă���ƁA�E�B���h�E�Ƃ͕ʂɃR���\�[�����\�������

	[��`]
		struct VERSION{
			char major; // OpenGL��major�o�[�W����
			char minor; // OpenGL��minor�o�[�W����
		}

	[�֐�]
		bool init(VERSION set_gl_version)
			�������֐�
			DrawBase�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢
			�ق��̊֐����g�p����O�ɂ��̊֐������s����
			�߂�l:����:0,�G���[:1

		bool loop()
			���t���[�����s���ׂ��֐�
			DrawBase�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢
			�߂�l:����:0,�G���[:1

		void exit()
			�I�����Ɏ��s���ׂ��֐�
			DrawBase�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢

		VERSION getVersion()
			���ݎw�肳��Ă���OpenGL�̃o�[�W�������擾����
			�߂�l:���ݎw�肳��Ă���OpenGL�̃o�[�W����

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
		struct VERSION{
			char major;
			char minor;
			VERSION() {
				major = 4;
				minor = 5;
			}
			VERSION(char set_major, char set_minor) {
				major = set_major;
				minor = set_minor;
			}
		};
	private:
		static VERSION gl_version;
	public:
		static bool init(VERSION set_gl_version = VERSION()) {
			// GLFW������
			if (glfwInit() == GL_FALSE) return 1;

			gl_version = set_gl_version;

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version.major); // OpenGL Version 4.x���w��
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version.minor); // OpenGL Version x.5���w��
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac�p
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // �Â��@�\���g���Ȃ�����		
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
		static inline VERSION getVersion() { return gl_version; }
	};
	GLManagement::VERSION GLManagement::gl_version;
}