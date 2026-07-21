#pragma once

class RegisterObject;
class JsonManager;

//============================================================
// アプリケーションクラス
//	APP.～ でどこからでもアクセス可能
//============================================================
class Application
{
// メンバ
public:

	// アプリケーション実行
	void Execute();

	// アプリケーション終了
	void End()							{ m_endFlag = true; }

	HWND GetWindowHandle()		const	{ return m_window.GetWndHandle(); }
	int GetMouseWheelValue()	const	{ return m_window.GetMouseWheelVal(); }

	int		GetNowFPS()			const	{ return m_fpsController.m_nowfps; }
	int		GetMaxFPS()			const	{ return m_fpsController.m_maxFps; }
	float	GetDeltaTime()		const	{ return m_fpsController.GetDeltaTime(); }

	std::shared_ptr<RegisterObject> GetRegisterObjectClass() { return m_RegisterObjectClass; }

	std::shared_ptr<JsonManager> GetJsonManagerClass() { return m_JsonManagerClass; }

private:

	void KdBeginUpdate();
	void PreUpdate();
	void Update();
	void PostUpdate();
	void KdPostUpdate();

	void KdBeginDraw(bool usePostProcess = true);
	void PreDraw();
	void Draw();
	void PostDraw();
	void DrawSprite();
	void KdPostDraw();

	// アプリケーション初期化
	bool Init(int w, int h);

	// アプリケーション解放
	void Release();

	// ゲームウィンドウクラス
	KdWindow		m_window;

	// FPSコントローラー
	KdFPSController	m_fpsController;

	// ゲーム終了フラグ trueで終了する
	bool		m_endFlag = false;

	//ファクトリー登録クラス
	std::shared_ptr<RegisterObject>	m_RegisterObjectClass;

	//Jsonファイルの管理クラス
	std::shared_ptr<JsonManager>	m_JsonManagerClass;

//=====================================================
// シングルトンパターン
//=====================================================
private:
	// 
	Application() {}

public:
	static Application &Instance(){
		static Application Instance;
		return Instance;
	}
};
