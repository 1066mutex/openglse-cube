

#ifndef PLATFORM_UTILS_H
#define PLATFORM_UTILS_H

#include "FolderInfo.h"
#include "data/DateTime.h"


#include <list>
#include <string>
#include <time.h>


void sleep_ms(unsigned int ms);
void sleep_ns(unsigned long ns);
void strncpy_safe(char* dest, const char* src, unsigned int count);

void getFolderInfo(const std::string& folder, FCInterface::FolderInfo& folderInfoOut, const bool &threadStopFlag = true, const char* szExtension = 0, bool includeDirectories = true, bool includeFiles = true);

void getFilesInFolder(const std::string& folder, std::list<std::string>& filesOut, const char* szExtension = 0);

void getSubfolders(const std::string& folder, std::list<std::string>& subfoldersOut);
void getCWD(std::string& directoryOut);
void localtime_safe(struct tm* const _Tm, time_t const* const _Time);

unsigned int getSizeOfFile(const std::string& filePath);

double currentSeconds();

void startTone();
void stopTone();


bool fileExists(const std::string& filePath);

FILE* pipeFromProcess(const char *command, const char *type);
void closePipe(FILE* pipe);
int fileDescriptor(FILE* file);
int setPipeToNonBlocking(int fd);
int posixRead(int fildes, void *buf, size_t nbyte);
int flushFile(int fd);
FILE * myfopen(const char * filename, const char * mode);
bool makeFolder(const std::string& str);
int moveFile(const std::string& src, const std::string& dest);


bool isMediaReady(const std::string& mountpoint);
bool isAMountPoint(const std::string& mountpoint);

bool getDiskUsage(const std::string& path, unsigned int& blockSizeOut, unsigned int& totalBlocksOut, unsigned int& totalNodesOut, unsigned int& freeBlocksOut, unsigned int& freeNodesOut);


int clearFolderContents(const std::string& folder);

bool myrmdir(const std::string& folder);


std::string exec(const char* cmd);

void printThreadParams(const char* threadName);
void setThreadPriorityForGUI();
void setThreadLowPriority();
void setThreadNormalPriority();

bool setSystemAndHardwareTime(const FCInterface::DateTime& dt);

bool isFolderWritable(std::string& folder);

int execAndGetExitCode(const std::string& cmd);

std::string fileSystemType(const std::string& devicePath);

std::string remountDevice(const std::string& devicePath);

float userSpaceTime();

#endif // !PLATFORM_UTILS_H

