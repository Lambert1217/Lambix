/**
 ***************************************************************
 * @file            : ExampleLayer.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#include "ExampleLayer.h"

ExampleLayer::ExampleLayer(): Lambix::lbLayer("Example")
{
}
void ExampleLayer::OnAttach()
{
	LOG_INFO("{0} -> OnAttach", this->GetName());
}
void ExampleLayer::OnDetach()
{
	LOG_INFO("{0} -> OnDetach", this->GetName());
}
void ExampleLayer::OnUpdate(Lambix::lbTimestep ts)
{
	//LOG_INFO("{0} -> OnUpdate: {1}s", this->GetName(), (float)ts);
}
void ExampleLayer::OnEvent(Lambix::Event& event)
{
	//LOG_INFO(event.ToString());
}
