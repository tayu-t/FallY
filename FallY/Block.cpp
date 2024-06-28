#include "stdafx.h"
#include "Block.h"
#include"Play.h"

void Block::update()
{
}

void Block::draw(double camera_y)
{
	switch (nature)
	{
	case normal:
		//hit_box.movedBy(Vec2{ 0,play->get_scene_size().y / 2 } - Vec2{ 0,camera_y }).draw(Palette::Brown);
		for (int i = 0; i < tex_num; i++) {
			Vec2 tex_pos = hit_box.pos + Vec2{ 50 * i , 0 } + Vec2{ 0,play->get_scene_size().y / 2 } - Vec2{ 0,camera_y };

			TextureAsset(U"normal").draw(tex_pos);

		}
		break;
	case slime:
		for (int i = 0; i < tex_num; i++) {
			Vec2 tex_pos = hit_box.pos + Vec2{ 50 * i , 0 } + Vec2{ 0,play->get_scene_size().y / 2 } - Vec2{ 0,camera_y };

			TextureAsset(U"slime").draw(tex_pos);

		}
		break;
	default:
		break;
	}
	
}
