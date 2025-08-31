//
// Created by 17203 on 2025/8/30.
//

#ifndef BEHAVIORTREE_SCREENCHECK_H
#define BEHAVIORTREE_SCREENCHECK_H
#include "behaviortree_cpp/bt_factory.h"

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <iostream>

using namespace BT;


class ScreenCheck : public SyncActionNode{

public:
    ScreenCheck(const std::string& name, const NodeConfig& config);

    NodeStatus tick() override;

    static PortsList providedPorts();
private:
    // 保存黑板指针供类内使用
    Blackboard::Ptr bb_;
};



#endif //BEHAVIORTREE_SCREENCHECK_H