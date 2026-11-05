#include <iostream>
#include <cstdlib>
#include <filesystem> // For searching for files in folders at various levels
#include "AssetsWork.h"
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

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

    INT_PTR result = (INT_PTR)ShellExecuteA(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
    if (result <= 32) {
        std::cerr << "Ошибка ShellExecute при открытии изображения. Код: " << result << std::endl;
    }
}

void PlayAudioBackground(const std::string& raw_path) {
    std::string path = ResolveMediaPath(raw_path);

    if (!fs::exists(path)) {
        std::cerr << "Ошибка: аудиофайл не найден по пути: " << path << std::endl;
        return;
    }

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
}

void StopAudioBackground() {
    mciSendStringA("stop current_track", NULL, 0, NULL);
    mciSendStringA("close current_track", NULL, 0, NULL);
}