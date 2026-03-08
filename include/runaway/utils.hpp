#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <random>
#include <string>

// NOTE: If you encounter issues with SOIL loading assets, you should change the path below.
// On Mac OS or Linux, it should be the relative path from the terminal where you
// run the program, to the assets/ folder.
// It is recommended to run the program with the command "./bin/runaway" while your
// terminal is in the build/ directory. If so, the path below should be correct.
// On Windows, if you are using Visual Studio, it should be the relative path from the
// .sln file (../assets/). If you are running the program in command line or by double-clicking, it
// should be from the .exe (../../assets/).
// Especially when you need to build your game for others to play,
// make sure to change this if needed, and ensure your assets are loaded correctly.
// For example, if you want to package your game like the sample game we provide,
// you should change this to ".assets/", because the .exe (or MacOS/Linux executable)
// is in the same directory as the assets folder.
static const std::string ASSET_DIR = "assets/";

// Returns a random integer within [min, max] (inclusive).
inline int randInt(int min, int max)
{
	if (max < min)
		std::swap(max, min);
	static std::random_device rd;
	static std::mt19937 generator(rd());
	std::uniform_int_distribution<> distro(min, max);
	return distro(generator);
}

enum class LevelStatus
{
	ONGOING,
	LOSING
};

enum class KeyCode
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	JUMP,
	FIRE1, // Left mouse button
	FIRE2, // Right mouse button
	ENTER, // Enter
	QUIT   // Esc
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

enum class ImageID
{
	NONE = 0,
	BACKGROUND,
	PLAYER,
	BULLET,
	GOBLIN,
	AXE,
	GAME_OVER = 100
};

enum class AnimID
{
	NO_ANIMATION = 0,
	IDLE,
	THROW,
	HURT,
	BOOST,
	JUMP
};

const int MAX_LAYERS = 7;

enum class LayerID
{
	UI = 0,
	PLAYER,
	ENEMIES,
	PROJECTILES,
	BACKGROUND
};

const int MS_PER_FRAME = 33;

#endif // !UTILS_HPP__

