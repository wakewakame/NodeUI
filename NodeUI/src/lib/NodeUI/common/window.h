#pragma once

#include <string>
#include <Windows.h>
#include <functional>

namespace nui {
	class Window {
	public:
		using SIZE = glm::ivec2;
		using TITLE = std::string;
		using FPS = double;
		using SPEED = double;
		using RESIZE_FLAG = bool;
		using WINDOW_HANDLE = HWND;
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
		static WINDOW_HANDLE hwnd; // �E�B���h�E�n���h��
		static GLFW_HANDLE gl_hwnd; // GL�E�B���h�E�n���h��
		// ���T�C�Y�C�x���g�����p
		static void resize(GLFWwindow *window, int width, int heigh) {
			setSize(glm::ivec2(width, heigh));
		}
		// �N���[�Y�C�x���g�����p
		static void close(GLFWwindow *window) {
			close_event();
		}
		// �f�t�H���g�N���[�Y�C�x���g����
		static void default_close_event() {}

	public:
		static CLOSE close_event; // �N���[�Y�C�x���g�֐�

		static bool loop() {
			// �E�B���h�E���T�C�Y�t���O�m�F
			resize_flag = (size != size_buf);
			size_buf = size;

			// FPS����
			fps = 1.0 / glfwGetTime();
			speed = std_fps / fps;
			glfwSetTime(0.0);

			return 0;
		}
		static bool setSize(SIZE set_size) {
			size = set_size;

			// �E�B���h�E�T�C�Y�ύX
			glfwSetWindowSize(gl_hwnd, size.x, size.y);

			// �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
			glViewport(0, 0, size.x, size.y);

			// �ϊ��s��̏�����
			glLoadIdentity();

			// �X�N���[����̕\���̈���r���[�|�[�g�̑傫���ɔ�Ⴓ����
			glOrtho(0.0, (double)size.x, (double)size.y, 0.0, -1.0, 1.0);

			return 0;
		}
		static bool setTitle(TITLE set_title) {
			title = set_title;
			glfwSetWindowTitle(gl_hwnd, title.c_str());
			return 0;
		}
		static bool setStdFps(FPS set_std_fps) {
			std_fps = set_std_fps;
			return 0;
		}
		static bool setGLFWHwnd(GLFW_HANDLE set_gl_hwnd) {
			gl_hwnd = set_gl_hwnd;

			// �E�B���h�E�n���h���擾
			HDC glDc = wglGetCurrentDC();
			hwnd = WindowFromDC(glDc);

			// �E�B���h�E���T�C�Y�C�x���g�����֐��o�^
			glfwSetWindowSizeCallback(gl_hwnd, resize);
			// �E�B���h�E�N���[�Y�C�x���g�����֐��o�^
			glfwSetWindowCloseCallback(gl_hwnd, close);

			return 0;
		}
		static SIZE getSize() {
			return size;
		}
		static TITLE getTitle() {
			return title;
		}
		static FPS getFps() {
			return fps;
		}
		static FPS getStdFps() {
			return std_fps;
		}
		static SPEED getSpeed() {
			return speed;
		}
		static RESIZE_FLAG getResizeFlag() {
			return resize_flag;
		}
		static WINDOW_HANDLE getHwnd() {
			return hwnd;
		}
		static GLFW_HANDLE getGLFWHwnd() {
			return gl_hwnd;
		}
	};
	Window::SIZE Window::size = Window::SIZE(640, 480);
	Window::SIZE Window::size_buf = size;
	Window::TITLE Window::title = "";
	Window::FPS Window::fps = 0.0;
	Window::FPS Window::std_fps = 60.0;
	Window::SPEED Window::speed = 1.0;
	Window::RESIZE_FLAG Window::resize_flag = 0;
	Window::WINDOW_HANDLE Window::hwnd = nullptr;
	Window::GLFW_HANDLE Window::gl_hwnd = nullptr;
	Window::CLOSE Window::close_event = Window::default_close_event;
}