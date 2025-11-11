#pragma once
#include <vector>
#include <string>
#include <typeinfo>





template<typename T>
class GenericFactory {
public:
	T* Create(const char* name = nullptr) { return NewGO<T>(0, name ? name : typeid(T).name()); }
	void Destroy(T* obj) { DeleteGO(obj); }
};


//
// ObjectPool クラス
// ------------------------
// 汎用的なオブジェクトプールテンプレート。
// 頻繁に生成・削除されるゲームオブジェクト（弾・敵・エフェクトなど）を
// 事前に確保・再利用することで、パフォーマンスを向上させる目的で使用する。
//
// T は IGameObject を継承した型を想定。
// 使用例：
//   ObjectPool<SnowBall> snowBallPool;
//   snowBallPool.Init(12, "snowBall");
//   auto ball = snowBallPool.GetInactive();
//   if (ball) { ball->Fire(...); }
//
template<typename T>
class ObjectPool {
	std::vector<T*> m_pool;	// プール内のオブジェクト一覧
	GenericFactory<T>m_factory;
public:

	//
	// Init
	// ------------------------
	// 指定された数だけオブジェクトを生成し、非アクティブ状態にしてプールに格納する。
	//
	// count : 生成するオブジェクト数
	// name  : GameObject名（FindGOなどで識別したい場合に使用）
	//
	void Init(size_t count, const char* name = nullptr) {
		for (size_t i = 0; i < count; ++i) {
			auto obj =m_factory.Create(name);
			obj->Deactivate();	// 初期状態では非アクティブ
			m_pool.push_back(obj);
		}
	}

	//
	// GetInactive
	// ------------------------
	// プール内から「非アクティブなオブジェクト」を探して返す。
	// すべて使用中の場合、autoExpand が true なら新規生成してプールに追加する。
	//
	// autoExpand : trueならプールを自動拡張して新規オブジェクトを生成
	// 戻り値     : 使用可能なオブジェクトポインタ（存在しない場合はnullptr）
	//
	T* GetInactive(bool autoExpand = true) {
		for (auto obj : m_pool) {
			if (!obj->IsActive())
				return obj;
		}

		if (autoExpand) {
			auto obj =m_factory.Create(typeid(T).name());
			obj->Deactivate();
			m_pool.push_back(obj);
			return obj;
		}
		return nullptr;
	}

	//
	// Spawn
	// ------------------------
	// 指定した時間間隔ごとにオブジェクトを自動的に取得し、アクティブ化する。
	// 経過時間は呼び出し元で保持する変数を参照渡しする。
	//
	// spawnInterval : 出現間隔（秒）
	// elapsedTime   : 経過時間（呼び出し元で管理するタイマー）
	// 戻り値        : 新たにアクティブ化されたオブジェクト（またはnullptr）
	//
	T* Spawn(float spawnInterval, float& elapsedTime) {
		elapsedTime += g_gameTime->GetFrameDeltaTime();
		if (elapsedTime >= spawnInterval) {
			auto obj = GetInactive();
			if (obj) {
				obj->Activate();
				elapsedTime = 0.0f;  // 時間リセット
				return obj;          // 生成（再利用）したオブジェクトを返す
			}
		}
		return nullptr;  // まだ時間に達していない、または空きがない
	}

	// GetActive
	// ------------------------
	// プール内のオブジェクトのうち、現在アクティブなものだけを集めて返す。
	// 戻り値は std::vector<T*> で、アクティブなオブジェクトのポインタ一覧。
	// - obj が nullptr の場合は無視する
	// - obj->IsActive() が false の場合も無視する
	//
	// 注意:
	// - 戻り値はコピーされるため、大量のオブジェクトがある場合はコストがかかる。
	// - 参照を返すバージョンにするとコピーを避けられるが、外部から誤って変更されるリスクもある。
	std::vector<T*> GetActive() const {
		std::vector<T*> activeObjs;
		for (auto obj : m_pool) {
			if (obj && obj->IsActive()) activeObjs.push_back(obj);
		}
		return activeObjs;
	}


	//
	// Clear
	// ------------------------
	// プール内の全オブジェクトを削除し、メモリを解放する。
	// ゲーム終了時やシーン遷移時に呼び出すことを想定。
	//
	void Clear() {
		for (auto it = m_pool.rbegin(); it != m_pool.rend(); ++it) {
			if (*it) {
				m_factory.Destroy(*it);
				*it = nullptr;
			}
		}
		m_pool.clear();
	}
};
