//
// Created by 17203 on 2025/9/1.
//

#include "../include/CreateStage.h"

#include <pxr/usd/usd/stage.h>
#include <pxr/usd/usd/prim.h>
#include <pxr/base/tf/token.h>
#include <string>
#include <pxr/usd/sdf/path.h>


CreateStage::CreateStage(const std::string &name, const NodeConfig &config):
    SyncActionNode(name, config)
{

}

NodeStatus CreateStage::tick() {
    std::string filePath;
    getInput("filePath", filePath);
    std::cout << "filePath: " << filePath << std::endl;

    pxr::UsdStageRefPtr stage = pxr::UsdStage::CreateNew(filePath);
    auto xform = stage->DefinePrim(pxr::SdfPath("/hello"), pxr::TfToken("Xform"));
    auto sphere = stage->DefinePrim(pxr::SdfPath("/hello/world"), pxr::TfToken("Sphere"));
    stage->GetRootLayer()->Save();

    return NodeStatus::SUCCESS;
}

PortsList CreateStage::providedPorts() {
    return {BT::InputPort<std::string>("filePath")};
}
