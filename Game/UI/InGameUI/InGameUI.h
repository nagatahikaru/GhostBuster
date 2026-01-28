/**
* UI.h
* 画面に表示されるUIの基底クラス
*/
#pragma once
#include "InGameUI.h"
#include "UI/UI.h"

class Player;

// ========================================
// 定数定義（コンパイル時計算）
// ========================================
enum EnTime {
    enTime_sec,
    enTime_tensec,
    enTime_min,
    enTime_tenmin,
    enTime_num
};

enum EnResidue {
    enResidue_owncount,
    enResidue_tencount,
    enResidue_mincount,
    enResidue_num
};

enum EnItem {
    enItem_none,
    enItem_snowball,
    enItem_star,
    enItem_mushroom,
    enItem_Book,
    enItem_num
};

enum { enMaxScoreDigit = 6 };

enum EnScoreType {
    enScoreType_Item,
    enScoreType_NormalEnemy,
    enScoreType_GimmickEnemy,
    enScoreType_BossEnemy,
    enScoreType_TimeBonus,
    enScoreType_Num
};

// ========================================
// 定数（コンパイル時最適化）
// ========================================
namespace UIColors {
    constexpr float BLACK = 1.0f;
    constexpr float TRANSPARENCY_DEFAULT = 0.5f;
    constexpr float TRANSPARENCY_FULL = 1.0f;
    constexpr float BLUE = 0.81960784313f;
    constexpr float GREEN = 0.63137254902f;
    constexpr float CYAN = 0.0f;
    constexpr float RED = 0.0f;
}

namespace nsUI {
    namespace nsTimer {
        constexpr int ONE_SECOND = 1;
        constexpr int TEN_SECOND = 10;
        constexpr int ONE_MINUTE = 60;
        constexpr int TEN_MINUTE = 600;
        constexpr float LIMIT = 120.0f;

        const Vector3 POS[enTime_num] = {
            { 960.0f, 490.0f, 0.0f },
            { 860.0f, 490.0f, 0.0f },
            { 660.0f, 490.0f, 0.0f },
            { 560.0f, 490.0f, 0.0f }
        };

        constexpr int DIGIT[enTime_num] = {
            ONE_SECOND, TEN_SECOND, ONE_MINUTE, TEN_MINUTE
        };

        const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };
    }

    namespace nsResidue {
        constexpr int ONE_COUNT = 1;
        constexpr int TEN_COUNT = 10;
        constexpr int HUN_COUNT = 100;
        constexpr int MIN = 0;
        constexpr int MAX = 999;

        const Vector3 POS[enResidue_num] = {
            { -570.0f, 445.0f, 0.0f },
            { -670.0f, 445.0f, 0.0f },
            { -770.0f, 445.0f, 0.0f }
        };

        constexpr int COUNT[enResidue_num] = {
            ONE_COUNT, TEN_COUNT, HUN_COUNT
        };

        const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };
    }

    namespace nsScore {
        const Vector3 POS[enMaxScoreDigit] = {
            { 960.0f, 390.0f, 0.0f },
            { 860.0f, 390.0f, 0.0f },
            { 760.0f, 390.0f, 0.0f },
            { 660.0f, 390.0f, 0.0f },
            { 560.0f, 390.0f, 0.0f },
            { 460.0f, 390.0f, 0.0f },
        };

        constexpr int DIGIT[enMaxScoreDigit] = {
            1, 10, 100, 1000, 10000, 100000
        };

        constexpr int MIN = 0;
        constexpr int MAX = 999999;

        const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };

        const int TYPE[enScoreType_Num] = {
            50, 100, 150, 500, 20
        };
    }

    namespace nsItem {
        const Vector3 POS[enItem_num] = {
            { -900.0f, -400.0f, 0.0f },
            { -900.0f, -400.0f, 0.0f },
            { -900.0f, -400.0f, 0.0f },
            { -900.0f, -400.0f, 0.0f },
            { -900.0f, -400.0f, 0.0f }
        };

        constexpr int NONE = 0;
        const Vector3 SCALE = { 100.0f, 100.0f, 1.0f };
    }
}

// ========================================
// 軽量化された構造体
// ========================================
struct Timer {
    int nowTime = 0;
    SpriteRender spriteRender;
};

struct Residue {
    int nowResidue = 0;
    SpriteRender spriteRender;
};

struct Item {
    int nowItem = 0;
    SpriteRender spriteRender;
};

struct Score {
    int nowScore = 0;
    SpriteRender spriteRender;
};

// ========================================
// 最適化された InGameUI クラス
// ========================================
class InGameUI : public UI
{
public:
    InGameUI() {};
    ~InGameUI();
    
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;
    
    // アクセサ（inline 化で高速化）
    bool GetSBlackout() const { return m_blackout; }
    void SetBlackout(bool blackout) { 
        m_blackout = blackout;
        m_directionUpdateFlag = true;
    }
    
    bool GetSceneMovement() const { return m_sceneMovement; }
    float GetNowTime() const { return m_nowTime; }
    int GetNowScore() const { return m_nowScore; }
    
    void AddScore();
    int GetScore()
    {
        return m_nowScore;
    }

private:
    // ========================================
    // HOT DATA（頻繁にアクセス - キャッシュ最適化）
    // ========================================
    Player* m_player = nullptr;
    float m_gameTimer = 0.0f;
    float m_nowTime = nsUI::nsTimer::LIMIT;
    int m_nowResidue = 0;
    int m_nowItem = 0;
    int m_nowScore = 0;
    int m_TimeBonusScore = 0;
    int m_pastScore = 0;
    
    // フラグ（1 byte ずつでパディング最適化）
    bool m_blackout = false;
    bool m_sceneMovement = false;
    bool m_scoreUpdateFlag = false;
    bool m_residueUpdateFlag = false;
    bool m_itemUpdateFlag = false;
    bool m_directionUpdateFlag = false;
    bool m_selectionUpdateFlag = false;
    // パディング 1 byte

    // ========================================
    // WARM DATA（たまにアクセス）
    // ========================================
    float m_overFrameTransparency = 1.0f;
    float m_lordFrameTransparency = 0.5f;

    // ========================================
    // COLD DATA（初期化時のみ）
    // ========================================
    std::array<Timer, enTime_num> m_timeUI;
    std::array<Residue, enResidue_num> m_residueUI;
    std::array<Item, enItem_num> m_itemUI;
    std::array<Score, enMaxScoreDigit> m_scoreUI;
    
    SpriteRender m_koronSprite;
    SpriteRender m_overSelectionFrame;
    SpriteRender m_lordSelectionFrame;
    SpriteRender m_playerfestureUI;
    SpriteRender m_itemColumnUI;
    SpriteRender m_map;
    std::vector<SpriteRender> m_spritePool;  // 実体はここで一括管理

    // ========================================
    // プライベートメソッド
    // ========================================
    void MeasureNowTime();
    void Direction();
    void Selection();
    
    void PlayerResidueUI();
    void InitializeTimer();
    void InitializeResidue();
    void InitializeItem();
    void InitializeScore();
    void ItemUI();
    void MapUI();
};

