#pragma once

#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:

	TitleScene() { Init(); }
	~TitleScene() {};

private:

	void Event() override;
	void Init()  override;

	std::shared_ptr <KdAudioManager>	m_spAudio;			//効果音

	bool	m_ClickFlg = true;
};
