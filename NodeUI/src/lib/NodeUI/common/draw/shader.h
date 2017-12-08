/*

[Shaderクラス] 継承元:ShaderBase
	[定義]
		[default vertex shader]
			#version xxx core // OpenGLのバージョン指定(デフォルトは450)
			in vec2 pos; // 入力頂点配列
			in vec4 col; // 入力色配列
			out vec4 fragmentColor; // 出力色配列
			uniform vec2 reso; // 解像度
			vec2 position; // 頂点座標一時代入用

			void main(){
				position = pos; // 一時代入
				// Window座標 -> OpenGL座標 に変換
				position.x /= reso.x;
				position.y /= reso.y;
				position.y = 1.0 - position.y;
				position *= 2.0;
				position -= vec2(1.0, 1.0);
				// 頂点配列出力
				gl_Position.xyz = vec3(position, 0.0);
				gl_Position.w = 1.0;
				// 色配列出力
				fragmentColor = col;
			}

		[default fragment shader]
			#version xxx core // OpenGLのバージョン指定(デフォルトは450)
			in vec4 fragmentColor; // 入力色配列
			out vec4 color; // 出力色配列
			void main(){
				color = fragmentColor;
			}

	[関数]
		static bool init()
			初期化関数
			DrawBaseクラスが実行するため、通常は呼び出さなくてよい
			ほかの関数を使用する前にこの関数を実行する
			戻り値:成功:0,エラー:1

		static bool loop()
			毎フレーム実行すべき関数
			DrawBaseクラスが実行するため、通常は呼び出さなくてよい
			戻り値:成功:0,エラー:1

		static PROGRAM createVSProgram(SHADER_CODE vs)
			バーテックスシェーダのコンパイル関数
			フラグメントシェーダはデフォルトのものを使う
			引数1:バーテックスシェーダのソースコード
			戻り値:プログラムID
			コンパイルに失敗した場合は0が返る

		static PROGRAM createFSProgram(SHADER_CODE fs)
			フラグメントシェーダコンパイル関数
			バーテックスシェーダはデフォルトのものを使う
			引数1:フラグメントシェーダのソースコード
			戻り値:プログラムID
			コンパイルに失敗した場合は0が返る

		static inline PROGRAM getNormalProgram()
			デフォルトのシェーダのプログラムIDを取得する
			戻り値:プログラムID

		static inline GLuint getVertexLocation()
			現在のシェーダの頂点配列が格納される変数のロケーションID取得
			戻り値:現在のシェーダの頂点配列が格納される変数のロケーションID

		static inline GLuint getColorLocation()
			現在のシェーダの色配列が格納される変数のロケーションID取得
			戻り値:現在のシェーダの色配列が格納される変数のロケーションID

		static bool setProgram(PROGRAM p)
			シェーダを指定する
			引数1:プログラムID
			戻り値:成功:0,エラー:1

*/

#pragma once

#include "shader_base.h"

namespace nui{
	class Shader : public ShaderBase {
	private:
		static SHADER_CODE version_code_string; // シェーダの先頭につけるバージョン指定コード
		static SHADER_CODE normal_vs; // ノーマルバーテックスシェーダのコード
		static SHADER_CODE normal_fs; // ノーマルフラグメントシェーダのコード
		static GLuint pos_s; // shaderのpos変数のID
		static GLuint col_s; // shaderのcol変数のID
		static GLuint reso_s; // shaderのreso変数のID
		static PROGRAM normal; // ノーマルプログラムのプログラムID
	public:
		static bool init();
		static bool loop();
		// バーテックスシェーダのみ生成
		static PROGRAM createVSProgram(SHADER_CODE vs);
		// フラグメントシェーダのみ指定
		static PROGRAM createFSProgram(SHADER_CODE fs);
		static inline Shader::PROGRAM Shader::getNormalProgram() { return normal; }
		static inline GLuint Shader::getVertexLocation() { return pos_s; }
		static inline GLuint Shader::getColorLocation() { return col_s; }
		static bool setProgram(PROGRAM p);
	};
}