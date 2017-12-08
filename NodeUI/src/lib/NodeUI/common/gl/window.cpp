#include "window.h"

namespace nui {
	// リサイズイベント処理用
	void Window::resize_func(GLFWwindow *window, int width, int heigh) {
		setSize(glm::ivec2(width, heigh));
	}
	// クローズイベント処理用
	void Window::close_func(GLFWwindow *window) {
		close_event();
	}
	// デフォルトクローズイベント処理
	void Window::default_close_event() {}

	Window::CLOSE Window::close_event; // クローズイベント関数

	bool Window::init() {
		close_event = default_close_event;
		return 0;
	}
	bool Window::loop() {
		// ウィンドウリサイズフラグ確認
		resize_flag = (size != size_buf);
		size_buf = size;

		// FPS測定
		fps = 1.0 / glfwGetTime();
		speed = std_fps / fps;
		glfwSetTime(0.0);

		return 0;
	}
	bool Window::setPos(SIZE set_pos) {
		// ウィンドウ位置変更
		glfwSetWindowPos(gl_hwnd, set_pos.x, set_pos.y);

		return 0;
	}
	bool Window::setSize(SIZE set_size) {
		size = set_size;

		// ウィンドウサイズ変更
		glfwSetWindowSize(gl_hwnd, size.x, size.y);

		// ウィンドウ全体をビューポートにする
		glViewport(0, 0, size.x, size.y);

		// 変換行列の初期化
		glLoadIdentity();

		// スクリーン上の表示領域をビューポートの大きさに比例させる
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
		// ウィンドウ生成
		gl_hwnd = glfwCreateWindow(
			getSize().x,
			getSize().y,
			getTitle().c_str(),
			NULL,
			NULL
		);

		// 成功確認
		if (gl_hwnd == NULL) return NULL;

		// 生成したウィンドウをOpenGLの処理対象にする
		glfwMakeContextCurrent(gl_hwnd);

		// ウィンドウリサイズイベント処理関数登録
		glfwSetWindowSizeCallback(gl_hwnd, resize_func);
		// ウィンドウクローズイベント処理関数登録
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