#pragma once

#include <memory>
#include <unordered_map>
#include <assert.h>
#include <Windows.h>

namespace reshade
{
	class input
	{
	public:
		explicit input(HWND hwnd);
		~input();

		static void register_window(HWND hwnd, std::shared_ptr<input> &instance);
		static void register_raw_input_device(const RAWINPUTDEVICE &device);
		static void uninstall();

		bool is_key_down(UINT keycode) const
		{
			assert(keycode < 255);

			return _keys[keycode] > 0;
		}
		bool is_key_pressed(UINT keycode) const
		{
			assert(keycode < 255);

			return _keys[keycode] == 1;
		}
		bool is_key_released(UINT keycode) const
		{
			assert(keycode < 255);

			return _keys[keycode] == -1;
		}
		bool is_mouse_button_down(UINT button) const
		{
			assert(button < 3);

			return _mouse_buttons[button] > 0;
		}
		bool is_mouse_button_pressed(UINT button) const
		{
			assert(button < 3);

			return _mouse_buttons[button] == 1;
		}
		bool is_mouse_button_released(UINT button) const
		{
			assert(button < 3);

			return _mouse_buttons[button] == -1;
		}
		const POINT &mouse_position() const
		{
			return _mouse_position;
		}

		void next_frame();

	private:
		static LRESULT CALLBACK handle_window_message(int nCode, WPARAM wParam, LPARAM lParam);

		HWND _hwnd;
		HHOOK _hook_wndproc;
		signed char _keys[256], _mouse_buttons[3];
		POINT _mouse_position;
		static std::unordered_map<HWND, HHOOK> s_raw_input_hooks;
		static std::unordered_map<HWND, std::weak_ptr<input>> s_windows;
	};
}