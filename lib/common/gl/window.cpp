#include "window.h"

namespace nui {
	// ���T�C�Y�C�x���g�����p
	void Window::resize_func(GLFWwindow *window, int width, int heigh) {
		setSize(glm::ivec2(width, heigh));
	}
	// �N���[�Y�C�x���g�����p
	void Window::close_func(GLFWwindow *window) {
		close_event();
	}
	// �f�t�H���g�N���[�Y�C�x���g����
	void Window::default_close_event() {}

	Window::CLOSE Window::close_event; // �N���[�Y�C�x���g�֐�

	bool Window::init() {
		close_event = default_close_event;
		return 0;
	}
	bool Window::loop() {
		// �E�B���h�E���T�C�Y�t���O�m�F
		resize_flag = (size != size_buf);
		size_buf = size;

		// FPS����
		fps = 1.0 / glfwGetTime();
		speed = std_fps / fps;
		glfwSetTime(0.0);

		return 0;
	}
	bool Window::setPos(SIZE set_pos) {
		// �E�B���h�E�ʒu�ύX
		glfwSetWindowPos(gl_hwnd, set_pos.x, set_pos.y);

		return 0;
	}
	bool Window::setSize(SIZE set_size) {
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
	bool Window::setTitle(TITLE set_title) {
		title = set_title;
		glfwSetWindowTitle(gl_hwnd, title.c_str());
		return 0;
	}
	bool Window::setStdFps(FPS set_std_fps) {
		std_fps = set_std_fps;
		return 0;
	}
	bool Window::createWindow() {
		// �E�B���h�E����
		gl_hwnd = glfwCreateWindow(
			getSize().x,
			getSize().y,
			getTitle().c_str(),
			NULL,
			NULL
		);

		// �����m�F
		if (gl_hwnd == NULL) return NULL;

		// ���������E�B���h�E��OpenGL�̏����Ώۂɂ���
		glfwMakeContextCurrent(gl_hwnd);

		// �E�B���h�E���T�C�Y�C�x���g�����֐��o�^
		glfwSetWindowSizeCallback(gl_hwnd, resize_func);
		// �E�B���h�E�N���[�Y�C�x���g�����֐��o�^
		glfwSetWindowCloseCallback(gl_hwnd, close_func);

		return 0;
	}

	Window::SIZE Window::size = Window::SIZE(640, 480);
	Window::SIZE Window::size_buf = size;
	Window::TITLE Window::title = "";
	Window::FPS Window::fps = 0.0;
	Window::FPS Window::std_fps = 60.0;
	Window::SPEED Window::speed = 1.0;
	Window::RESIZE_FLAG Window::resize_flag = 1;
	Window::GLFW_HANDLE Window::gl_hwnd = nullptr;
}