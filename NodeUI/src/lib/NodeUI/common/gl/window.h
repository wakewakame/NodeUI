/*

[Window�N���X]
[��`]
using SIZE = glm::ivec2
using TITLE = std::string
using FPS = double
using SPEED = double
using RESIZE_FLAG = bool
using GLFW_HANDLE = GLFWwindow*
using CLOSE = std::function<void()>

[�ϐ�]
CLOSE close_event
�E�B���h�E�N���[�Y���ɏ��������֐��������邽�߂̌^

[�֐�]
bool loop()
���t���[�����s���ׂ��֐�
GLManagement�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢
�߂�l:����:0,�G���[:1

bool setSize(SIZE set_size)
�E�B���h�E�T�C�Y��set_size�ɕύX����
����1:�E�B���h�E�T�C�Y
�߂�l:����:0,�G���[:1

bool setPos(SIZE set_pos)
�E�B���h�E�ʒu��set_pos�ɕύX����
����1:�E�B���h�E���W
�߂�l:����:0,�G���[:1

bool setTitle(TITLE set_title)
�E�B���h�E�^�C�g����set_title�ɕύX����
����1:�E�B���h�E�^�C�g����
�߂�l:����:0,�G���[:1

bool setStdFps(FPS set_std_fps)
getSpeed�֐��̌v�Z��ƂȂ�t���[�����[�g��set_std_fps�ɂ���
�f�t�H���g�̃t���[�����[�g��60.0
���A���ۂɕ`�悳���t���[�����[�g�Ƃ̊֌W�͂Ȃ�
����1:�t���[�����[�g��
�߂�l:����:0,�G���[:1

bool createWindow()
�E�B���h�E�𐶐�����
GLManagement�N���X�����s���邽�߁A�ʏ�͌Ăяo���Ȃ��Ă悢
�߂�l:����:0,�G���[:1

SIZE getSize()
���݂̃E�B���h�E�̑傫�����擾����

TITLE getTitle()
���݂̃E�B���h�E�^�C�g�����擾����

FPS getFps()
���݂̃t���[�����[�g���擾����

FPS getStdFps()
���݂�getSpeed�֐��̌v�Z��ƂȂ�t���[�����[�g���擾����

SPEED getSpeed()
1�t���[��������̃A�j���[�V�������x���Z�o����֐�
setStdFps�Ŏw�肳�ꂽ�t���[�����[�g�̂Ƃ��̃A�j���[�V�������x��1�Ƃ��A
���݂̃t���[�����[�g���������Ȃ�ɂ�A�A�j���[�V�������x�͑傫���Ȃ�
���݂̃t���[�����[�g���傫���Ȃ�ɂ�A�A�j���[�V�������x�͏������Ȃ�
�v�Z���e�� setStdFps�Ŏw�肳�ꂽ�t���[�����[�g / ���݂̃t���[�����[�g
�t���[�����[�g�ɂ��A�j���[�V�������x�Ƀ������o��̂�h��

RESIZE_FLAG getResizeFlag()
�E�B���h�E�T�C�Y���X�V���ꂽ����̃t���[���̂�1�ɂȂ�

GLFW_HANDLE getGLFWHwnd()
GLFW�E�B���h�E�n���h���擾

*/

#pragma once
#include "gl.h"

namespace nui {
	class Window {
	public:
		using SIZE = glm::ivec2;
		using TITLE = std::string;
		using FPS = double;
		using SPEED = double;
		using RESIZE_FLAG = bool;
		using GLFW_HANDLE = GLFWwindow*;
		using CLOSE = std::function<void()>;

	private:
		static SIZE size; // �E�B���h�E�T�C�Y
		static SIZE size_buf; // 1�t���[���O�̃E�B���h�E�T�C�Y
		static TITLE title; // �E�B���h�E�^�C�g��
		static FPS fps; // ���݂̃t���[�����[�g
		static FPS std_fps; // fps��l (�A�j���[�V�������x�̒��ߗp)
		static SPEED speed; // std_fps / fps (�A�j���[�V�������x�̒��ߗp)
		static RESIZE_FLAG resize_flag; // �E�B���h�E���T�C�Y�t���O
		static GLFW_HANDLE gl_hwnd; // GL�E�B���h�E�n���h��
									// ���T�C�Y�C�x���g�����p
		static void resize_func(GLFWwindow *window, int width, int heigh);
		// �N���[�Y�C�x���g�����p
		static void close_func(GLFWwindow *window);
		// �f�t�H���g�N���[�Y�C�x���g����
		static void default_close_event();

	public:
		static CLOSE close_event; // �N���[�Y�C�x���g�֐�

		static bool init();
		static bool loop();
		static bool setPos(SIZE set_pos);
		static bool setSize(SIZE set_size);
		static bool setTitle(TITLE set_title);
		static bool setStdFps(FPS set_std_fps);
		static bool createWindow();
		static inline Window::SIZE Window::getSize() { return size; }
		static inline Window::TITLE Window::getTitle() { return title; }
		static inline Window::FPS Window::getFps() { return fps; }
		static inline Window::FPS Window::getStdFps() { return std_fps; }
		static inline Window::SPEED Window::getSpeed() { return speed; }
		static inline Window::RESIZE_FLAG Window::getResizeFlag() { return resize_flag; }
		static inline Window::GLFW_HANDLE Window::getGLFWHwnd() { return gl_hwnd; }
	};
}