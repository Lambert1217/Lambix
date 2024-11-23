/**
 ***************************************************************
 * @file            : lbImguiLayer.h
 * @author          : Lambert
 * @brief           : imgui实现 ui 层
 * @attention       : None
 * @data            : 2024/11/23
 ***************************************************************
 */
//

#pragma once

#include "Core/lbLayer.h"

namespace Lambix
{

	class lbImguiLayer : public lbLayer
	{
	 public:
		lbImguiLayer();
		~lbImguiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	};

} // Lambix
