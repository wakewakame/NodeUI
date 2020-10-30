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
#include "../math/math.h"

namespace nui {
	class Draw : public DrawBase {
	private:
		static bool fill;
		static float width;

	public:
		static void setFill(bool set_fill);
		static void setWidth(float set_width);
		static void line(float start_x, float start_y, float end_x, float end_y);
		static void box(float left, float top, float right, float bottom);
		static void circle(float set_x, float set_y, float size, float div = 24);
	};
}