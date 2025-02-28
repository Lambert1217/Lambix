#include "lbEngine.h"
#include "lbEnterPoint.h"
#include "lbEditorLayer.h"

namespace Lambix
{
	class lbEditorApp : public lbApplication
	{
	public:
		lbEditorApp(const lbAppSettings &settings) : lbApplication(settings)
		{
			PushLayer(new lbEditorLayer());
		}
		~lbEditorApp() override = default;
	};

	lbApplication *CreateApplication()
	{
		lbAppSettings appSettings;
		{
			appSettings.WindowWidth = 1920;
			appSettings.WindowHeight = 1080;
			appSettings.WindowTitle = "Lambix Engine Editor";
		}
		return new lbEditorApp(appSettings);
	}
}