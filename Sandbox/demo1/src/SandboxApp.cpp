#include "lbEngine.h"
#include "lbEnterPoint.h"
#include "ExampleLayer.h"

class SandboxApp : public Lambix::lbApplication
{
 public:
	 SandboxApp(const Lambix::lbAppSettings &settings) : Lambix::lbApplication(settings)
	 {
		 PushLayer(new ExampleLayer());
	 }
	~SandboxApp() override = default;
};

Lambix::lbApplication* Lambix::CreateApplication()
{
	Lambix::lbAppSettings appSettings;
	appSettings.WindowTitle = "Demo1";
	return new SandboxApp(appSettings);
}
