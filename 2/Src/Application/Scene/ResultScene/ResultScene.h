#pragma once

#include"../BaseScene/BaseScene.h"

class ResultScene : public BaseScene
{
public:

	ResultScene() { Init(); }
	~ResultScene();

private:

	void Event() override;
	void Init()  override;

	std::shared_ptr <KdAudioManager>	m_spAudio;			//効果音

	bool	m_ClickFlg = true;
};
#pragma once
