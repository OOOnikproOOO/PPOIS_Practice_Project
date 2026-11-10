#ifndef ASSETSWORK_H
#define ASSETSWORK_H

#include <string>

std::string ResolveMediaPath(const std::string& original_path);

void OpenImageInViewer(const std::string& raw_path);

void PlayAudioBackground(const std::string& raw_path);

void StopAudioBackground();

#endif