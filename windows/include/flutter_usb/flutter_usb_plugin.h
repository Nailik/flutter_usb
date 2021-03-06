#ifndef FLUTTER_PLUGIN_FLUTTER_USB_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_USB_PLUGIN_H_

#include <flutter_plugin_registrar.h>
#include <wia_xp.h>
#include <list>
#include "../../../../../../../../build/windows/plugins/flutter_usb/command.h"
#include "../../../../../../../../build/windows/plugins/flutter_usb/usbdevice.h"
#include "../../../../../../../../build/windows/plugins/flutter_usb/response.h"

#ifdef FLUTTER_PLUGIN_IMPL
#define FLUTTER_PLUGIN_EXPORT __declspec(dllexport)
#else
#define FLUTTER_PLUGIN_EXPORT __declspec(dllimport)
#endif

#if defined(__cplusplus)
extern "C" {
#endif
HRESULT CreateWiaDeviceManager(IWiaDevMgr** ppWiaDevMgr);
HRESULT EnumerateWiaDevices(IWiaDevMgr* pWiaDevMgr, std::list<USBDevice>* mylist);
HRESULT CreateWiaDevice(IWiaDevMgr* pWiaDevMgr, BSTR bstrDeviceID, IWiaItem** ppWiaDevice);
HRESULT EnumerateItems(IWiaItem* pWiaItem);
void initialize(IWiaDevMgr** pWiaDevMgr);
void getDevices(IWiaDevMgr* pWiaDevMgr, std::list<USBDevice>* mylist);
Response sendCommand(Command command);
bool connectToDevice(IWiaDevMgr* pWiaDevMgr, BSTR bstrDeviceID, IWiaItem* ppWiaDevice);

FLUTTER_PLUGIN_EXPORT void FlutterUsbPluginRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar);

#if defined(__cplusplus)
}  // extern "C"
#endif

#endif  // FLUTTER_PLUGIN_FLUTTER_USB_PLUGIN_H_
