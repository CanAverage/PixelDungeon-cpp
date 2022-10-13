#pragma once
#include <string>
class Texture;

struct Window
{
	Window(const std::string& title = "Title", float width = 320.0f,
	       float height = 180.0f, bool isVSyncOn = true);

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Point2f
{
	Point2f();
	Point2f(float x, float y);

	float x;
	float y;
};

struct Point2i
{
	Point2i();
	Point2i(int x, int y);

	int x;
	int y;
};

struct Rectf
{
	Rectf();
	Rectf(float left, float bottom, float width, float height);

	float left;
	float bottom;
	float width;
	float height;
};


struct Color4f
{
	Color4f();
	Color4f(float r, float g, float b, float a);

	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Circlef();
	Circlef(const Point2f& center, float radius);
	Circlef(float centerX, float centerY, float radius);

	Point2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef();
	Ellipsef(const Point2f& center, float radiusX, float radiusY);
	Ellipsef(float centerX, float centerY, float radiusX, float radiusY);

	Point2f center;
	float radiusX;
	float radiusY;
};

struct FxElement
{
	FxElement(Rectf rect, Texture* texture, float creationTimer);
	Rectf rect;
	Texture* texture;
	float creationTimer;
};


struct TextureInfo
{
	TextureInfo(int idleBegin, int idleLength, int walkBegin, int walkLength, int atackBegin, int attackLength,
	            int deathBegin, int deathLength);
	int idleBegin;
	int idleLength;
	int walkBegin;
	int walkLength;
	int attackBegin;
	int attackLength;
	int deathBegin;
	int deathLength;
};
