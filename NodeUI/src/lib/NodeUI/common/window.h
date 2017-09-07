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
		static SIZE size; // ウィンドウサイズ
		static SIZE size_buf; // 1フレーム前のウィンドウサイズ
		static TITLE title; // ウィンドウタイトル
		static FPS fps; // 現在のフレームレート
		static FPS std_fps; // fps基準値 (アニメーション速度の調節用)
		static SPEED speed; // std_fps / fps (アニメーション速度の調節用)
		static RESIZE_FLAG resize_flag; // ウィンドウリサイズフラグ
		static WINDOW_HANDLE hwnd; // ウィンドウハンドル
		static GLFW_HANDLE gl_hwnd; // GLウィンドウハンドル
		// リサイズイベント処理用
		static void resize(GLFWwindow *window, int width, int heigh) {
			setSize(glm::ivec2(width, heigh));
		}
		// クローズイベント処理用
		static void close(GLFWwindow *window) {
			close_event();
		}
		// デフォルトクローズイベント処理
		static void default_close_event() {}

	public:
		static CLOSE close_event; // クローズイベント関数

		static bool loop() {
			// ウィンドウリサイズフラグ確認
			resize_flag = (size != size_buf);
			size_buf = size;

			// FPS測定
			fps = 1.0 / glfwGetTime();
			speed = std_fps / fps;
			glfwSetTime(0.0);

			return 0;
		}
		static bool setSize(SIZE set_size) {
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

			// ウィンドウハンドル取得
			HDC glDc = wglGetCurrentDC();
			hwnd = WindowFromDC(glDc);

			// ウィンドウリサイズイベント処理関数登録
			glfwSetWindowSizeCallback(gl_hwnd, resize);
			// ウィンドウクローズイベント処理関数登録
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