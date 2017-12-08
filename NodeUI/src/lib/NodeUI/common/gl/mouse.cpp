#include "mouse.h"

namespace nui {
	Mouse::CLICK::CLICK() {
		l = 0;
		r = 0;
		w = 0;
	}

	// ホイールイベント処理用
	void Mouse::wheel_func(GLFWwindow *window, double x, double y) {
		wheel_buf.x += x;
		wheel_buf.y += y;
	}
	// 初期化関数
	void Mouse::init() {
		glfwSetScrollCallback(Window::getGLFWHwnd(), wheel_func);
	}

	bool Mouse::loop() {
		// 初期化がされていなければ初期化
		if (init_flag) init();

		// カーソル座標取得
		cursor_buf = cursor;
		glfwGetCursorPos(Window::getGLFWHwnd(), &cursor.x, &cursor.y);
		cursor_move = cursor - cursor_buf;

		// click_a取得
		click_a_buf = click_a;
		click_a.l = (glfwGetMouseButton(Window::getGLFWHwnd(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
		click_a.r = (glfwGetMouseButton(Window::getGLFWHwnd(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);
		click_a.w = (glfwGetMouseButton(Window::getGLFWHwnd(), GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);

		// click_b取得
		click_b.l = ((click_a.l) && (!click_a_buf.l));
		click_b.r = ((click_a.r) && (!click_a_buf.r));
		click_b.w = ((click_a.w) && (!click_a_buf.w));
		if (click_b.l || click_b.r || click_b.w) drag_from = cursor;

		// ホイール回転量取得
		wheel = wheel_buf;
		wheel_buf = glm::dvec2(0.0, 0.0);

		return 0;
	}
	Mouse::CURSOR Mouse::cursor = glm::dvec2(0.0, 0.0);
	Mouse::CURSOR Mouse::cursor_buf = cursor;
	Mouse::CURSOR Mouse::cursor_move = glm::dvec2(0.0, 0.0);
	Mouse::CURSOR Mouse::drag_from = glm::dvec2(0.0, 0.0);
	Mouse::CLICK Mouse::click_a;
	Mouse::CLICK Mouse::click_a_buf;
	Mouse::CLICK Mouse::click_b;
	Mouse::WHEEL Mouse::wheel = glm::dvec2(0.0, 0.0);
	Mouse::WHEEL Mouse::wheel_buf = glm::dvec2(0.0, 0.0);
	bool Mouse::init_flag = 1;
}