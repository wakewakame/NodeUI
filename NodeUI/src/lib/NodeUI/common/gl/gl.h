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
		struct VERSION {
			char major;
			char minor;
			VERSION();
			VERSION(char set_major, char set_minor);
		};
	private:
		static VERSION gl_version;
	public:
		static bool init(VERSION set_gl_version = VERSION());
		static bool loop();
		static void exit();
		static inline GLManagement::VERSION GLManagement::getVersion() { return gl_version; }
	};
}