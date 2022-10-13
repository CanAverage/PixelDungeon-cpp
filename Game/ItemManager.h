#pragma once
#include <vector>
#include "Texture.h"
#include "Player.h"
class Item;
class Item_Bubble;
class Item_Weapon;
class Item_Armor;
class Inventory;

class ItemManager
{
public:
	enum items
	{
		Bones,
		BlessedCross,
		IronSword,
		BasicStaff,
		Food,
		UnknownSword,
		UnknownArmor,
		UnknownRing,
		SkullKey,
		IronKey,
		GoldRing,
		Chest,
		ChestKey,
		Grave,
		Gold,
		Shuriken,
		Knuckles,
		Polearm,
		Mace,
		Dagger,
		SteelSword,
		GreatSword,
		BattleAxe,
		SledgeHammer,
		ClothArmor,
		LeatherArmor,
		ChainMail,
		PlateArmor,
		IronArmor,
		IronSpear,
		SteelSpear,
		Arrow,
		WhiteRing,
		BlueRing,
		DarkRedRing,
		RedRing,
		PurpleRing,
		LightGreenRing,
		DarkGreenRing,
		DarkBlueRing,
		YScroll,
		NScroll,
		IScroll,
		OScroll,
		XScroll,
		RScroll,
		lScroll,
		ForkScroll,
		ApprenticeStaff,
		DarkOrangeStaff,
		DarkBrownStaff,
		OrangeStaff,
		LightBrownStaff,
		BrownStaff,
		KakiStaff,
		RedStaff,
		LightBluePotion,
		RedPotion,
		BluePotion,
		GreenPotion,
		YellowPotion,
		PinkPotion,
		DarkGrayPotion,
		WhitePotion,
		OrangePotion,
		BrownPotion,
		PurplePotion,
		GrayPotion,
		GreenStaff,
		PinkStaff,
		SageStaff,
		GrayStaff,
		GreenRing,
		PurpleBlueRing,
		PinkRing,
		GrayRing,
		SScroll,
		FScroll,
		UnknownScroll,
		TScroll,
		EnchantRod,
		Bubble,
		Book,
		Bag,
		Torch,
		Radio,
		BlackSmithTools,
		Elements,
		OrangeSeed,
		BlueSeed,
		PurpleSeed,
		YellowSeed,
		GreenSeed,
		BrownSeed,
		WhiteSeed,
		RedSeed,
		GrayUniform,
		PaladinArmor,
		RedRode,
		InvisibilityCloak,
		RedRose,
		PickAxe,
		GoldChunk,
		FetidRat,
		ChocolateBar,
		PaladinChest,
		Boomerang,
		Axe,
		ExplosiveArrow,
		GoldArrow,
		SteelArrow,
		Quiver,
		FancyFood,
		UnknownMeat,
		CookedUnknownMeat,
		FancyMeal,
		PinkMeat,
		MonsterScroll,
		Fish,
		Empty,
		DewVial,
		Radar,
		GoldPlate,
		UnknownRock,
		Bomb,
		HoneyPot,
		Keychain,
		Unknown
	};

	ItemManager(Player* player, SoundManager* soundManager);
	~ItemManager();
	void SpawnItem(int textureIndex, bool equipment, Point2f pos);
	void ChanceToSpawnItem(int Rarity, Point2f pos);
	void SpawnBubble(Point2f pos);
	void Draw() const;
	void Update(float elapsedSec);
	void RemoveItem(int index);
	void DeleteItem(int index);
	void SetInventoryptr(Inventory* i);
	Item* GetItem(std::string name);
private:
	void LoadWeapons();
	void LoadArmor();
	std::vector<Item*> m_pItems{};
	std::vector<Item_Weapon*> m_pWeaponTemplates{};
	std::vector<Item_Armor*> m_pArmorTemplates{};
	int m_IndexCounter{0};
	const int m_ChanceToSpawnItem{4};
	const int m_ChanceForTier3Item{5};
	const int m_ChanceForTier2Item{20};
	Texture* m_pItemTextures;
	SoundManager* m_pSoundManager;
	Inventory* m_pInventory;
	Player* m_pPlayer;
	const int m_ChanceToDropBubble{33};
};
