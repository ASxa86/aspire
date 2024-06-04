#include <aspire/Engine.h>
#include "Ball.h"
#include "Paddle.h"

int main(int argc, char** argv)
{
	aspire::Engine engine{argc, argv};

	aspire::Input input{engine};
	aspire::Action actionUp{input, Action::Up};
	action.addEvent(aspire::EventKeyboard::Key::Up);

	aspire::Action actionDown{input, Action::Down};
	action.addEvent(aspire::EventKeyboard::Key::Down);

	Menu menu{engine};
	menu.visible(true);

	World world;
	world.visible(false);
	Ball ball{engine};
	ball.setRadius(10.0f);
	ball.setColor(Color::White());
	ball.setVelocity(30.0f, 0.0f);
	ball.setPosition({.x = window.width / 2, .y = window.height / 2});

	Paddle paddle;
	paddle.setSize({.w = 25.0f, .h = 100.0f});
	paddle.setColor(Color::White());
	paddle.setPosition({.x = window.width - 100, .y = window.height / 2});
	paddle.onProcess([&](dt) { paddle.move({paddle.position().x, ball.position().y}); });

	Player player;
	player.setSize(paddle.size());
	player.setColor(paddle.color());
	player.setPosition({.x = 100, .y = window.height / 2});
	player.onAction(
		[&player](action)
		{
			auto pos = player.position();

			if(action.pressed(Action::Up) == true)
			{
				pos.y += 50;
			}

			if(action.pressed(Action::Down) == true)
			{
				pos.y -= 50;
			}

			player.setPosition(pos);
		});

	engine.onProcess(
		[&](auto dt)
		{
			// if ball cross left or right window edge.
			// Reset its position.
			// Increment player/paddle score;
		});

	engine.onAction(
		[&](auto action) {

		});

	return engine.run();
}
