# include <Siv3D.hpp> // Siv3D v0.6.12
#include"Play.h"




void Main()
{
	FontAsset::Register(U"40",40,Typeface::Icon_Awesome_Brand);
	FontAsset::Register(U"50", 50, Typeface::Mplus_Bold);

	TextureAsset::Register(U"yaguchi", Resource(U"yaguchi.png"));
	TextureAsset::Register(U"ground_l",Resource( U"ground.png"));
	TextureAsset::Register(U"ground_r", Resource(U"ground2.png"));
	TextureAsset::Register(U"normal", Resource(U"normal.png"));
	TextureAsset::Register(U"slime", Resource(U"slime.png"));
	TextureAsset::Register(U"clock", Resource(U"clock.png"));
	//Scene::SetBackground(Palette::Dodgerblue);
	Scene::Resize(700, 780);
	//Window::Centering();
	//Window::Resize(700, 780);
	
	Play play;

	

	while (System::Update())
	{
		play.update();
		play.draw();
	}
}
