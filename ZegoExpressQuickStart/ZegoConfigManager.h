#ifndef ZEGOCONFIGMANAGER_H
#define ZEGOCONFIGMANAGER_H

#include <string>

class ZegoConfigManager
{
public:
    static ZegoConfigManager* instance();
    unsigned int getAppID();
    std::string getAppSign();
    bool isTestEnviroment();

	std::string getRoomID();
	std::string getUserID();

private:
    ZegoConfigManager();
};

#endif // ZEGOCONFIGMANAGER_H
