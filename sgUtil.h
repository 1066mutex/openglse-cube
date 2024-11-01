#ifndef SGUTIL_H_
#define SGUTIL_H_
#ifndef SG_UTIL_H
#define SG_UTIL_H

#include <string>
#include <vector>
#include <map>
#include <thread>
#include <algorithm>

class Util
{
public:

	static bool stringCaseInsensitiveLessThan(const std::string& a, const std::string& b);

	static void splitFilename(const std::string& filename, std::string& bodyOut, std::string& extensionOut);
	static std::string& trim(std::string& s);
	static void splitPath(std::string& path, std::string& folderOut, std::string& filenameOut);
	static void split(const std::string &s, char delim, std::vector<std::string>& result, bool trimResult = false);
	
	static void stripFilenameIllegals(std::string& filename);

	static void movePathUpOneLevel(std::string& path);
	static std::string subFolderName(std::string& path);

	static std::string threadId(std::thread::id id);
	static std::string join(std::vector<std::string>& parts, char separator);


	static unsigned int crc32(const std::string& str);
	
	static void splitWithQuotes(const std::string &s, char delim, std::map<std::string, std::string>& result, bool trimResult = false);
	
	static void convert_to_words(unsigned int number, std::string& strOut);
	static bool loadConfigFile(const std::string& filename, std::map<std::string, std::string>& configParamsOut);

	static unsigned char hexCharToNum(char hex);

	static char lower(char c);
	static std::string& lower(std::string& s);
	static std::string titleCase(std::string s);
	static bool checkExtension(const std::string& filename, const char* szExt1, ...);

	static void checkFolderTrailingSlash(std::string& folder);


	static float easeQuadInOut(float t);
	static float easeQuartOut(float t);
	static float easeQuartIn(float t);

	static void convertToAscii(const std::vector<unsigned char>& bytesIn, std::string& strOut, bool stripUnprintable = false);
	static void convertFromAscii(const std::string& str, std::vector<unsigned char>& bytesOut);
	static unsigned char checkSum(int messageLength, std::vector<unsigned char> bytes);

	static void stripChar(std::string& str, char toRemove);

	static std::string to_string_with_precision(float val, unsigned int precision);


	static void generateRandomBase36String(unsigned int length, std::string& strOut);
	static unsigned int generateRandomUInt();

	static std::string formatString(const char* szText, ...);

	static void escapeStringForBash(std::string& s);

	static bool parseByteString(const std::string& str, unsigned int& bytesOut);

	template <typename T>
	static T clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

	static std::string padZeros(std::string s, unsigned int width);

	static unsigned int folderSize(const std::string& folder);


};



#endif //!defined SG_UTIL_H


#endif // SGUTIL_H_
