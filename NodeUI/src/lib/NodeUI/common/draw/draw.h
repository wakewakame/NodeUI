/*

[Drawクラス] 継承元:DrawBase
	[関数]
		void setFill(bool set_fill)
			塗りつぶし指定
			引数1:塗りつぶさない:0,塗りつぶす:1

		void setWidth(float set_width)
			線の太さ指定
			引数1:線の太さ(px単位)

		void line(float start_x, float start_y, float end_x, float end_y)
			線描画関数
			引数1,2:線の末端座標1
			引数3,4:線の末端座標2

		void box(float left, float top, float right, float bottom)
			四角形描画関数
			引数1,2:四角形の左上座標
			引数3,4:四角形の右下座標

		void circle(float set_x, float set_y, float size, float div = 24)
			円描画関数
			引数1,2:円の中心座標
			引数3:円の半径
			引数4:円の分割数(デフォルトは24)

*/

#pragma once

#include "draw_base.h"
#include "../math.h"

namespace nui {
	class Draw : public DrawBase {
	private:
		static bool fill;
		static float width;

	public:
		static void setFill(bool set_fill) {
			fill = set_fill;
		}
		static void setWidth(float set_width) {
			width = set_width;
		}
		static void line(float start_x, float start_y, float end_x, float end_y) {
			nui::Draw::addPoint(start_x, start_y);
			nui::Draw::addPoint(end_x, end_y);
			nui::Draw::drawPoint(GL_LINES);
		}
		static void box(float left, float top, float right, float bottom) {
			nui::Draw::addPoint(left, top);
			nui::Draw::addPoint(right, top);
			nui::Draw::addPoint(right, bottom);
			nui::Draw::addPoint(left, bottom);
			if (fill) {
				nui::Draw::drawPoint(GL_TRIANGLE_FAN);
			}
			else {
				nui::Draw::drawPoint(GL_LINE_LOOP);
			}
		}
		static void circle(float set_x, float set_y, float size, float div = 24) {
			for (int i = 0; i < div; i++) {
				nui::Draw::addPoint(
					set_x + size * std::cos( (2.0*M_PI) * ( ((float)i) / ((float)div) )),
					set_y + size * std::sin( (2.0*M_PI) * ( ((float)i) / ((float)div) ))
				);
			}
			if (fill) {
				nui::Draw::drawPoint(GL_TRIANGLE_FAN);
			}
			else {
				nui::Draw::drawPoint(GL_LINE_LOOP);
			}
		}
	};
	bool Draw::fill = 1;
}