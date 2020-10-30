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

#include "../gl/gl.h"
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
			ERROR_MESSAGE();
		};
	protected:
		static PROGRAM now; // 現在指定されているプログラムのID
		static ERROR_MESSAGE error; // エラー代入用
		static SHADER createShader(SHADER_CODE code, GLenum Type);
		static void deleteShader(SHADER s);
	public:
		static PROGRAM createProgram(SHADER_CODE vs, SHADER_CODE fs);
		static bool setProgram(PROGRAM p);
		static inline PROGRAM getNowProgram();
		static inline ERROR_MESSAGE getError();
	};
}