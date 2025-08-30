//
// Created by 17203 on 2025/8/30.
//

// bt_export.h
#pragma once

// 跨平台动态库导出/导入宏：解决 Windows/Linux/macOS 下的符号导出问题
#ifdef _WIN32
    // Windows 平台逻辑：
    // - 编译动态库（DLL）时，定义 BT_PLUGIN_EXPORTS，宏会解析为 dllexport（导出符号）
    // - 使用动态库时，不定义 BT_PLUGIN_EXPORTS，宏会解析为 dllimport（导入符号）
    #ifdef BT_PLUGIN_EXPORTS
        #define BT_PLUGIN_API __declspec(dllexport)
    #else
        #define BT_PLUGIN_API __declspec(dllimport)
    #endif
#else
    // Linux/macOS 平台逻辑：
    // - 通过 visibility("default") 让符号可见（相当于 Windows 的 dllexport）
    #define BT_PLUGIN_API __attribute__((visibility("default")))
#endif