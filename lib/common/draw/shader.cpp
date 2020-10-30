#include "shader.h"

namespace nui {
	bool Shader::init() {
		version_code_string =
			"#version " +
			std::to_string(GLManagement::getVersion().major) +
			std::to_string(GLManagement::getVersion().minor) +
			std::to_string(0) +
			" core\n";
		normal_vs =
			version_code_string +
			R"(
in vec2 pos;
in vec4 col;
out vec4 fragmentColor;
uniform vec2 reso;
vec2 position;

void main(){
position = pos;
position.x /= reso.x;
position.y /= reso.y;
position.y = 1.0 - position.y;
position *= 2.0;
position -= vec2(1.0, 1.0);
gl_Position.xyz = vec3(position, 0.0);
gl_Position.w = 1.0;
fragmentColor = col;
}
			)";
		normal_fs =
			version_code_string +
			R"(
in vec4 fragmentColor;
out vec4 color;
void main(){
color = fragmentColor;
}
			)";
		normal = createProgram(normal_vs, normal_fs);
		if (normal == GL_FALSE) return 1;
		return 0;
	}
	bool Shader::loop() {
		// �����v���O�������w�肳��Ă��Ȃ���Ώ����I��
		if (now == GL_FALSE) return 0;
		// �V�F�[�_�ɉ𑜓x�𑗐M
		if (Window::getResizeFlag()) {
			glUniform2f(reso_s, (float)Window::getSize().x, (float)Window::getSize().y);
		}
		return 0;
	}
	// �o�[�e�b�N�X�V�F�[�_�̂ݐ���
	Shader::PROGRAM Shader::createVSProgram(SHADER_CODE vs) {
		return createProgram(vs, normal_fs);
	}
	// �t���O�����g�V�F�[�_�̂ݎw��
	Shader::PROGRAM Shader::createFSProgram(SHADER_CODE fs) {
		return createProgram(normal_vs, fs);
	}
	bool Shader::setProgram(PROGRAM p) {
		if (ShaderBase::setProgram(p)) return 1;
		pos_s = glGetAttribLocation(now, "pos");
		col_s = glGetAttribLocation(now, "col");
		reso_s = glGetUniformLocation(now, "reso");
		glUniform2f(reso_s, (float)Window::getSize().x, (float)Window::getSize().y);
		return 0;
	}
	Shader::SHADER_CODE Shader::version_code_string;
	Shader::SHADER_CODE Shader::normal_vs;
	Shader::SHADER_CODE Shader::normal_fs;
	GLuint Shader::pos_s;
	GLuint Shader::col_s;
	GLuint Shader::reso_s;
	Shader::PROGRAM Shader::normal;
}