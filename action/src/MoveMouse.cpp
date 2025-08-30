//
// Created by 17203 on 2025/8/30.
//
#include <thread>
#include <chrono>
#include <Windows.h>
#include <algorithm>  // 新增：包含std::max所需的头文件
#include "../include/MoveMouse.h"


MoveMouse::MoveMouse(const std::string &name, const NodeConfig &config):
    SyncActionNode(name, config)
{

}

NodeStatus MoveMouse::tick() {
    // 1. 获取当前鼠标位置
    POINT current_pos;
    GetCursorPos(&current_pos);

    // 2. 计算目标位置（向上移动100像素，确保Y坐标不小于0）
    int target_x = current_pos.x;
    int target_y = std::max<int>(0, static_cast<int>(current_pos.y) - 100);

    // 3. 平滑移动（分20步，每步5像素，总耗时200ms）
    const int steps = 20;
    int step_x = (target_x - current_pos.x) / steps;
    int step_y = (target_y - current_pos.y) / steps;

    for (int i = 1; i <= steps; ++i) {
        int x = current_pos.x + step_x * i;
        int y = current_pos.y + step_y * i;
        SetCursorPos(x, y);  // 移动到中间位置
        // std::cout << "mouse move pos:" << "x: " << x << " y: " << y << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // 每步间隔10ms
    }

    // 4. 最终校准到精确位置
    SetCursorPos(target_x, target_y);

        return NodeStatus::SUCCESS;
}

PortsList MoveMouse::providedPorts() {
    return {BT::InputPort<std::string>("message")};
}
