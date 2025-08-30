#include "behaviortree_cpp/bt_factory.h"
#include "ScreenCheck.h"
#include "MoveMouse.h"
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace BT;

// // clang-format off
// static const char* xml_text = R"(
//  <?xml version="1.0" encoding="UTF-8"?>
// <root BTCPP_format="4">
//   <BehaviorTree ID="Untitled">
//     <Sequence>
//       <ScreenCheck message="this works too"/>
//       <ThinkWhatToSay text="{the_answer}"/>
//       <ScreenCheck message="{the_answer}"/>
//     </Sequence>
//   </BehaviorTree>
//
//   <!-- Description of Node Models (used by Groot) -->
//   <TreeNodesModel>
//     <Action ID="ScreenCheck"
//             editable="true">
//       <input_port name="message"/>
//     </Action>
//     <Action ID="ThinkWhatToSay"
//             editable="true">
//       <output_port name="text"
//                    default="the_answer"/>
//     </Action>
//   </TreeNodesModel>
//
// </root>
//  )";
// clang-format on

// 声明变量
static const char* xml_text;
static std::string xml_content; // 用于存储XML内容，确保生命周期

// 从文件读取XML内容
void loadXmlFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("无法打开XML文件: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // 读取整个文件内容
    xml_content = buffer.str();
    xml_text = xml_content.c_str(); // 赋值给const char*变量
}

class SaySomething : public BT::SyncActionNode
{
public:
    SaySomething(const std::string& name, const BT::NodeConfig& config) :
          BT::SyncActionNode(name, config)
    {}

    BT::NodeStatus tick() override {
        std::string msg;
        getInput("message", msg);
        std::cout << msg << std::endl;
        return BT::NodeStatus::SUCCESS;

    }

    static BT::PortsList providedPorts() {
        return {BT::InputPort<std::string>("message")};
    }
};

class ThinkWhatToSay : public BT::SyncActionNode
{
public:
    ThinkWhatToSay(const std::string& name, const BT::NodeConfig& config) :
          BT::SyncActionNode(name, config)
    {}

    BT::NodeStatus tick() override
    {
        setOutput("text", "The answer is 42");
        return BT::NodeStatus::SUCCESS;
    }

    static BT::PortsList providedPorts()
    {
        return {BT::OutputPort<std::string>("text")};
    }
};

int main()
{
    try {
        loadXmlFromFile("C:\\Users\\17203\\Desktop\\test.xml");
        // 现在xml_text已经包含了XML文件的内容，可以像以前一样使用
        // 例如:
        // createTreeFromText(xml_text);
    }
    catch (const std::exception& e) {
        // 处理错误
        std::cout << e.what() << std::endl;
        return 1;
    }
    BehaviorTreeFactory factory;
    factory.registerNodeType<SaySomething>("SaySomething");
    factory.registerNodeType<ScreenCheck>("ScreenCheck");
    factory.registerNodeType<MoveMouse>("MoveMouse");
    factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

    auto tree = factory.createTreeFromText(xml_text);
    while (1) {
        tree.tickWhileRunning();
    }


    return 0;
}
