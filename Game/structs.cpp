#include "stdafx.h"
#include "structs.h"

//-----------------------------------------------------------------
// Window Constructors
//-----------------------------------------------------------------
Window::Window(const std::string& title, float width, float height, bool isVSyncOn)
	: title{title}
	  , width{width}
	  , height{height}
	  , isVSyncOn{isVSyncOn}
{
}

//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
Point2f::Point2f()
	: Point2f{0.0f, 0.0f}
{
}

Point2f::Point2f(float x, float y)
	: x{x}, y{y}
{
}

//-----------------------------------------------------------------
// Point2i Constructors
//-----------------------------------------------------------------
Point2i::Point2i()
	: Point2i{0, 0}
{
}

Point2i::Point2i(int x, int y)
	: x{x}, y{y}
{
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf()
	: Rectf{0.0f, 0.0f, 0.0f, 0.0f}
{
}

Rectf::Rectf(float left, float bottom, float width, float height)
	: left{left}
	  , bottom{bottom}
	  , width{width}
	  , height{height}
{
}

//-----------------------------------------------------------------
// Color4f Constructors
//-----------------------------------------------------------------
Color4f::Color4f()
	: Color4f{0.0f, 0.0f, 0.0f, 1.0f}
{
}

Color4f::Color4f(float r, float g, float b, float a)
	: r{r}
	  , g{g}
	  , b{b}
	  , a{a}
{
}

//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
Circlef::Circlef()
	: Circlef{0.0f, 0.0f, 0.0f}
{
}

Circlef::Circlef(float centerX, float centerY, float radius)
	: Circlef{Point2f{centerX, centerY}, radius}
{
}

Circlef::Circlef(const Point2f& center, float radius)
	: center{center}
	  , radius{radius}
{
}

//-----------------------------------------------------------------
// Ellipsef Constructors
//-----------------------------------------------------------------
Ellipsef::Ellipsef()
	: Ellipsef{0.0f, 0.0f, 0.0f, 0.0f}
{
}


Ellipsef::Ellipsef(const Point2f& center, float radiusX, float radiusY)
	: center{center}
	  , radiusX{radiusX}
	  , radiusY{radiusY}
{
}

Ellipsef::Ellipsef(float centerX, float centerY, float radiusX, float radiusY)
	: Ellipsef{Point2f{centerX, centerY}, radiusX, radiusY}
{
}


FxElement::FxElement(Rectf rect, Texture* texture, float creationTimer) : rect(rect), texture(texture),
                                                                          creationTimer(creationTimer)
{
}


TextureInfo::TextureInfo(int idleBegin, int idleLength, int walkBegin, int walkLength, int atackBegin, int attackLength,
                         int deathBegin, int deathLength)
	: idleBegin(idleBegin), idleLength(idleLength), walkBegin(walkBegin), walkLength(walkLength),
	  attackBegin(atackBegin), attackLength(attackLength), deathBegin(deathBegin), deathLength(deathLength)
{
}
