#include "lbEngine.h"
#include "lbEnterPoint.h"

class SandboxApp : public Lambix::lbApplication
{
 public:
	SandboxApp(){};
	virtual ~SandboxApp() = default;
};

Lambix::lbApplication* Lambix::CreateApplication()
{
	return new SandboxApp();
}
