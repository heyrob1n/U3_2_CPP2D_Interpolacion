//
// Created by Omar Zamarrón on 14/02/24.
//
#pragma  once
#include <string>

#ifdef ROOT_FOLDER
	const std::string ROOT_DIR = ROOT_FOLDER;
#else
	const std::string ROOT_DIR = ".";
#endif
