#pragma once

#include "../gl/gl.h"

namespace nui {
	class Draw {
	private:
		static GLuint VertexArrayID; // VAO
		static GLuint vertexbuffer; // VBO

	public:
		static bool init() {
			// GLManagementクラスの初期化
			if (nui::GLManagement::init()) return 1;

			// VAOの生成
			static const GLfloat g_vertex_buffer_data[] = {
				-1.0f, -1.0f, 0.0f,
				1.0f, -1.0f, 0.0f,
				0.0f,  1.0f, 0.0f,
			};
			glGenVertexArrays(1, &VertexArrayID);
			glGenBuffers(1, &vertexbuffer);
			glBindVertexArray(VertexArrayID);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

			return 0;
		}

		static bool draw() {
			if (nui::GLManagement::loop()) return 1;
			//イベントが発生するまで待機
			glfwPollEvents();

			//画面初期化
			glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(
				0,                  // 属性0：0に特に理由はありません。しかし、シェーダ内のlayoutとあわせないといけません。
				3,                  // サイズ
				GL_FLOAT,           // タイプ
				GL_FALSE,           // 正規化？
				0,                  // ストライド
				(void*)0            // 配列バッファオフセット
			);

			// 三角形を描きます！
			glDrawArrays(GL_TRIANGLES, 0, 3); // 頂点0から始まります。合計3つの頂点です。&rarr;1つの三角形です。

			glDisableVertexAttribArray(0);

			//バッファに描画
			glFlush();
			//カラーバッファを入れ替える
			glfwSwapBuffers(nui::Window::getGLFWHwnd());

			return 0;
		}

		static void exit() {
			glDeleteVertexArrays(1, &VertexArrayID);

			nui::GLManagement::exit();
		}
	};
	GLuint Draw::VertexArrayID = GL_FALSE;
	GLuint Draw::vertexbuffer = GL_FALSE;
}