#ifndef FLUTTER_PLUGIN_STATE_RESTORATION_DESKTOP_PLUGIN_H_
#define FLUTTER_PLUGIN_STATE_RESTORATION_DESKTOP_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace state_restoration_desktop {

	class StateRestorationDesktopPlugin : public flutter::Plugin {
	public:
		static void RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar);

		StateRestorationDesktopPlugin();

		virtual ~StateRestorationDesktopPlugin();

		// Disallow copy and assign.
		StateRestorationDesktopPlugin(const StateRestorationDesktopPlugin&) = delete;
		StateRestorationDesktopPlugin& operator=(const StateRestorationDesktopPlugin&) = delete;

		// Called when a method is called on this plugin's channel from Dart.
		void HandleMethodCall(
			const flutter::MethodCall<flutter::EncodableValue>& method_call,
			std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
	private:
		static void save_vector(const std::string& filename, const std::vector<uint8_t>& vec);

		static std::vector<uint8_t> read_vector(const std::string& filename);
	};

}  // namespace state_restoration_desktop

#endif  // FLUTTER_PLUGIN_STATE_RESTORATION_DESKTOP_PLUGIN_H_
