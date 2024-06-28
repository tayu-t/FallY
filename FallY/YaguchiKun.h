#pragma once

class Play;

enum class Act_Kind
{
	move,
	jump,
};

class YaguchiKun
{
private:
	Vec2 pre_pos{ 0,0 };
	Vec2 pos{ 0,100 };
	double key_acc{ 700 };
	Vec2 speed{ 0,0 };
	double x_speed_max{ 400 };
	int hp{ 10 };
	static constexpr double scale{ 1.2 };
	double height{ 45*scale };
	double width{ 30*scale };
	RectF hit_box;
	Play* play;
	double gravity{ 850 };
	bool grounded{ false };

public:
	YaguchiKun(Play* play) :play(play)
	{
		pos = Vec2{Scene::Size().x/2, 0};
		hit_box = RectF(Arg::center(pos), width, height);
	};

	void update();
	void update_key_move();
	void draw(double camera_y);

	inline RectF& get_hit_box() noexcept { return hit_box; }
	inline const Vec2 get_pre_pos() noexcept { return pre_pos; }
	inline const Vec2 get_pos() noexcept { return pos; }
	inline void set_pos(Vec2 t)noexcept {
		pos = t;
		hit_box = RectF(Arg::center(pos), width, height);
	}

	inline void set_speed(Vec2 t) noexcept { speed = t; }
	inline Vec2 get_speed()noexcept { return speed; }

	inline bool& get_grounded() noexcept { return grounded; }
};

