#pragma once 
#include <filesystem>
#include <iostream>


#ifdef __linux__
#include <unistd.h>
#endif


class FileDirectoryManager {
    public:
    std::filesystem::path exePath ; 
    std::filesystem::path projectRootDir  ; 
    
    FileDirectoryManager(){

        #ifdef __linux__
            char buffer[1024];
            ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer));
            if (count != -1) {
                exePath = std::filesystem::path(std::string(buffer, count)).parent_path();
            } else {
                throw std::runtime_error("Failed to get executable path");  
            }
        #endif

        #ifdef _WIN32
            char buffer[MAX_PATH];
            GetModuleFileNameA(NULL, buffer, MAX_PATH);
            exePath = std::filesystem::path(std::string(buffer)).parent_path();
        #endif

        #ifdef __APPLE__
            char buffer[1024];
            uint32_t size = sizeof(buffer);
            if (_NSGetExecutablePath(buffer, &size) == 0) {
                exePath = std::filesystem::path(std::string(buffer)).parent_path();
            } else {
                throw std::runtime_error("Failed to get executable path");  
            }
        #endif

        projectRootDir = exePath.parent_path();
        std::cout << "Project Root Directory: " << projectRootDir << std::endl;
    }

    FileDirectoryManager(const FileDirectoryManager&) = delete; // cannot copy
    FileDirectoryManager& operator=(const FileDirectoryManager&) = delete; // cannot assign

    static std::filesystem::path assetDir () {
        static FileDirectoryManager instance; // Initialized on first use
        return instance.projectRootDir / "assets";
    }


};