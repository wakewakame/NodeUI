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
		struct VERSION {
			char major;
			char minor;
			VERSION();
			VERSION(char set_major, char set_minor);
		};
	private:
		static VERSION gl_version;
	public:
		static bool init(VERSION set_gl_version = VERSION());
		static bool loop();
		static void exit();
		static inline GLManagement::VERSION GLManagement::getVersion() { return gl_version; }
	};
}