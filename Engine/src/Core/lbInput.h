/**
 ***************************************************************
 * @file            : lbInput.h
 * @author          : Lambert
 * @brief           : 处理输入
 * @attention       : None
 * @data            : 2024/8/21
 ***************************************************************
 */
//

#pragma once

namespace Lambix
{

	class lbInput
	{
	 public:
		lbInput() = default;
		lbInput(const lbInput&) = delete;
		lbInput &operator=(const lbInput&) = delete;
		~lbInput() = default;

		/**
		 * @brief 查询键盘 keycode 是否按下
		 * @param keycode
		 * @return
		 */
		inline static bool IsKeyPressed(int keycode) { return s_lbInput->IsKeyPressedHelp(keycode); }

		/**
		 * @brief 查询鼠标 button 是否点击
		 * @param button
		 * @return
		 */
		inline static bool IsMouseButtonPressed(int button) { return s_lbInput->IsMouseButtonPressedHelp(button); }

		/**
		 * @brief 返回鼠标位置
		 * @return
		 */
		inline static std::pair<float, float> GetMousePosition() { return s_lbInput->GetMousePositionHelp(); }

		/**
		 * @brief 返回鼠标位置 x
		 * @return
		 */
		inline static float GetMouseX() { return s_lbInput->GetMouseXHelp(); }

		/**
		 * @brief 返回鼠标位置 y
		 * @return
		 */
		inline static float GetMouseY() { return s_lbInput->GetMouseYHelp(); }
	 protected:
		virtual bool IsKeyPressedHelp(int keycode) = 0;
		virtual bool IsMouseButtonPressedHelp(int button) = 0;
		virtual std::pair<float, float> GetMousePositionHelp() = 0;
		virtual float GetMouseXHelp() = 0;
		virtual float GetMouseYHelp() = 0;
	 private:
		static lbInput* s_lbInput;
	};

} // Lambix

#if LAMBIX_OS_WINDOWS | LAMBIX_OS_APPLE | LAMBIX_OS_LINUX

// 鼠标键值
#define LB_MOUSE_BUTTON_1         0
#define LB_MOUSE_BUTTON_2         1
#define LB_MOUSE_BUTTON_3         2
#define LB_MOUSE_BUTTON_4         3
#define LB_MOUSE_BUTTON_5         4
#define LB_MOUSE_BUTTON_6         5
#define LB_MOUSE_BUTTON_7         6
#define LB_MOUSE_BUTTON_8         7
#define LB_MOUSE_BUTTON_LAST      GLFW_MOUSE_BUTTON_8
#define LB_MOUSE_BUTTON_LEFT      GLFW_MOUSE_BUTTON_1
#define LB_MOUSE_BUTTON_RIGHT     GLFW_MOUSE_BUTTON_2
#define LB_MOUSE_BUTTON_MIDDLE    GLFW_MOUSE_BUTTON_3

// 键盘键值 (源自glfw3.h)
#define LB_KEY_SPACE              32
#define LB_KEY_APOSTROPHE         39  /* ' */
#define LB_KEY_COMMA              44  /* , */
#define LB_KEY_MINUS              45  /* - */
#define LB_KEY_PERIOD             46  /* . */
#define LB_KEY_SLASH              47  /* / */
#define LB_KEY_0                  48
#define LB_KEY_1                  49
#define LB_KEY_2                  50
#define LB_KEY_3                  51
#define LB_KEY_4                  52
#define LB_KEY_5                  53
#define LB_KEY_6                  54
#define LB_KEY_7                  55
#define LB_KEY_8                  56
#define LB_KEY_9                  57
#define LB_KEY_SEMICOLON          59  /* ; */
#define LB_KEY_EQUAL              61  /* = */
#define LB_KEY_A                  65
#define LB_KEY_B                  66
#define LB_KEY_C                  67
#define LB_KEY_D                  68
#define LB_KEY_E                  69
#define LB_KEY_F                  70
#define LB_KEY_G                  71
#define LB_KEY_H                  72
#define LB_KEY_I                  73
#define LB_KEY_J                  74
#define LB_KEY_K                  75
#define LB_KEY_L                  76
#define LB_KEY_M                  77
#define LB_KEY_N                  78
#define LB_KEY_O                  79
#define LB_KEY_P                  80
#define LB_KEY_Q                  81
#define LB_KEY_R                  82
#define LB_KEY_S                  83
#define LB_KEY_T                  84
#define LB_KEY_U                  85
#define LB_KEY_V                  86
#define LB_KEY_W                  87
#define LB_KEY_X                  88
#define LB_KEY_Y                  89
#define LB_KEY_Z                  90
#define LB_KEY_LEFT_BRACKET       91  /* [ */
#define LB_KEY_BACKSLASH          92  /* \ */
#define LB_KEY_RIGHT_BRACKET      93  /* ] */
#define LB_KEY_GRAVE_ACCENT       96  /* ` */
#define LB_KEY_WORLD_1            161 /* non-US #1 */
#define LB_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define LB_KEY_ESCAPE             256
#define LB_KEY_ENTER              257
#define LB_KEY_TAB                258
#define LB_KEY_BACKSPACE          259
#define LB_KEY_INSERT             260
#define LB_KEY_DELETE             261
#define LB_KEY_RIGHT              262
#define LB_KEY_LEFT               263
#define LB_KEY_DOWN               264
#define LB_KEY_UP                 265
#define LB_KEY_PAGE_UP            266
#define LB_KEY_PAGE_DOWN          267
#define LB_KEY_HOME               268
#define LB_KEY_END                269
#define LB_KEY_CAPS_LOCK          280
#define LB_KEY_SCROLL_LOCK        281
#define LB_KEY_NUM_LOCK           282
#define LB_KEY_PRINT_SCREEN       283
#define LB_KEY_PAUSE              284
#define LB_KEY_F1                 290
#define LB_KEY_F2                 291
#define LB_KEY_F3                 292
#define LB_KEY_F4                 293
#define LB_KEY_F5                 294
#define LB_KEY_F6                 295
#define LB_KEY_F7                 296
#define LB_KEY_F8                 297
#define LB_KEY_F9                 298
#define LB_KEY_F10                299
#define LB_KEY_F11                300
#define LB_KEY_F12                301
#define LB_KEY_F13                302
#define LB_KEY_F14                303
#define LB_KEY_F15                304
#define LB_KEY_F16                305
#define LB_KEY_F17                306
#define LB_KEY_F18                307
#define LB_KEY_F19                308
#define LB_KEY_F20                309
#define LB_KEY_F21                310
#define LB_KEY_F22                311
#define LB_KEY_F23                312
#define LB_KEY_F24                313
#define LB_KEY_F25                314
#define LB_KEY_KP_0               320
#define LB_KEY_KP_1               321
#define LB_KEY_KP_2               322
#define LB_KEY_KP_3               323
#define LB_KEY_KP_4               324
#define LB_KEY_KP_5               325
#define LB_KEY_KP_6               326
#define LB_KEY_KP_7               327
#define LB_KEY_KP_8               328
#define LB_KEY_KP_9               329
#define LB_KEY_KP_DECIMAL         330
#define LB_KEY_KP_DIVIDE          331
#define LB_KEY_KP_MULTIPLY        332
#define LB_KEY_KP_SUBTRACT        333
#define LB_KEY_KP_ADD             334
#define LB_KEY_KP_ENTER           335
#define LB_KEY_KP_EQUAL           336
#define LB_KEY_LEFT_SHIFT         340
#define LB_KEY_LEFT_CONTROL       341
#define LB_KEY_LEFT_ALT           342
#define LB_KEY_LEFT_SUPER         343
#define LB_KEY_RIGHT_SHIFT        344
#define LB_KEY_RIGHT_CONTROL      345
#define LB_KEY_RIGHT_ALT          346
#define LB_KEY_RIGHT_SUPER        347
#define LB_KEY_MENU               348

#endif