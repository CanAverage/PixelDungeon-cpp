#pragma once
#include "utils.h"
#include <vector>
#include "structs.h"
#include <time.h>
#include <chrono>
class Texture;

class FxManager
{
public:
	FxManager();
	~FxManager();
	void CreateTexture(Rectf rect, int number);
	void CreateTexture(Rectf rect, std::string input);
	void Draw() const;
	void Update(float elapsedSec);
private:
	float m_ElapsedSec{};
	TTF_Font* pFont{};
	TTF_Font* pBackFont{};
	TTF_Font* pTextFont{};
	TTF_Font* pTextBackFont{};
	std::vector<FxElement*> m_pElements;
};
