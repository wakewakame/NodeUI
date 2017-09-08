/*

[GLManagementクラス]
	[マクロ]
		NUI_DEBUGが定義されていると、ウィンドウとは別にコンソールが表示される

	[関数]
		init()
			初期化関数
			ほかの関数を使用する前にこの関数を実行する

		loop()
			毎フレーム実行すべき関数

		exit()
			終了時に実行すべき関数

*/

#pragma once

//コンソール非表示化
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
		static bool init() {
			// GLFW初期化
			if (glfwInit() == GL_FALSE) return 1;

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL Version 4.xを指定
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // OpenGL Version x.5を指定
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true); // 古い機能を使えなくする			
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // コアプロファイル指定		
			glfwWindowHint(GLFW_SAMPLES, 4); // アンチエイリアスを有効化

			// ウィンドウ生成
			if (Window::createWindow()) return 1;

			// GLEW初期化
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK) return 1;
			
			// ウィンドウサイズ指定
			Window::setSize(Window::SIZE(640, 480));

			// 垂直同期のタイミングを待つ
			glfwSwapInterval(1);

			// デフォルトでブレンドモード有効化
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // アルファブレンド適用

			// デフォルトでアンチエイリアス適応
			glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // 点のアンチエイリアス精度最大化
			glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // 線のアンチエイリアス精度最大化
			glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST); // 面のアンチエイリアス精度最大化
			glEnable(GL_POINT_SMOOTH); // 点
			glEnable(GL_LINE_SMOOTH); // 線
			glEnable(GL_POLYGON_SMOOTH); // 面

			return 0;
		}
		static bool loop() {
			// ウィンドウが開いている間繰り返す
			if (glfwWindowShouldClose(Window::getGLFWHwnd()) != GL_FALSE) return 1;

			// nui内のloop関数をすべて実行
			if (Window::loop()) return 1;
			if (Mouse::loop()) return 1;

			return 0;
		}
		static void exit() {
			glfwTerminate();
		}
	};
}