#ifndef AUDIOQUESTION_H
#define AUDIOQUESTION_H

#include <vector>
#include <string>
#include "IQuestion.h"

class AudioQuestion : public IQuestion {
public:
    AudioQuestion(int i, int cat_id, int c, std::string& t, std::string& diff, std::string& p_answer, std::vector<std::string>& alts, std::string aud_path);

    bool CheckAnswer(const std::string& user_input) const override;
    std::string GetAudioPath() const;

private:
    std::vector<std::string> alternative_answers;
    std::string audio_path;
};

#endif