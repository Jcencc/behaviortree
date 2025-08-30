//
// Created by 17203 on 2025/8/30.
//

#include "../include/ScreenCheck.h"
using namespace cv;
using namespace std;

// 捕获屏幕图像并转换为OpenCV的Mat格式
Mat captureScreen() {
    // 获取屏幕尺寸
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // 创建屏幕DC
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);

    // 创建位图
    HBITMAP hbmScreen = CreateCompatibleBitmap(hdcScreen, screenWidth, screenHeight);
    SelectObject(hdcMem, hbmScreen);

    // 复制屏幕内容到位图
    BitBlt(hdcMem, 0, 0, screenWidth, screenHeight, hdcScreen, 0, 0, SRCCOPY);

    // 获取位图信息
    BITMAPINFOHEADER bmih;
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biWidth = screenWidth;
    bmih.biHeight = -screenHeight;  // 负数表示_top-down图像
    bmih.biPlanes = 1;
    bmih.biBitCount = 24;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = 0;
    bmih.biXPelsPerMeter = 0;
    bmih.biYPelsPerMeter = 0;
    bmih.biClrUsed = 0;
    bmih.biClrImportant = 0;

    // 分配内存并获取位图数据
    Mat screenMat(screenHeight, screenWidth, CV_8UC3);
    GetDIBits(hdcMem, hbmScreen, 0, screenHeight, screenMat.data,
             (BITMAPINFO*)&bmih, DIB_RGB_COLORS);

    // 转换颜色空间 (BGR -> RGB)
    cvtColor(screenMat, screenMat, COLOR_BGR2RGB);

    // 释放资源
    DeleteObject(hbmScreen);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);

    return screenMat;
}

// 检测屏幕上是否存在目标图像
bool detectImage(const Mat& screen, const Mat& templateImg, double threshold = 0.8, Rect* outRect = nullptr) {
    if (templateImg.empty() || screen.empty()) {
        // cerr << "图像为空，无法进行匹配" << endl;
        return false;
    }

    // 确保模板尺寸小于屏幕尺寸
    if (templateImg.cols > screen.cols || templateImg.rows > screen.rows) {
        // cerr << "模板图像尺寸大于屏幕尺寸" << endl;
        return false;
    }

    // 转换为灰度图提高匹配效率
    Mat screenGray, templateGray;
    cvtColor(screen, screenGray, COLOR_RGB2GRAY);
    cvtColor(templateImg, templateGray, COLOR_RGB2GRAY);

    // 模板匹配
    Mat result;
    matchTemplate(screenGray, templateGray, result, TM_CCOEFF_NORMED);

    // 寻找匹配结果超过阈值的位置
    vector<Point> locations;
    findNonZero(result >= threshold, locations);

    if (!locations.empty()) {
        // 如果需要返回第一个匹配位置的矩形
        if (outRect != nullptr) {
            *outRect = Rect(locations[0], Size(templateGray.cols, templateGray.rows));
        }
        return true;
    }

    return false;
}

ScreenCheck::ScreenCheck(const std::string &name, const NodeConfig &config) :
    SyncActionNode(name, config)
{
    // 1. 从 NodeConfig 中直接获取黑板指针（config.blackboard 是 public 成员）
    Blackboard::Ptr bb_from_config = config.blackboard;

    // 2. 可将其保存为类成员变量，供后续使用
    bb_ = bb_from_config;
}

NodeStatus ScreenCheck::tick() {
    std::string msg;
    getInput("message", msg);
    // 加载模板图像（对比图）
    Mat templateImg = imread(msg.c_str());  // 替换为你的对比图路径
    if (templateImg.empty()) {
        cerr << "not load" << endl;
        return NodeStatus::SUCCESS;
    }

    // 捕获屏幕
    Mat screen = captureScreen();
    if (screen.empty()) {
        cerr << "get Pingmu error" << endl;
        return NodeStatus::SUCCESS;
    }

    // 检测目标图像
    Rect matchRect;
    bool found = detectImage(screen, templateImg, 0.85, &matchRect);  // 阈值可根据需要调整

    if (found) {
        cout << "yes image!" << endl;
        cout << "pos:l top(" << matchRect.x << "," << matchRect.y
             << "), width:" << matchRect.width << ", height:" << matchRect.height << endl;

        // 可选：在屏幕图像上标记匹配区域并显示
        // rectangle(screen, matchRect, Scalar(0, 255, 0), 2);
        // namedWindow("匹配结果", WINDOW_NORMAL);
        // imshow("匹配结果", screen);
        // waitKey(5000);  // 显示5秒后关闭
    }else {
        cout << "Not ++++++ image!" << endl;
    }
    return NodeStatus::SUCCESS;
}

PortsList ScreenCheck::providedPorts() {
    return {BT::InputPort<std::string>("message")};
}
