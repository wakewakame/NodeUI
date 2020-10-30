#include "draw.h"

namespace nui {
	void Draw::setFill(bool set_fill) {
		fill = set_fill;
	}
	void Draw::setWidth(float set_width) {
		width = set_width;
	}
	void Draw::line(float start_x, float start_y, float end_x, float end_y) {
		nui::Draw::addPoint(start_x, start_y);
		nui::Draw::addPoint(end_x, end_y);
		nui::Draw::drawPoint(GL_LINES);
	}
	void Draw::box(float left, float top, float right, float bottom) {
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
	void Draw::circle(float set_x, float set_y, float size, float div) {
		for (int i = 0; i < div; i++) {
			nui::Draw::addPoint(
				set_x + size * std::cos((2.0*M_PI) * (((float)i) / ((float)div))),
				set_y + size * std::sin((2.0*M_PI) * (((float)i) / ((float)div)))
			);
		}
		if (fill) {
			nui::Draw::drawPoint(GL_TRIANGLE_FAN);
		}
		else {
			nui::Draw::drawPoint(GL_LINE_LOOP);
		}
	}
	bool Draw::fill = 1;
	float Draw::width = 1.0f;
}