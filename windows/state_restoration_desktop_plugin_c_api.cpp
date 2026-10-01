#include "include/state_restoration_desktop/state_restoration_desktop_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "state_restoration_desktop_plugin.h"

void StateRestorationDesktopPluginCApiRegisterWithRegistrar(
	FlutterDesktopPluginRegistrarRef registrar) {
	state_restoration_desktop::StateRestorationDesktopPlugin::RegisterWithRegistrar(
		flutter::PluginRegistrarManager::GetInstance()
		->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
