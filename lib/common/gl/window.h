/*

[Windowクラス]
[定義]
using SIZE = glm::ivec2
using TITLE = std::string
using FPS = double
using SPEED = double
using RESIZE_FLAG = bool
using GLFW_HANDLE = GLFWwindow*
using CLOSE = std::function<void()>

[変数]
CLOSE close_event
ウィンドウクローズ時に処理される関数を代入するための型

[関数]
bool loop()
毎フレーム実行すべき関数
GLManagementクラスが実行するため、通常は呼び出さなくてよい
戻り値:成功:0,エラー:1

bool setSize(SIZE set_size)
ウィンドウサイズをset_sizeに変更する
引数1:ウィンドウサイズ
戻り値:成功:0,エラー:1

bool setPos(SIZE set_pos)
ウィンドウ位置をset_posに変更する
引数1:ウィンドウ座標
戻り値:成功:0,エラー:1

bool setTitle(TITLE set_title)
ウィンドウタイトルをset_titleに変更する
引数1:ウィンドウタイトルを
戻り値:成功:0,エラー:1

bool setStdFps(FPS set_std_fps)
getSpeed関数の計算基準となるフレームレートをset_std_fpsにする
デフォルトのフレームレートは60.0
尚、実際に描画されるフレームレートとの関係はない
引数1:フレームレートは
戻り値:成功:0,エラー:1

bool createWindow()
ウィンドウを生成する
GLManagementクラスが実行するため、通常は呼び出さなくてよい
戻り値:成功:0,エラー:1

SIZE getSize()
現在のウィンドウの大きさを取得する

TITLE getTitle()
現在のウィンドウタイトルを取得する

FPS getFps()
現在のフレームレートを取得する

FPS getStdFps()
現在のgetSpeed関数の計算基準となるフレームレートを取得する

SPEED getSpeed()
1フレームあたりのアニメーション速度を算出する関数
setStdFpsで指定されたフレームレートのときのアニメーション速度を1とし、
現在のフレームレートが小さくなるにつれ、アニメーション速度は大きくなる
現在のフレームレートが大きくなるにつれ、アニメーション速度は小さくなる
計算内容は setStdFpsで指定されたフレームレート / 現在のフレームレート
フレームレートによりアニメーション速度にムラが出るのを防ぐ

RESIZE_FLAG getResizeFlag()
ウィンドウサイズが更新された直後のフレームのみ1になる

GLFW_HANDLE getGLFWHwnd()
GLFWウィンドウハンドル取得

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
		static SIZE size; // ウィンドウサイズ
		static SIZE size_buf; // 1フレーム前のウィンドウサイズ
		static TITLE title; // ウィンドウタイトル
		static FPS fps; // 現在のフレームレート
		static FPS std_fps; // fps基準値 (アニメーション速度の調節用)
		static SPEED speed; // std_fps / fps (アニメーション速度の調節用)
		static RESIZE_FLAG resize_flag; // ウィンドウリサイズフラグ
		static GLFW_HANDLE gl_hwnd; // GLウィンドウハンドル
									// リサイズイベント処理用
		static void resize_func(GLFWwindow *window, int width, int heigh);
		// クローズイベント処理用
		static void close_func(GLFWwindow *window);
		// デフォルトクローズイベント処理
		static void default_close_event();

	public:
		static CLOSE close_event; // クローズイベント関数

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