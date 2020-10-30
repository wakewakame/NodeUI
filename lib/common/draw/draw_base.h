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

#pragma once

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
			POINTS();
			POINTS(unsigned int set_num_points, unsigned int set_dim);
			inline unsigned int DrawBase::POINTS::size() {
				return sizeof(VAR_TYPE)*points.size();
			}
			inline void DrawBase::POINTS::set(unsigned int set_index, unsigned int set_dim, VAR_TYPE val) {
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
		static bool createBuffers();
		static bool setArray(GLuint Location, POINTS &set_array);

	public:
		static bool init(unsigned int set_max_point = 512);

		static void setColor(float r, float g, float b, float a = 1.0f);

		static bool addPoint(float set_x, float set_y);

		static void drawPoint(GLenum Type);

		static void clear();

		static bool render();

		static void exit();
	};
}