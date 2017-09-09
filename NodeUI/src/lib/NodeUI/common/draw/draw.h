#pragma once

#include "draw_base.h"

namespace nui {
	class Draw : public DrawBase {
	public:
		static void line(float left, float top, float right, float bottom) {
			nui::Draw::addPoint(left, top);
			nui::Draw::addPoint(right, bottom);
			nui::Draw::drawPoint(GL_LINES);
		}
		static void box(float left, float top, float right, float bottom) {
			nui::Draw::addPoint(left, top);
			nui::Draw::addPoint(right, top);
			nui::Draw::addPoint(right, bottom);
			nui::Draw::addPoint(left, bottom);
			nui::Draw::drawPoint(GL_TRIANGLE_FAN);
		}
	};
}