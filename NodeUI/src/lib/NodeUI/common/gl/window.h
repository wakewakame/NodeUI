/*

[Windowクラス]
	[定義]
		using SIZE = glm::ivec2;
		using TITLE = std::string;
		using FPS = double;
		using SPEED = double;
		using RESIZE_FLAG = bool;
		using GLFW_HANDLE = GLFWwindow*;
		using CLOSE = std::function<void()>;

	[変数]
		CLOSE close_event;
			ウィンドウクローズ時に処理される関数を代入するための型

	[関数]
		static bool loop()
			毎フレーム実行すべき関数
			GLManagementクラスが実行するため、通常は呼び出さなくてよい。

		static bool setSize(SIZE set_size)
			ウィンドウサイズをset_sizeに変更する

		static bool setTitle(TITLE set_title)
			ウィンドウタイトルをset_titleに変更する

		static bool setStdFps(FPS set_std_fps)
			getSpeed関数の計算基準となるフレームレートをset_std_fpsにする
			デフォルトのフレームレートは60.0
			尚、実際に描画されるフレームレートとの関係はない

		static bool createWindow(GLFW_HANDLE set_gl_hwnd)
			ウィンドウを生成する
			GLManagementクラスが実行するため、通常は呼び出さなくてよい。

		static SIZE getSize()
			現在のウィンドウの大きさを取得する

		static TITLE getTitle()
			現在のウィンドウタイトルを取得する

		static FPS getFps()
			現在のフレームレートを取得する

		static FPS getStdFps()
			現在のgetSpeed関数の計算基準となるフレームレートを取得する

		static SPEED getSpeed()
			1フレームあたりのアニメーション速度を算出する関数
			setStdFpsで指定されたフレームレートのときのアニメーション速度を1とし、
			現在のフレームレートが小さくなるにつれ、アニメーション速度は大きくなる
			現在のフレームレートが大きくなるにつれ、アニメーション速度は小さくなる
			計算内容は setStdFpsで指定されたフレームレート / 現在のフレームレート
			フレームレートによりアニメーション速度にムラが出るのを防ぐ

		static RESIZE_FLAG getResizeFlag()
			ウィンドウサイズが更新された直後のフレームのみ1になる

		static GLFW_HANDLE getGLFWHwnd()
			GLFWウィンドウハンドル取得

*/

#pragma once

#include "common.h"

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
		static SIZE size; // ウィンドウサイズ
		static SIZE size_buf; // 1フレーム前のウィンドウサイズ
		static TITLE title; // ウィンドウタイトル
		static FPS fps; // 現在のフレームレート
		static FPS std_fps; // fps基準値 (アニメーション速度の調節用)
		static SPEED speed; // std_fps / fps (アニメーション速度の調節用)
		static RESIZE_FLAG resize_flag; // ウィンドウリサイズフラグ
		static GLFW_HANDLE gl_hwnd; // GLウィンドウハンドル
		// リサイズイベント処理用
		static void resize_func(GLFWwindow *window, int width, int heigh) {
			setSize(glm::ivec2(width, heigh));
		}
		// クローズイベント処理用
		static void close_func(GLFWwindow *window) {
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
		static bool createWindow() {
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
		static inline SIZE getSize() {return size;}
		static inline TITLE getTitle() {return title;}
		static inline FPS getFps() {return fps;}
		static inline FPS getStdFps() {return std_fps;}
		static inline SPEED getSpeed() {return speed;}
		static inline RESIZE_FLAG getResizeFlag() {return resize_flag;}
		static inline GLFW_HANDLE getGLFWHwnd() {return gl_hwnd;}
	};
	Window::SIZE Window::size = Window::SIZE(640, 480);
	Window::SIZE Window::size_buf = size;
	Window::TITLE Window::title = "";
	Window::FPS Window::fps = 0.0;
	Window::FPS Window::std_fps = 60.0;
	Window::SPEED Window::speed = 1.0;
	Window::RESIZE_FLAG Window::resize_flag = 0;
	Window::GLFW_HANDLE Window::gl_hwnd = nullptr;
	Window::CLOSE Window::close_event = Window::default_close_event;
}