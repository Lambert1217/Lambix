#include "lbEngine.h"
#include "lbEnterPoint.h"
#include "EditorLayer.h"

class LambixEditorApp : public Lambix::lbApplication
{
public:
	LambixEditorApp(const Lambix::lbAppSettings &settings) : Lambix::lbApplication(settings)
	{
		PushLayer(new EditorLayer());
	}
	~LambixEditorApp() override = default;
};

Lambix::lbApplication *Lambix::CreateApplication()
{
	Lambix::lbAppSettings appSettings;
	appSettings.WindowTitle = "Lambix Engine Editor";
	return new LambixEditorApp(appSettings);
}
