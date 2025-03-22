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
#include "Renderer/lbGeometry.h"
#include "Renderer/lbAttribute.h"
// ----Interfaces
#include "Renderer/Interfaces/lbBuffer.h"
#include "Renderer/Interfaces/lbVertexArray.h"
#include "Renderer/Interfaces/lbShader.h"
#include "Renderer/Interfaces/lbTexture.h"
#include "Renderer/Interfaces/lbFrameBuffer.h"
// ----Material
#include "Renderer/Material/lbMaterial.h"
#include "Renderer/Material/lbBasicMaterial.h"
// ----Light
#include "Renderer/Light/lbLight.h"

// --Events
#include "Events/lbEvent.h"
#include "Events/lbEventPool.h"

// --ECS
#include "ECS/lbScene.h"
#include "ECS/lbEntity.h"
// ----Components
#include "ECS/Components/lbBasicComponents.h"
#include "ECS/Components/lbTransformComponent.h"
#include "ECS/Components/lbMeshRendererComponent.h"
#include "ECS/Components/lbLightComponent.h"
// ----System
#include "ECS/System/lbCameraSystem.h"
#include "ECS/System/lbLightSystem.h"
#include "ECS/System/lbTransformSystem.h"
#include "ECS/System/lbRendererSystem.h"

// --Utils
#include "Utils/lbFileUtils.h"
#include "Utils/lbTimer.h"
#include "Utils/lbTimestep.h"

// --Resource
#include "Resource/lbCache.h"
#include "Resource/lbTextureLoader.h"
#include "Resource/lbModelLoader.h"
