#include "lbEngine.h"
#include "lbEnterPoint.h"
#include "EditorLayer.h"

class LambixEditorApp : public Lambix::lbApplication
{
public:
	LambixEditorApp()
	{
		PushLayer(new EditorLayer());
	}
	~LambixEditorApp() override = default;
};

Lambix::lbApplication *Lambix::CreateApplication()
{
	return new LambixEditorApp();
}
