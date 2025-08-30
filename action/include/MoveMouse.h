//
// Created by 17203 on 2025/8/30.
//

#ifndef BEHAVIORTREE_MOVEMOUSE_H
#define BEHAVIORTREE_MOVEMOUSE_H

#include "behaviortree_cpp/bt_factory.h"

using namespace BT;

class MoveMouse :public SyncActionNode{

public:
    MoveMouse(const std::string& name, const NodeConfig& config);

    NodeStatus tick() override;

    static PortsList providedPorts();
};


#endif //BEHAVIORTREE_MOVEMOUSE_H
