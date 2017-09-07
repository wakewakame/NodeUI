#pragma once

//コンソール非表示化
#ifndef NUI_DEBUG
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#include "window.h"

namespace nui {
	class GLManagement {
	public:
		static bool init() {
			// GLFW初期化
			if (glfwInit() == GL_FALSE) return 1;

			// OpenGL Version 4.3を指定
			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

			// ウィンドウ生成
			Window::setGLFWHwnd(
				glfwCreateWindow(
					Window::getSize().x,
					Window::getSize().y,
					Window::getTitle().c_str(),
					NULL,
					NULL
				)
			);

			// ウィンドウが生成されていなければ終了
			if (Window::getGLFWHwnd() == NULL) return 1;

			// 生成したウィンドウをOpenGLの処理対象にする
			glfwMakeContextCurrent(Window::getGLFWHwnd());

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

			// イベントが発生するまで待機
			glfwPollEvents();

			return 0;
		}
		static void exit() {
			glfwTerminate();
		}
	};
}