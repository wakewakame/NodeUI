/*

[GLManagementクラス]
	[マクロ]
		NUI_DEBUGが定義されていると、ウィンドウとは別にコンソールが表示される

	[定義]
		struct VERSION{
			char major; // OpenGLのmajorバージョン
			char minor; // OpenGLのminorバージョン
		}

	[関数]
		bool init(VERSION set_gl_version)
			初期化関数
			DrawBaseクラスが実行するため、通常は呼び出さなくてよい
			ほかの関数を使用する前にこの関数を実行する
			戻り値:成功:0,エラー:1

		bool loop()
			毎フレーム実行すべき関数
			DrawBaseクラスが実行するため、通常は呼び出さなくてよい
			戻り値:成功:0,エラー:1

		void exit()
			終了時に実行すべき関数
			DrawBaseクラスが実行するため、通常は呼び出さなくてよい

		VERSION getVersion()
			現在指定されているOpenGLのバージョンを取得する
			戻り値:現在指定されているOpenGLのバージョン

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
		struct VERSION{
			char major;
			char minor;
			VERSION() {
				major = 4;
				minor = 5;
			}
			VERSION(char set_major, char set_minor) {
				major = set_major;
				minor = set_minor;
			}
		};
	private:
		static VERSION gl_version;
	public:
		static bool init(VERSION set_gl_version = VERSION()) {
			// GLFW初期化
			if (glfwInit() == GL_FALSE) return 1;

			gl_version = set_gl_version;

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version.major); // OpenGL Version 4.xを指定
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version.minor); // OpenGL Version x.5を指定
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Mac用
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 古い機能を使えなくする		
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
		static inline VERSION getVersion() { return gl_version; }
	};
	GLManagement::VERSION GLManagement::gl_version;
}