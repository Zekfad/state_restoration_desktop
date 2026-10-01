#include "state_restoration_desktop_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>
#include <fstream>

namespace state_restoration_desktop {

	static constexpr char kRestorationChannelName[] = "flutter/restoration";
	static constexpr char kGetMethod[] = "get";
	static constexpr char kPutMethod[] = "put";
	static constexpr char kPushMethod[] = "push";
	static constexpr char kBadArgumentError[] = "Bad Arguments";

	// static
	void StateRestorationDesktopPlugin::RegisterWithRegistrar(flutter::PluginRegistrarWindows* registrar) {
		auto channel = std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
			registrar->messenger(), kRestorationChannelName,
			&flutter::StandardMethodCodec::GetInstance()
		);

		auto plugin = std::make_unique<StateRestorationDesktopPlugin>();

		channel->SetMethodCallHandler(
			[plugin_pointer = plugin.get()](const auto& call, auto result) {
				plugin_pointer->HandleMethodCall(call, std::move(result));
			}
		);

		registrar->AddPlugin(std::move(plugin));
	}

	StateRestorationDesktopPlugin::StateRestorationDesktopPlugin() {}

	StateRestorationDesktopPlugin::~StateRestorationDesktopPlugin() {}

	void StateRestorationDesktopPlugin::HandleMethodCall(
		const flutter::MethodCall<flutter::EncodableValue>& method_call,
		std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result
	) {
		auto& method = method_call.method_name();
		if (method.compare(kGetMethod) == 0) {
			// GET DATA
			flutter::EncodableMap response = {
				{ flutter::EncodableValue("enabled"), flutter::EncodableValue(true), },
			};
			auto buffer = read_vector("restoration.bin");
			if (!buffer.empty()) {
				response[flutter::EncodableValue("data")] = flutter::EncodableValue(buffer);
			}
			result->Success(flutter::EncodableValue(response));
			return;
		}
		else if (method.compare(kPutMethod) == 0) {
			// SET DATA
			if (!method_call.arguments() || method_call.arguments()->IsNull()) {
				result->Error(kBadArgumentError, "Method invoked without args");
				return;
			}
			const auto* data = std::get_if<std::vector<uint8_t>>(method_call.arguments());
			if (!data) {
				result->Error(kBadArgumentError, "Method put expected a Uint8List");
				return;
			}
			save_vector("restoration.bin", *data);
			result->Success();
		}
		else {
			result->NotImplemented();
		}
	}

	void StateRestorationDesktopPlugin::save_vector(const std::string& filename, const std::vector<uint8_t>& vec) {
		std::ofstream file(filename, std::ios::binary);

		if (!file) return;

		file.write(reinterpret_cast<const char*>(vec.data()), vec.size());
	}

	std::vector<uint8_t> StateRestorationDesktopPlugin::read_vector(const std::string& filename) {
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		if (!file) return {};

		// Get file size using the read pointer at the end
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8_t> vec(size);
		if (file.read(reinterpret_cast<char*>(vec.data()), size)) {
			return vec;
		}

		return {};
	}

}  // namespace state_restoration_desktop
