/**
 ***************************************************************
 * @file            : lbLayerStack.cpp
 * @author          : Lambert
 * @brief           : None
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#include "Core/lbLayerStack.h"

namespace Lambix
{
	
	lbLayerStack::lbLayerStack()
	{
	}

	lbLayerStack::~lbLayerStack()
	{
		for (lbLayer* layer : m_Layers)
			delete layer;
	}

	void lbLayerStack::PushLayer(lbLayer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void lbLayerStack::PushOverlay(lbLayer* overlay)
	{
		m_Layers.emplace_back(overlay);
	}

	void lbLayerStack::PopLayer(lbLayer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void lbLayerStack::PopOverlay(lbLayer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
	
} // Lambix