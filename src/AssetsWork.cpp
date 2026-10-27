#include <iostream>
#include <cstdlib>
#include <filesystem> // For searching for files in folders at various levels
#include "AssetsWork.h"

#if defined(_WIN32)
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

namespace fs = std::filesystem;

std::string ResolveMediaPath(const std::string& original_path) {
    try {
        if (fs::exists(original_path)) {
            return fs::canonical(original_path).string();
        }
        if (fs::exists("../" + original_path)) {
            return fs::canonical("../" + original_path).string();
        }
        if (fs::exists("../../" + original_path)) {
            return fs::canonical("../../" + original_path).string();
        }
    }
    catch (const std::exception&) {
        return fs::absolute(original_path).string();
    }

    return original_path;
}

void OpenImageInViewer(const std::string& raw_path) {
    std::string path = ResolveMediaPath(raw_path);

    if (!fs::exists(path)) {
        std::cerr << "Ошибка: файл изображения не найден по пути: " << path << std::endl;
        return;
    }

#if defined(_WIN32)
    // Windows
    INT_PTR result = (INT_PTR)ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
    if (result <= 32) {
        std::cerr << "Ошибка ShellExecute при открытии изображения. Код: " << result << std::endl;
    }
#elif defined(__APPLE__)
    // macOS
    std::string cmd = "open \"" + path + "\" &";
    std::system(cmd.c_str());
#elif defined(__linux__)
    // Linux
    std::string cmd = "xdg-open \"" + path + "\" > /dev/null 2>&1 &";
    std::system(cmd.c_str());
#endif
}

void PlayAudioBackground(const std::string& raw_path) {
    std::string path = ResolveMediaPath(raw_path);

    if (!fs::exists(path)) {
        std::cerr << "Ошибка: аудиофайл не найден по пути: " << path << std::endl;
        return;
    }

#if defined(_WIN32)
    // Windows
    mciSendStringA("close current_track", NULL, 0, NULL);

    std::string open_cmd = "open \"" + path + "\" type mpegvideo alias current_track";
    MCIERROR err = mciSendStringA(open_cmd.c_str(), NULL, 0, NULL);
    if (err != 0) {
        char err_buf[256];
        mciGetErrorStringA(err, err_buf, sizeof(err_buf));
        std::cerr << "Ошибка MCI (открытие): " << err_buf << " (код " << err << ")" << std::endl;
        return;
    }

    err = mciSendStringA("play current_track repeat", NULL, 0, NULL);
    if (err != 0) {
        char err_buf[256];
        mciGetErrorStringA(err, err_buf, sizeof(err_buf));
        std::cerr << "Ошибка MCI (воспроизведение): " << err_buf << std::endl;
    }
#elif defined(__APPLE__)
    // macOS
    std::string cmd = "afplay \"" + path + "\" &";
    std::system(cmd.c_str());
#elif defined(__linux__)
    // Linux
    std::string cmd = "mpg123 -q \"" + path + "\" > /dev/null 2>&1 &";
    std::system(cmd.c_str());
#endif
}

void StopAudioBackground() {
#if defined(_WIN32)
    // Windows
    mciSendStringA("stop current_track", NULL, 0, NULL);
    mciSendStringA("close current_track", NULL, 0, NULL);
#elif defined(__APPLE__)
    // macOS
    std::system("killall afplay > /dev/null 2>&1");
#elif defined(__linux__)
    // Linux
    std::system("killall mpg123 > /dev/null 2>&1");
#endif
}