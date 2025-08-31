//
// Created by 17203 on 2025/9/1.
//

#ifndef BEHAVIORTREE_CREATESTAGE_H
#define BEHAVIORTREE_CREATESTAGE_H

#include "behaviortree_cpp/bt_factory.h"
using namespace BT;


class CreateStage :public SyncActionNode{

public:
    CreateStage(const std::string& name, const NodeConfig& config);

    NodeStatus tick() override;

    static PortsList providedPorts();
};


#endif //BEHAVIORTREE_CREATESTAGE_H