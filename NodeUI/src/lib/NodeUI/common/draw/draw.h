/*

[Draw�N���X] �p����:DrawBase
	[�֐�]
		void setFill(bool set_fill)
			�h��Ԃ��w��
			����1:�h��Ԃ��Ȃ�:0,�h��Ԃ�:1

		void setWidth(float set_width)
			���̑����w��
			����1:���̑���(px�P��)

		void line(float start_x, float start_y, float end_x, float end_y)
			���`��֐�
			����1,2:���̖��[���W1
			����3,4:���̖��[���W2

		void box(float left, float top, float right, float bottom)
			�l�p�`�`��֐�
			����1,2:�l�p�`�̍�����W
			����3,4:�l�p�`�̉E�����W

		void circle(float set_x, float set_y, float size, float div = 24)
			�~�`��֐�
			����1,2:�~�̒��S���W
			����3:�~�̔��a
			����4:�~�̕�����(�f�t�H���g��24)

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