#include "lbEngine.h"
#include "lbEnterPoint.h"
#include "ExampleLayer.h"

class SandboxApp : public Lambix::lbApplication
{
 public:
	SandboxApp(){
		PushLayer(new ExampleLayer());
	}
	~SandboxApp() override = default;
};

Lambix::lbApplication* Lambix::CreateApplication()
{
	return new SandboxApp();
}
