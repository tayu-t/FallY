#include "stdafx.h"
#include "Play.h"

void Play::create_stage()
{
	double between_dis = right_wall - left_wall;

	while (pre_create_y - camera_y < 600) {
		

		double create_y = pre_create_y + Random(300,400);

		if (RandomBool(0.2))
		{
			double clock_x = Random(left_wall + 50,right_wall - 50);
			clocks << Clock(Circle{ clock_x,create_y - Random(25,40),16});
		}
		bool left_start = RandomBool(0.5);
		double spon_x{ left_wall };
		

		
		for (int i = 0; i < 9;) {
			int l = Random(2, 5);
			double width = l*50;
			double height = 20;
			int del = Random(2,3);
			Block_Nature b_kind;
			if (RandomBool(0.7)) {
				b_kind = slime;
			}
			b_kind = Block_Nature(Random(0, Block_Nature::num - 1));


			if (left_start) {
				spon_x = left_wall + i * 50;
				blocks << Block(this, RectF(Vec2{ spon_x,create_y }, width, 20), b_kind);
				i += l + del;

			}
			else {
				spon_x = right_wall - i * 50;
				blocks << Block(this, RectF(Vec2{ spon_x - width,create_y }, width, 20), b_kind);
				i += l +del;

			}
		}

		pre_create_y = create_y;
		
	}

}

void Play::update()
{

	scene_del = Scene::DeltaTime();
	create_stage();

	if (scene == start)
	{
		timer = limit_time;
		if (KeyRight.pressed() || KeyLeft.pressed()) {
			scene = play;
		}
	}
	else if (scene == play)
	{
		yaguchi.update();
		timer -= scene_del;
		if (timer <= 0) {
			scene = result;
			if (bestscore <= score) {
				bestscore = score;
			}
		}
	}
	else if (scene == result)
	{
		result_y += (300 - result_y) / 8;

		if (KeySpace.pressed()) {
			scene = start;
			camera_y = 0;
			yaguchi.set_speed(Vec2{ 0,0 });
			yaguchi.set_pos(Vec2{ scene_size.x / 2,0 });
			score = 0;
			pre_create_y = -10;
			result_y = -10;
			blocks.clear();
			create_stage();
			
		}
	}

	for (auto& c : clocks) {
		if (c.circle.intersects(yaguchi.get_hit_box())) {
			c.t = false;
			timer += Random(3,8);
		}
	}

	clocks.remove_if([&](Clock clock) {
		return clock.t == false;
	});

	blocks.remove_if([&](Block block) {
		return block.get_hit_box().bottomY() <= -300;
	});

	score = Max(score, int(yaguchi.get_pos().y / 20));
	for_ground_y += (yaguchi.get_pos().y + 200 - camera_y) / 3;

	while (for_ground_y >= 50) {
		for_ground_y -= 50;
	}
	while (for_ground_y <= -50) {
		for_ground_y += 50;
	}

	camera_y += (yaguchi.get_pos().y + 200 - camera_y) / 3;
	

	intersect();
}

void Play::draw()
{
	RectF(0, 0, scene_size).draw(Arg::top = Palette::Cornflowerblue,Arg::bottom = Palette::Paleturquoise);

	for (auto& b : blocks) {
		b.draw(camera_y);
	}

	for (auto& c : clocks) {
		c.circle.movedBy(Vec2{ 0,scene_size.y / 2 } - Vec2{ 0,camera_y }).draw();
		TextureAsset(U"clock").drawAt(c.circle.center + Vec2{ 0,scene_size.y / 2 } - Vec2{ 0,camera_y });
	}

	yaguchi.draw(camera_y);



	RectF(right_wall, 0, scene_size).draw(Palette::Black);
	for (int y = -100; y <= scene_size.y + 100; y += 50) {
		TextureAsset(U"ground_l").draw(left_wall - 50, y - for_ground_y);
		TextureAsset(U"ground_r").draw(right_wall,y - for_ground_y);
	}

	Line{ left_wall,bestscore * 20,right_wall,bestscore * 20 }.movedBy(Vec2{ 0,scene_size.y / 2 } - Vec2{ 0,camera_y }).draw(2,Palette::Yellow);
	FontAsset(U"40")(U"BestDepth").draw(Vec2{ right_wall + 40 ,bestscore * 20 } + Vec2{ 0,scene_size.y / 2 } - Vec2{ 0,camera_y });

	FontAsset(U"40")(U"Depth\n{}m"_fmt(score)).draw(right_wall+50, 0);
	FontAsset(U"40")(U"Time").draw(right_wall + 50, 100);
	FontAsset(U"40")(U"{}s"_fmt(int(timer))).draw(right_wall + 50, 150,Palette::Yellow);


	if (scene == start)
	{
		FontAsset(U"50")(U"Press←→").draw(scene_size/2, Palette::Yellow);
	}
	else if (scene == play)
	{

	}
	else if (scene == result)
	{

		FontAsset(U"40")(U"Score\n{}"_fmt(score)).draw(Vec2{ scene_size.x / 2 - 100 ,result_y  }, Palette::Yellow);
		FontAsset(U"40")(U"BestScore\n{}"_fmt(bestscore)).draw(Vec2{ scene_size.x / 2 - 100 ,result_y + 120 }, Palette::Yellow);
		FontAsset(U"40")(U"PressSpace").draw(Vec2{ scene_size.x / 2 - 100,result_y + 300}, Palette::Yellow);
	}

	if (scene == start) {

	}

}

void Play::intersect()
{
	//壁との衝突
	if (yaguchi.get_hit_box().x <= left_wall) {
		yaguchi.set_pos(Vec2(left_wall + yaguchi.get_hit_box().w / 2, yaguchi.get_pos().y));
		yaguchi.set_speed(Vec2{ yaguchi.get_speed().x * -0.01, yaguchi.get_speed().y });
	}
	else if(yaguchi.get_hit_box().rightX() >= right_wall) {

		yaguchi.set_pos(Vec2(right_wall - yaguchi.get_hit_box().w / 2, yaguchi.get_pos().y));

		yaguchi.set_speed(Vec2{ yaguchi.get_speed().x * -0.01, yaguchi.get_speed().y });
	}
	yaguchi.get_grounded() = false;
	//blockとの衝突
	for (auto& b : blocks) {
		if (b.get_hit_box().intersects(yaguchi.get_hit_box())) {
			double line_rate = 0.02;
			//yaguchiの下面は前のフレームではstageの上面より上にあった
			if (yaguchi.get_pre_pos().y + yaguchi.get_hit_box().h/2 <= b.get_hit_box().y)
			{
				if (yaguchi.get_hit_box().bottomY() >= b.get_hit_box().y)
				{


					double intersect_line_begin;//交差している部分
					double intersect_line_end;//交差している部分

					intersect_line_begin = Max(yaguchi.get_hit_box().x, b.get_hit_box().x);
					intersect_line_end = Min(yaguchi.get_hit_box().rightX(), b.get_hit_box().rightX());

					double dis_begin_end = intersect_line_end - intersect_line_begin;
					if (dis_begin_end / yaguchi.get_hit_box().w >= line_rate)
					{
						yaguchi.set_pos(Vec2{ yaguchi.get_pos().x,b.get_hit_box().y - 0.01 - yaguchi.get_hit_box().h/2});
						yaguchi.set_speed(Vec2{ yaguchi.get_speed().x ,yaguchi.get_speed().y * -b.get_e() });
						yaguchi.get_grounded() = true;
					}
				}
			}



			
			//actorの上面は前のフレームではstageの下面より下にあった
			if (yaguchi.get_pre_pos().y - yaguchi.get_hit_box().h / 2 >= b.get_hit_box().bottomY())
			{

				if (yaguchi.get_hit_box().y <= b.get_hit_box().bottomY())
				{
					double intersect_line_begin;//交差している部分
					double intersect_line_end;//交差している部分

					intersect_line_begin = Max(yaguchi.get_hit_box().x, b.get_hit_box().x);
					intersect_line_end = Min(yaguchi.get_hit_box().rightX(), b.get_hit_box().rightX());

					double dis_begin_end = intersect_line_end - intersect_line_begin;
					if (dis_begin_end / yaguchi.get_hit_box().w >= line_rate)
					{
						yaguchi.set_pos(Vec2{ yaguchi.get_pos().x,b.get_hit_box().bottomY() + 0.01 + yaguchi.get_hit_box().h/2});
						yaguchi.set_speed(Vec2{ yaguchi.get_speed().x ,yaguchi.get_speed().y * -b.get_e() });

					}
				}
			}



			//actorがstageの右にあたる

			//actorの左面は前のフレームではstageの右面より右にあった
			if (yaguchi.get_pre_pos().x - yaguchi.get_hit_box().w/2 >= b.get_hit_box().rightX())
			{
				if (yaguchi.get_hit_box().x <= b.get_hit_box().rightX())
				{
					double intersect_line_begin;//交差している部分
					double intersect_line_end;//交差している部分

					intersect_line_begin = Max(yaguchi.get_hit_box().y, b.get_hit_box().y);
					intersect_line_end = Min(yaguchi.get_hit_box().bottomY(), b.get_hit_box().bottomY());


					double dis_begin_end = intersect_line_end - intersect_line_begin;
					if (dis_begin_end / yaguchi.get_hit_box().h >= line_rate)
					{

						yaguchi.set_pos(Vec2{ b.get_hit_box().rightX() + 0.01 + yaguchi.get_hit_box().w/2,yaguchi.get_pos().y});
						yaguchi.set_speed(Vec2{ yaguchi.get_speed().x * -b.get_e(),yaguchi.get_speed().y  });

					}
				}
			}


			//actorがstageの左にあたる
			//actorの右面は前のフレームではstageの左面より左にあった
			if (yaguchi.get_pre_pos().x + yaguchi.get_hit_box().w/2 <= b.get_hit_box().x)
			{
				if (yaguchi.get_hit_box().rightX()  >= b.get_hit_box().x)
				{
					double intersect_line_begin;//交差している部分
					double intersect_line_end;//交差している部分

					intersect_line_begin = Max(yaguchi.get_hit_box().y, b.get_hit_box().y);
					intersect_line_end = Min(yaguchi.get_hit_box().bottomY(), b.get_hit_box().bottomY());


					double dis_begin_end = intersect_line_end - intersect_line_begin;
					if (dis_begin_end / yaguchi.get_hit_box().h >= line_rate)
					{
						yaguchi.set_pos(Vec2{ b.get_hit_box().x - 0.01 - yaguchi.get_hit_box().w / 2,yaguchi.get_pos().y });
						yaguchi.set_speed(Vec2{ yaguchi.get_speed().x * -b.get_e(),yaguchi.get_speed().y });


					}
				}
			}

		}
	}


}
