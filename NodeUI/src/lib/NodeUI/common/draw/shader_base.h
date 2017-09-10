/*

[ShaderBaseクラス]
[定義]
using PROGRAM = GLuint
using SHADER = GLuint
using SHADER_CODE = std::string
struct ERROR {
std::string vertex; // バーテックスシェーダエラー内容
std::string fragment; // フラグメントシェーダエラー内容
std::string link; // リンクエラー内容
}

[関数]
PROGRAM createProgram(SHADER_CODE vs, SHADER_CODE fs)
シェーダコンパイル関数
引数1:バーテックスシェーダのソースコード
引数2:フラグメントシェーダのソースコード
戻り値:プログラムID
コンパイルに失敗した場合は0が返る

bool setProgram(PROGRAM p)
シェーダを指定する
引数1:プログラムID
戻り値:成功:0,エラー:1

PROGRAM getNowProgram()
現在指定されているシェーダを取得する
戻り値:現在指定されているプログラムID

ERROR getError()
エラー内容を取得する

*/

#pragma once

#include <string>
#include <vector>

namespace nui {
	class ShaderBase {
	public:
		using PROGRAM = GLuint;
		using SHADER = GLuint;
		using SHADER_CODE = std::string;
		struct ERROR_MESSAGE {
			std::string vertex;
			std::string fragment;
			std::string link;
			ERROR_MESSAGE() {
				vertex = "";
				fragment = "";
				link = "";
			}
		};
	protected:
		static PROGRAM now; // 現在指定されているプログラムのID
		static ERROR_MESSAGE error; // エラー代入用
		static SHADER createShader(SHADER_CODE code, GLenum Type) {
			// シェーダの生成
			GLuint ShaderID = glCreateShader(Type);
			// シェーダのコンパイル
			char const *SourcePointer = code.c_str();
			glShaderSource(ShaderID, 1, &SourcePointer, NULL);
			glCompileShader(ShaderID);
			// エラーチェック
			GLint Result = GL_FALSE;
			glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
			if (Result == GL_FALSE) {
				int InfoLogLength;
				glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
				std::vector<char> ErrorMessage(InfoLogLength + 1);
				glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &ErrorMessage[0]);
				switch (Type) {
				case GL_VERTEX_SHADER:
					error.vertex = std::string(ErrorMessage.data());
					break;
				case GL_FRAGMENT_SHADER:
					error.fragment = std::string(ErrorMessage.data());
					break;
				}
				return GL_FALSE;
			}
			// シェーダID出力
			return ShaderID;
		}
		static void deleteShader(SHADER s) {
			glDeleteShader(s);
		}
	public:
		static PROGRAM createProgram(SHADER_CODE vs, SHADER_CODE fs) {
			// シェーダのコンパイル
			SHADER vs_id = createShader(vs, GL_VERTEX_SHADER);
			SHADER fs_id = createShader(fs, GL_FRAGMENT_SHADER);
			if (vs_id == GL_FALSE || fs_id == GL_FALSE) return GL_FALSE;
			// プログラムの生成
			PROGRAM ProgramID = glCreateProgram();
			glAttachShader(ProgramID, vs_id);
			glAttachShader(ProgramID, fs_id);
			glLinkProgram(ProgramID);
			// シェーダ破棄
			deleteShader(vs_id);
			deleteShader(fs_id);
			// エラーチェック
			GLint Result = GL_FALSE;
			glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
			if (Result == GL_FALSE) {
				int InfoLogLength;
				glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
				std::vector<char> ErrorMessage(InfoLogLength + 1);
				glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ErrorMessage[0]);
				error.link = std::string(ErrorMessage.data());
				return GL_FALSE;
			}
			// プログラムID出力
			return ProgramID;
		}
		static bool setProgram(PROGRAM p) {
			glUseProgram(p);
			now = p;
			return 0;
		}
		static inline PROGRAM getNowProgram() { return now; }
		static inline ERROR_MESSAGE getError() { return error; }
	};
	ShaderBase::PROGRAM ShaderBase::now;
	ShaderBase::ERROR_MESSAGE ShaderBase::error;
}