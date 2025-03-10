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
#include "Log/lbLog.h"
#include "Core/lbApplication.h"
#include "Core/lbInput.h"
#include "Core/lbLayer.h"

// --Renderer
#include "Renderer/lbRendererCommand.h"
#include "Renderer/lbBuffer.h"
#include "Renderer/lbVertexArray.h"
#include "Renderer/lbShader.h"
#include "Renderer/lbTexture.h"
#include "Renderer/lbFrameBuffer.h"
// ----Material
#include "Renderer/Material/lbMaterial.h"
#include "Renderer/Material/lbBasicMaterial.h"
// ----Geometry
#include "Renderer/Geometry/lbGeometry.h"
#include "Renderer/Geometry/lbCubeGeometry.h"

// --Events
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

// --ECS
#include "ECS/lbScene.h"
#include "ECS/lbEntity.h"
#include "ECS/Components/lbBasicComponents.h"
#include "ECS/Components/lbTransformComponent.h"
#include "ECS/Components/lbMeshRendererComponent.h"
#include "ECS/Components/lbLightComponent.h"

// --UI
#include "Imgui/lbLogUI.h"
#include "Utils/lbTimestep.h"

// --Utils
#include "Utils/lbFileUtils.h"

// --Resource
#include "Resource/lbResourceManager.h"
