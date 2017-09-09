/*

[Mouseクラス]
	[定義]
		using CURSOR = glm::dvec2
		struct CLICK {
			bool l; // 左クリック
			bool r; // 右クリック
			bool w; // ホイールクリック
			CLICK() {
				l = 0;
				r = 0;
				w = 0;
			}
		}
		using WHEEL = glm::dvec2

	[関数]
		static bool loop()
			毎フレーム実行すべき関数
			GLManagementクラスが実行するため、通常は呼び出さなくてよい。
			戻り値:成功:0,エラー:1

		static inline CURSOR getCursor()
			現在のマウスカーソルの座標を取得
			戻り値:現在のマウスカーソルの座標

		static inline CURSOR getCursorMove()
			1つ前のフレームからのマウスカーソルの移動量を取得
			戻り値:1つ前のフレームからのマウスカーソルの移動量

		static inline CURSOR getDragFrom()
			左、右、ホイールのいずれかがクリックされた瞬間のカーソル座標を取得(ドラッグ用)
			戻り値:左、右、ホイールのいずれかがクリックされた瞬間のカーソル座標

		static inline CLICK getClickA()
			押されている間ずっと1のクリック情報を取得
			戻り値:押されている間ずっと1のクリック情報

		static inline CLICK getClickB()
			押されたフレームのみ1のクリック情報を取得
			戻り値:押されたフレームのみ1のクリック情報

		static inline WHEEL getWheel()
			1フレーム間に発生したホイール回転量を取得
			戻り値:1フレーム間に発生したホイール回転量を取得

*/

#pragma once

namespace nui {
	class Mouse {
	public:
		using CURSOR = glm::dvec2; // カーソル座標
		struct CLICK {
			bool l; // 左クリック
			bool r; // 右クリック
			bool w; // ホイールクリック
			CLICK() {
				l = 0;
				r = 0;
				w = 0;
			}
		};
		using WHEEL = glm::dvec2; // ホイール回転量

	private:
		static CURSOR cursor; // 現在のマウスカーソル座標
		static CURSOR cursor_buf; // 1つ前のcursorの状態
		static CURSOR cursor_move; // 1フレーム間のカーソルの移動量
		static CURSOR drag_from; // 左、右、ホイールのいずれかがクリックされた瞬間のカーソル座標(ドラッグ用)
		static CLICK click_a; // 押されている間ずっと1のクリック情報
		static CLICK click_a_buf; // 1つ前のclick_aの状態
		static CLICK click_b; // 押されたフレームのみ1のクリック情報
		static WHEEL wheel; // 1フレーム間に発生したホイール回転量
		static WHEEL wheel_buf; // 1フレーム間に発生したホイール回転量を蓄える為の変数
		static bool init_flag; // 初期化がされていなければ1
		// ホイールイベント処理用
		static void wheel_func(GLFWwindow *window, double x, double y) {
			wheel_buf.x += x;
			wheel_buf.y += y;
		}
		// 初期化関数
		static void init() {
			glfwSetScrollCallback(Window::getGLFWHwnd(), wheel_func);
		}

	public:
		static bool loop() {
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
		static inline CURSOR getCursor() {return cursor;}
		static inline CURSOR getCursorMove() {return cursor_move;}
		static inline CURSOR getDragFrom() { return drag_from; }
		static inline CLICK getClickA() {return click_a;}
		static inline CLICK getClickB() {return click_b;}
		static inline WHEEL getWheel() {return wheel;}
	};
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