#include "draw_base.h"

namespace nui {
		DrawBase::POINTS::POINTS() {
			dim = 0;
		}
		DrawBase::POINTS::POINTS(unsigned int set_num_points, unsigned int set_dim) {
			dim = set_dim;
			points = std::vector<VAR_TYPE>(set_dim * set_num_points, 0.0f);
		}

	bool DrawBase::createBuffers() {
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
	bool DrawBase::setArray(GLuint Location, POINTS &set_array) {
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
	bool DrawBase::init(unsigned int set_max_point) {
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

	void DrawBase::setColor(float r, float g, float b, float a) {
		default_color = glm::vec4(r, g, b, a);
	}

	bool DrawBase::addPoint(float set_x, float set_y) {
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

	void DrawBase::drawPoint(GLenum Type) {
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

	void DrawBase::clear() {
		// 画面の初期化
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		num_point = 0;
	}

	bool DrawBase::render() {
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

	void DrawBase::exit() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &cbo);

		nui::GLManagement::exit();
	}
	GLuint DrawBase::vao = GL_FALSE;
	GLuint DrawBase::vbo = GL_FALSE;
	GLuint DrawBase::cbo = GL_FALSE;
	DrawBase::POINTS DrawBase::vertex;
	DrawBase::POINTS DrawBase::color;
	glm::vec4 DrawBase::default_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	unsigned int DrawBase::max_point;
	unsigned int DrawBase::num_point = 0;
}