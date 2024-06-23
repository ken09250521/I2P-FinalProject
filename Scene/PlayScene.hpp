#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"

class Turret;
namespace Engine {
	class Group;
	class Image;
	class Label;
	class Sprite;
}  // namespace Engine

class PlayScene final : public Engine::IScene {
private:
	enum TileType {
		TILE_DIRT,
		TILE_FLOOR,
		TILE_OCCUPIED,
		TILE_SLIME
	};
	ALLEGRO_SAMPLE_ID bgmId;
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> deathBGMInstance;
protected:
	int money;
	int SpeedMult;
	std::string speedmultStr;

public:
	static bool DebugMode;
	static const std::vector<Engine::Point> directions;
	static const int MapWidth, MapHeight;
	static const int BlockSize;
	static const float DangerTime;
	static const Engine::Point AllySpawnGridPoint;
	static const Engine::Point AllyEndGridPoint;
	static const Engine::Point EnemySpawnGridPoint;
	static const Engine::Point EnemyEndGridPoint;
	static const std::vector<int> code;
	static const int Y;
	int MapId;
	float ticks;
	int lives;
	float deathCountDown;
	int fscore;
	int finalScore;
	int killcount;
	// Map tiles.
	Group* TileMapGroup;
	Group* GroundEffectGroup;
	Group* DebugIndicatorGroup;
	Group* BulletGroup;
	Group* TowerGroup;
	Group* CharacterGroup;
	Group* EnemyGroup;
	Group* EffectGroup;
	Group* UIGroup;
	Engine::Label* UIMoney;
	Engine::Label* UILives;
	Engine::Label* UIScore;
	Engine::Image* imgTarget;
	Engine::Sprite* dangerIndicator;
	Turret* preview;
	std::vector<std::vector<TileType>> mapState;
	std::vector<std::vector<int>> mapDistance;
	std::list<std::pair<int, float>> enemyWaveData;
	std::list<int> keyStrokes;
	static Engine::Point GetClientSize();
	explicit PlayScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Draw() const override;
	// void OnMouseDown(int button, int mx, int my) override;
	// void OnMouseMove(int mx, int my) override;
	// void OnMouseUp(int button, int mx, int my) override;
	void OnKeyDown(int keyCode) override;
	// void Hit();
	int GetMoney() const;
	void EarnMoney(int money);
	void ReadMap();
	void ReadEnemyWave();
	void ConstructUI();
	// void UIBtnClicked(int id);
	bool CheckSpaceValid(int x, int y);
	void enemyDeathCount();
	std::vector<std::vector<int>> CalculateBFSDistance();
	// void ModifyReadMapTiles();
};
#endif // PLAYSCENE_HPP
