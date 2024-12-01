/**
 * @file EditorLayer.h
 * @author Lambert1217 (1904310303@qq.com)
 * @brief 编辑器图层
 * @date 2024-12-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "lbEngine.h"

class EditorLayer : public Lambix::lbLayer
{
public:
	EditorLayer();
	~EditorLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(Lambix::lbTimestep ts) override;
	virtual void OnEvent(Lambix::Event &event) override;
	virtual void OnImGuiRender() override;

private:
	std::shared_ptr<Lambix::lbFrameBuffer> m_FrameBuffer;
};
