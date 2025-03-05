/**
 ***************************************************************
 * @file            : lbcore.h
 * @author          : Lambert
 * @brief           : 提供给外部的头文件
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#pragma once

// --Core
// ----Base
#include "Core/Base/lbLog.h"
#include "Core/Base/lbApplication.h"
#include "Core/Base/lbInput.h"
#include "Core/Base/lbLayer.h"
#include "Core/Base/lbTimestep.h"
// ----Renderer
#include "Core/Renderer/lbRendererCommand.h"
#include "Core/Renderer/lbBuffer.h"
#include "Core/Renderer/lbVertexArray.h"
#include "Core/Renderer/lbShader.h"
#include "Core/Renderer/lbTexture.h"
#include "Core/Renderer/lbFrameBuffer.h"
// ------Material
#include "Core/Renderer/Material/lbMaterial.h"
#include "Core/Renderer/Material/lbBasicMaterial.h"
// ------Geometry
#include "Core/Renderer/Geometry/lbGeometry.h"
#include "Core/Renderer/Geometry/lbCubeGeometry.h"

// ----Events
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

// ----ECS
#include "Core/ECS/lbScene.h"
#include "Core/ECS/lbEntity.h"
#include "Core/ECS/Components/lbBasicComponents.h"
#include "Core/ECS/Components/lbTransformComponent.h"
#include "Core/ECS/Components/lbMeshRendererComponent.h"

// ----UI
#include "Core/UI/lbLogUI.h"

// ----Utils
#include "Core/Utils/lbFileUtils.h"
