#include <utility>
#include "AudioQuestion.h"

AudioQuestion::AudioQuestion(int i, int cat_id, int c, std::string& t, std::string& diff, std::string& p_answer, std::vector<std::string>& alts, std::string aud_path) : 
    IQuestion(i, cat_id, c, t, diff, p_answer), alternative_answers(alts), audio_path(std::move(aud_path)) {

}

bool AudioQuestion::CheckAnswer(const std::string& user_input) const {
    if (user_input == primary_answer) 
        return true;
    for (const auto& alt : alternative_answers) {
        if (user_input == alt) 
            return true;
    }
    return false;
}

std::string AudioQuestion::GetAudioPath() const {
    return audio_path;
}