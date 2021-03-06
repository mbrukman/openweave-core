/*
 *
 *    Copyright (c) 2018 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *          Provides an generic implementation of PlatformManager features
 *          for use on various platforms.
 */

#ifndef GENERIC_PLATFORM_MANAGER_IMPL_H
#define GENERIC_PLATFORM_MANAGER_IMPL_H

namespace nl {
namespace Weave {
namespace DeviceLayer {
namespace Internal {

/**
 * Provides a generic implementation of PlatformManager features that works on multiple platforms.
 *
 * This template contains implementations of select features from the PlatformManager abstract
 * interface that are suitable for use on all platforms.  It is intended to be inherited (directly
 * or indirectly) by the PlatformManagerImpl class, which also appears as the template's ImplClass
 * parameter.
 */
template<class ImplClass>
class GenericPlatformManagerImpl
{
protected:

    struct AppEventHandler
    {
        AppEventHandler * Next;
        PlatformManager::EventHandlerFunct Handler;
        intptr_t Arg;
    };

    AppEventHandler * mAppEventHandlerList;

    // ===== Methods that implement the PlatformManager abstract interface.

    WEAVE_ERROR _InitWeaveStack();
    WEAVE_ERROR _AddEventHandler(PlatformManager::EventHandlerFunct handler, intptr_t arg);
    void _RemoveEventHandler(PlatformManager::EventHandlerFunct handler, intptr_t arg);
    void _ScheduleWork(AsyncWorkFunct workFunct, intptr_t arg);
    void _DispatchEvent(const WeaveDeviceEvent * event);

    // ===== Support methods that can be overridden by the implementation subclass.

    void DispatchEventToSystemLayer(const WeaveDeviceEvent * event);
    void DispatchEventToDeviceLayer(const WeaveDeviceEvent * event);
    void DispatchEventToApplication(const WeaveDeviceEvent * event);
    static void HandleSessionEstablished(WeaveSecurityManager * sm, WeaveConnection * con,
            void * reqState, uint16_t sessionKeyId, uint64_t peerNodeId, uint8_t encType);

private:
    ImplClass * Impl() { return static_cast<ImplClass*>(this); }
};

} // namespace Internal
} // namespace DeviceLayer
} // namespace Weave
} // namespace nl

#endif // GENERIC_PLATFORM_MANAGER_IMPL_H
