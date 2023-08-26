#include "sbScene.h"
#include "sbGameObject.h"
#include "sbSound.h"

namespace sb
{
	class EndScene : public Scene
	{
	public:
		EndScene();
		virtual ~EndScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;



	private:
		GameObject* mCamera;
		Sound* mSound;
	};
}
