#pragma once

/*

[DrawBaseクラス]
	[定義]
		using VAR_TYPE = float
		struct POINTS {
			std::vector<VAR_TYPE> points; // 頂点配列
			unsigned int dim; // 頂点の次元数
		}

	[関数]
		bool init(unsigned int set_max_point = 512)
			初期化関数
			Drawクラスが実行するため、通常は呼び出さなくてよい
			ほかの関数を使用する前にこの関数を実行する
			引数1:1度に追加できる頂点の最大数(デフォルトは512個)
			戻り値:成功:0,エラー:1

		void setColor(float r, float g, float b, float a = 1.0f)
			色指定関数
			引数1:R値
			引数2:G値
			引数3:B値
			引数4:A値

		bool addPoint(float set_x, float set_y)
			頂点追加関数
			座標単位はpx
			ウィンドウ左上を原点とし、右下が正の方向
			引数1:x座標
			引数2:y座標
			戻り値:成功:0,エラー:1

		void drawPoint(GLenum Type)
			頂点描画関数
			追加された頂点をTypeモードでバッファに描画する
			バッファをウィンドウに反映するにはrender関数を使用する
			引数1:描画モード(以下のいずれか)
				GL_POINTS
				GL_LINE_STRIP
				GL_LINE_LOOP
				GL_LINES
				GL_LINE_STRIP_ADJACENCY
				GL_LINES_ADJACENCY
				GL_TRIANGLE_STRIP
				GL_TRIANGLE_FAN
				GL_TRIANGLES
				GL_TRIANGLE_STRIP_ADJACENCY
				GL_TRIANGLES_ADJACENCY
				GL_PATCHES

		void clear()
			バッファクリア関数
			バッファを白に塗りつぶす

		bool render()
			バッファをウィンドウに反映する関数

		void exit()
			終了時に実行すべき関数
			Drawクラスが実行するため、通常は呼び出さなくてよい

*/

#include <vector>

#include "../gl/gl.h"
#include "shader.h"

namespace nui {
	class DrawBase {
	public:
		using VAR_TYPE = float;
		struct POINTS {
			std::vector<VAR_TYPE> points;
			unsigned int dim;
			POINTS() {
				dim = 0;
			}
			POINTS(unsigned int set_num_points, unsigned int set_dim) {
				dim = set_dim;
				points = std::vector<VAR_TYPE>(set_dim * set_num_points, 0.0f);
			}
			inline unsigned int size() {
				return sizeof(VAR_TYPE)*points.size();
			}
			inline void set(unsigned int set_index, unsigned int set_dim, VAR_TYPE val) {
				points[set_index*dim + set_dim] = val;
			}
		};

	private:
		static GLuint vao; // Vertex Array Object
		static GLuint vbo; // Vertex Buffer Object
		static GLuint cbo; // Color Array Object
		static POINTS vertex;
		static POINTS color;
		static unsigned int num_point;
		static glm::vec4 default_color;
		static unsigned int max_point;
		static bool createBuffers() {
			// 配列の初期化
			vertex = POINTS(max_point, 2);
			color = POINTS(max_point, 4);
			// VAOの生成
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			// VBOの生成
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertex.size(), NULL, GL_DYNAMIC_DRAW);
			// CBOの生成
			glGenBuffers(1, &cbo);
			glBindBuffer(GL_ARRAY_BUFFER, cbo);
			glBufferData(GL_ARRAY_BUFFER, color.size(), NULL, GL_DYNAMIC_DRAW);
			return 0;
		}
		static bool setArray(GLuint Location, POINTS &set_array) {
			VAR_TYPE *p = (VAR_TYPE*)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(VAR_TYPE)*set_array.dim*num_point, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
			std::memcpy(p, set_array.points.data(), sizeof(VAR_TYPE)*set_array.dim*num_point);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glVertexAttribPointer(
				Location,
				set_array.dim,  // 次元数
				GL_FLOAT, // 座標精度
				GL_FALSE, // 正規化
				0, // ストライド
				(void*)0 // 配列バッファオフセット
			);
			return 0;
		}

	public:
		static bool init(unsigned int set_max_point = 512) {
			// 頂点数の最大値
			max_point = set_max_point;

			// GLManagementクラスの初期化
			if (GLManagement::init()) return 1;

			// Shaderクラスの初期化
			if (Shader::init()) return 1;

			// NormarShader指定
			Shader::setProgram(Shader::getNormalProgram());

			// 前のものよりもカメラに近ければ、フラグメントを受け入れる
			glDepthFunc(GL_LESS);

			// 必要なバッファオブジェクトをすべて生成
			if (createBuffers()) return 1;

			return 0;
		}

		static void setColor(float r, float g, float b, float a = 1.0f) {
			default_color = glm::vec4(r, g, b, a);
		}

		static bool addPoint(float set_x, float set_y) {
			if (num_point >= max_point) return 1;
			vertex.set(num_point, 0, set_x);
			vertex.set(num_point, 1, set_y);
			color.set(num_point, 0, default_color.r);
			color.set(num_point, 1, default_color.g);
			color.set(num_point, 2, default_color.b);
			color.set(num_point, 3, default_color.a);
			num_point += 1;
			return 0;
		}

		static void drawPoint(GLenum Type) {
			glBindVertexArray(vao);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glEnableVertexAttribArray(Shader::getVertexLocation());
			setArray(Shader::getVertexLocation(), vertex);

			glBindBuffer(GL_ARRAY_BUFFER, cbo);
			glEnableVertexAttribArray(Shader::getColorLocation());
			setArray(Shader::getColorLocation(), color);

			glDrawArrays(Type, 0, num_point);
			glDisableVertexAttribArray(Shader::getColorLocation());
			glDisableVertexAttribArray(Shader::getVertexLocation());

			num_point = 0;
		}

		static void clear() {
			// 画面の初期化
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			num_point = 0;
		}

		static bool render() {
			// カラーバッファを入れ替える
			glfwSwapBuffers(nui::Window::getGLFWHwnd());
			// イベントが発生するまで待機
			glfwPollEvents();
			// GLManagementのloop関数実行
			if (GLManagement::loop()) return 1;
			// Shaderのloop関数実行
			if (Shader::loop()) return 1;
			return 0;
		}

		static void exit() {
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &cbo);

			nui::GLManagement::exit();
		}
	};
	GLuint DrawBase::vao = GL_FALSE;
	GLuint DrawBase::vbo = GL_FALSE;
	GLuint DrawBase::cbo = GL_FALSE;
	DrawBase::POINTS DrawBase::vertex;
	DrawBase::POINTS DrawBase::color;
	glm::vec4 DrawBase::default_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	unsigned int DrawBase::max_point;
	unsigned int DrawBase::num_point = 0;
}