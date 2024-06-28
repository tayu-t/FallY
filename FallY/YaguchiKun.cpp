#include "stdafx.h"
#include "YaguchiKun.h"
#include"Play.h"

void YaguchiKun::update()
{
	pre_pos = pos;
	update_key_move();
	
	hit_box = RectF(Arg::center(pos), width, height);
}

void YaguchiKun::update_key_move()
{
	
	bool t =true;
	if (KeyRight.pressed()) {
		speed.x += key_acc*play->get_scene_del();
		t = false;
	}

	if (KeyLeft.pressed()) {
		speed.x -= key_acc * play->get_scene_del();
		t = false;
	}

	if (grounded && t) { speed.x *= 0.7; }
	

	speed.x = Clamp<double>(speed.x, -x_speed_max, x_speed_max);

	speed.y += gravity * play->get_scene_del();
	//speed.y = Max<double>(speed.y, 600);

	pos += speed * play->get_scene_del();
}



void YaguchiKun::draw(double camera_y)
{
	
	//hit_box.movedBy(Vec2{ 0,play->get_scene_size().y / 2 } - Vec2{0,camera_y}).draw(Palette::Skyblue);

	
	TextureAsset(U"yaguchi").mirrored(speed.x <= 0).scaled(0.2).drawAt(pos + Vec2{0,play->get_scene_size().y / 2} - Vec2{0,camera_y});
}
