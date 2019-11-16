#include "stdafx.h"
#include "ZegoConfigManager.h"
#include <random>

ZegoConfigManager *ZegoConfigManager::instance()
{
    static ZegoConfigManager oInstance;
    return &oInstance;
}

unsigned int ZegoConfigManager::getAppID()
{
    return ;    // input AppID here
}

std::string ZegoConfigManager::getAppSign()
{
	return "";  // input AppSign here
}

bool ZegoConfigManager::isTestEnviroment()
{
    return true;
}

std::string ZegoConfigManager::getRoomID()
{
	return "QuickStartRoom-1";
}

std::string ZegoConfigManager::getUserID()
{
	std::default_random_engine generator(time(0));
	std::uniform_int_distribution<int> distribution(0, 100);
	return std::to_string(distribution(generator));
}

ZegoConfigManager::ZegoConfigManager()
{

}
