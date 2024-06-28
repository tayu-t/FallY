#pragma once
#include"YaguchiKun.h"
#include"Block.h"

enum class Play_Scene
{
	start,
	play,
	result,
};

class Clock
{
public:
	Circle circle;
	bool t{true};
};

class Play
{
private:
	using enum Play_Scene;
	Play_Scene scene = start;
	static constexpr Vec2 scene_size{700,780};
	double scene_del{ 0 };
	static constexpr double left_wall{50};
	static constexpr double right_wall{ scene_size.x - 200 };
	double camera_y{ 100 };
	double pre_create_y{ -10 };
	YaguchiKun yaguchi{ this };
	double for_ground_y{0};
	double timer{ 0 };
	double limit_time{ 30 };

	double result_y{ -10 };

	Array<Clock> clocks;

	int score{ 0 };
	int bestscore{ 0 };

	Array<Block> blocks;



public:
	void create_stage();
	void update();
	void draw();
	void intersect();

	constexpr double get_left_wall() noexcept{ return left_wall; }
	constexpr double get_right_wall() noexcept{ return right_wall; }
	inline const double get_scene_del()noexcept { return scene_del; }
	inline const Vec2& get_scene_size()noexcept { return scene_size; }
};

