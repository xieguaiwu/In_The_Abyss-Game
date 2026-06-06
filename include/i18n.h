#ifndef I18N_H
#define I18N_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

class I18N {
    std::string current_lang_ = "zh";
    std::map<std::string, std::string> strings_;
public:
    static I18N& instance() {
        static I18N inst;
        return inst;
    }

    bool load(const std::string& lang) {
        std::string path = "translations/" + lang + ".json";
        std::ifstream f(path);
        if (!f) {
            current_lang_ = "zh";
            return false;
        }
        try {
            auto j = nlohmann::json::parse(f);
            strings_.clear();
            for (auto& [key, val] : j.items())
                strings_[key] = val.get<std::string>();
            current_lang_ = lang;
            return true;
        } catch (...) {
            current_lang_ = "zh";
            return false;
        }
    }

    std::string _(const std::string& key) const {
        auto it = strings_.find(key);
        return it != strings_.end() ? it->second : key;
    }

    std::string current_lang() const { return current_lang_; }
    void set_lang(const std::string& lang) { load(lang); }
};

#endif
