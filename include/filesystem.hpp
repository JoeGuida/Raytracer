#ifndef RAYTRACER_FILESYSTEM_HPP
#define RAYTRACER_FILESYSTEM_HPP

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

class FileSystem {
private:
    static std::string get_root() {
        std::string env = std::getenv("RAYTRACER_ROOT");

        if (env.empty()) {
            throw std::runtime_error("ERROR::FILESYSTEM Error reading environment variable: RAYTRACER_ROOT");
        }
        return std::string(env);
    }

public:
    static std::string get_path(const std::string& path) {
        std::string root = get_root();
        return std::string(root + path);
    }
};

#endif