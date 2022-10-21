#pragma once

#include <aspire/Bitmask.h>
#include <aspire/export.hxx>
#include <chrono>
#include <variant>

namespace aspire
{
	/// @brief This class defines a collection of common data shared between event types.
	struct EventBase
	{
		/// @brief Defines the point in time that this event occured.
		std::chrono::steady_clock::time_point timestamp{std::chrono::steady_clock::now()};

		/// @brief Defines whether this event has been previous handled by a Node.
		bool handled{false};
	};

	/// @brief This class defines a collection of keyboard state that represents an event at a given point in time.
	struct EventKeyboard : EventBase
	{
		enum class Type : int
		{
			Unknown,
			Pressed,
			Released
		};

		enum class Key : int
		{
			Unknown,
			Space,
			Num0,
			Num1,
			Num2,
			Num3,
			Num4,
			Num5,
			Num6,
			Num7,
			Num8,
			Num9,
			A,
			B,
			C,
			D,
			E,
			F,
			G,
			H,
			I,
			J,
			K,
			L,
			M,
			N,
			O,
			P,
			Q,
			R,
			S,
			T,
			U,
			V,
			W,
			X,
			Y,
			Z,
			Exclaim,
			Quotedbl,
			Hash,
			Dollar,
			Ampersand,
			Quote,
			Leftparen,
			Rightparen,
			Asterisk,
			Plus,
			Comma,
			Minus,
			Period,
			Slash,
			Colon,
			Semicolon,
			Less,
			Equals,
			Greater,
			Question,
			At,
			Leftbracket,
			Backslash,
			Rightbracket,
			Caret,
			Underscore,
			Backquote,
			BackSpace,
			Tab,
			Linefeed,
			Clear,
			Return,
			Pause,
			Scroll_Lock,
			Sys_Req,
			Escape,
			Delete,
			Home,
			Left,
			Up,
			Right,
			Down,
			Prior,
			Page_Up,
			Next,
			Page_Down,
			End,
			Begin,
			Select,
			Print,
			Execute,
			Insert,
			Undo,
			Redo,
			Menu,
			Find,
			Cancel,
			Help,
			Break,
			Mode_switch,
			Script_switch,
			Num_Lock,
			KP_Space,
			KP_Tab,
			KP_Enter,
			KP_F1,
			KP_F2,
			KP_F3,
			KP_F4,
			KP_Home,
			KP_Left,
			KP_Up,
			KP_Right,
			KP_Down,
			KP_Prior,
			KP_Page_Up,
			KP_Next,
			KP_Page_Down,
			KP_End,
			KP_Begin,
			KP_Insert,
			KP_Delete,
			KP_Equal,
			KP_Multiply,
			KP_Add,
			KP_Separator,
			KP_Subtract,
			KP_Decimal,
			KP_Divide,
			KP_0,
			KP_1,
			KP_2,
			KP_3,
			KP_4,
			KP_5,
			KP_6,
			KP_7,
			KP_8,
			KP_9,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			F16,
			F17,
			F18,
			F19,
			F20,
			F21,
			F22,
			F23,
			F24,
			F25,
			F26,
			F27,
			F28,
			F29,
			F30,
			F31,
			F32,
			F33,
			F34,
			F35,
			Shift_L,
			Shift_R,
			Control_L,
			Control_R,
			Caps_Lock,
			Shift_Lock,
			Meta_L,
			Meta_R,
			Alt_L,
			Alt_R,
			Super_L,
			Super_R,
			Hyper_L,
			Hyper_R
		};

		enum class Modifier : uint8_t
		{
			ShiftL = 0b00000001,
			ShiftR = 0b00000010,
			ControlL = 0b00000100,
			ControlR = 0b00001000,
			AltL = 0b00010000,
			AltR = 0b000100000,
			SuperL = 0b001000000,
			SuperR = 0b010000000,
			Shift = ShiftL | ShiftR,
			Control = ControlL | ControlR,
			Alt = AltL | AltR,
			Super = SuperL | SuperR
		};

		Type type{Type::Unknown};
		Key key{Key::Unknown};
		Bitmask<Modifier> modifier{};
	};

	/// @brief This class defines a collection of mouse state that represents an event at a given point in time.
	struct EventMouse : EventBase
	{
		enum class Type : int
		{
			Unknown,
			Moved,
			Scrolled,
			Pressed,
			Released,
			Entered
		};

		enum class Button : int
		{
			Unkown,
			Left,
			Right,
			Middle
		};

		enum class Modifier : uint8_t
		{
			ShiftL = 0b00000001,
			ShiftR = 0b00000010,
			ControlL = 0b00000100,
			ControlR = 0b00001000,
			AltL = 0b00010000,
			AltR = 0b000100000,
			SuperL = 0b001000000,
			SuperR = 0b010000000,
			Shift = ShiftL | ShiftR,
			Control = ControlL | ControlR,
			Alt = AltL | AltR,
			Super = SuperL | SuperR
		};

		float x{};
		float y{};
		float scrollX{};
		float scrollY{};
		Type type{Type::Unknown};
		Button button{Button::Unkown};
		Bitmask<Modifier> modifier{};
	};

	/// @brief Helper type for handling arbitrary number of types packed into a variant.
	/// @tparam ...Ts The types packed within a variant.
	template <class... Ts>
	struct overloaded : Ts...
	{
		using Ts::operator()...;
	};

	/// @brief Explicit deduction guide for variant types.
	template <class... Ts>
	overloaded(Ts...) -> overloaded<Ts...>;

	using Event = std::variant<EventKeyboard, EventMouse>;
}
