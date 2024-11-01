#include "sgUtil.h"

#include "sgPlatformUtils.h"
#include "FolderInfo.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <sstream> 
#include <string>
#include <fstream>
#include <iomanip> 
#include <cstdarg>
#include <cstdlib>
#include <ctime>
#include <array>
#include <numeric>
#include <list>
#include <regex>

using namespace std;
using namespace FCInterface;

void Util::splitFilename(const std::string& filename, std::string& bodyOut, std::string& extensionOut)
{
	size_t pos = filename.find_last_of('.');
	if (pos != std::string::npos)
	{
		bodyOut = filename.substr(0, pos);
		extensionOut = filename.substr(pos + 1, (filename.size() - pos) - 1);
	}
	else
	{
		bodyOut = filename;
		extensionOut.clear();
	}

}

void Util::stripFilenameIllegals(std::string& filename) {

	string illegal = "<>:\"/\\|?";
	string b;
	bool strip;
	b.reserve(filename.size());
	for (auto c : filename) {
		strip = false;
		for (auto i : illegal) {
			if (i == c) {
				strip = true;
				break;
			}
		}
		if (!strip) {
			b.push_back(c);
		}
	}
	filename.swap(b);
}

void Util::splitPath(std::string& path, std::string& folderOut, std::string& filenameOut)
{
	list<string> parts;
	parts.emplace_back();
	int sectionStart = -1;
	for (char c : path) {
		if (c == '/' || c == '\\') {
			parts.emplace_back(string());
			parts.back().reserve(128);
		}
		else {
			parts.back().push_back(c);
		}
	}
	if (parts.size() > 1) {
		parts.back().swap(filenameOut);
		parts.pop_back();
		for (string& s : parts) {
			folderOut += s;
			folderOut.push_back('/');
		}
	}
	else {
		filenameOut.swap(parts.front());
	}
}

void Util::movePathUpOneLevel(std::string& path)
{
	if (*path.rbegin() == '/') {
		path.pop_back();
	}

	size_t pos = path.find_last_of('/');
	if (pos != string::npos) {
		path = path.substr(0, pos + 1);
	}
	else {
		path = "";
	}
}

std::string Util::subFolderName(std::string& path)
{
	vector<string> parts;
	split(path, '/', parts);

	if (parts.empty())
		return string();

	if (parts.back().empty())
		parts.pop_back();

	if (!parts.empty())
		return parts.back();

	return string();

}

inline int is_space(int c)
{
	return  (c == 0x20 || (c >= 0x9 && c <= 0xD));
}


std::string& Util::trim(std::string& s)
{

	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(is_space))));

	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(is_space))).base(), s.end());


	return s;

}

unsigned char Util::hexCharToNum(char hex)
{
	if (hex >= '0' && hex <= '9')
		return hex - '0';
	else if (hex >= 'A' && hex <= 'Z')
		return hex - 55;
	else
		return hex - 87;

}


void Util::split(const std::string &s, char delim, std::vector<std::string>& result, bool trimResult) {
	std::istringstream ss(s);
	std::string item;
	unsigned int count = 0;

	for (std::string::const_iterator iter = s.begin(); iter != s.end(); iter++)
	{
		if (*iter == delim)
			count++;
	}
	result.reserve(count + 1);

	while (std::getline(ss, item, delim)) {
		if (trimResult)
			Util::trim(item);
		result.push_back(item);
	}
}


std::string Util::join(std::vector<std::string>& parts, char separator)
{
	stringstream ss;
	for (vector<string>::iterator iter = parts.begin(); iter != parts.end(); iter++) {

		if (iter != parts.begin())
			ss << separator;

		ss << *iter;
	}
	return ss.str();
}


void Util::splitWithQuotes(const std::string &s, char delim, std::map<std::string, std::string>& result, bool trimResult)
{

	string key;
	string value;
	bool inKey = true;
	bool inQuotes = false;
	char c;
	for (string::const_iterator iter = s.begin(); iter != s.end(); iter++) {
		c = *iter;
		if (inKey) {
			if (c == '=') {
				inKey = false;
			}
			else {
				key += c;
			}
		}
		else {
			if (inQuotes) {
				if (c == '"') {
					inQuotes = false;
				}
				else {
					value += c;
				}
			}
			else {
				if (c == '"') {
					inQuotes = true;
				}
				else if (c == ',') {
					if (key.size() > 0)
						result[key] = value;
					key.clear();
					value.clear();
					inKey = true;
				}
				else {
					value += c;
				}
			}
		}
	}
	if (key.size() > 0)
		result[key] = value;

}



/* A function that prints given number in words */
void Util::convert_to_words(unsigned int number, std::string& strOut)
{
	string num = std::to_string(number);


	int len = num.size();  // Get number of digits in given number

							/* Base cases */
	if (len == 0) {
		return;
	}
	if (len > 4) {
		return;
	}

	/* The first string is not used, it is to make array indexing simple */
	const char *single_digits[] = { "zero", "one", "two", "three", "four",
		"five", "six", "seven", "eight", "nine" };

	/* The first string is not used, it is to make array indexing simple */
	const char *two_digits[] = { "", "ten", "eleven", "twelve", "thirteen", "fourteen",
		"fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };

	/* The first two string are not used, they are to make array indexing simple*/
	const char *tens_multiple[] = { "", "", "twenty", "thirty", "forty", "fifty",
		"sixty", "seventy", "eighty", "ninety" };

	const char *tens_power[] = { "hundred", "thousand" };


	/* For single digit number */
	if (len == 1) {
		strOut = single_digits[num[0] - '0'];
		return;
	}

	/* Iterate while num is not '\0' */



	while (num.size() > 0) {

		/* Code path for first 2 digits */
		if (len >= 3) {
			if (num[0] - '0' != 0) {

				strOut += single_digits[num[0] - '0'];
				strOut += " ";
				strOut += tens_power[len - 3];
				strOut += " ";

			}
			--len;
		}

		/* Code path for last 2 digits */
		else {
			/* Need to explicitly handle 10-19. Sum of the two digits is
			used as index of "two_digits" array of strings */
			if (num[0] == '1') {
				int sum = num[0] - '0' + num[1] - '0';
				strOut += two_digits[sum];
				return;
			}

			/* Need to explicitely handle 20 */
			else if (num[0] == '2' && num[1] == '0') {
				strOut += "twenty";
				return;
			}

			/* Rest of the two digit numbers i.e., 21 to 99 */
			else {
				int i = num[0] - '0';
				strOut += (i ? tens_multiple[i] : "");
				strOut += " ";
				num.erase(0, 1);
				if (num[0] != '0') {
					strOut += single_digits[num[0] - '0'];
					strOut += " ";
				}
			}
		}
		num.erase(0, 1);
	}
}


float Util::easeQuadInOut(float t)
{
	if (t < 0.5)
		return (2 * t * t);
	else
		return -1 + (4 - 2 * t)*t;


}

float Util::easeQuartOut(float t)
{
	return -1 * ((t = t - 1)*t*t*t - 1);
}

float Util::easeQuartIn(float t)
{
	return t*t*t*t;
}

char Util::lower(char c)
{
	if (c >= 'A' && c <= 'Z') {
		c += 32;
	}
	return c;
}

string& Util::lower(string& s)
{
	for (std::string::iterator iter = s.begin(); iter != s.end(); iter++) {
		if (*iter >= 'A' && *iter <= 'Z')
			*iter += 32;
	}
	return s;
}

std::string Util::titleCase(std::string s)
{
	if (s.empty())
		return s;

	//first character always goes uppercase
	if (s[0] >= 'a' && s[0] <= 'z')
		s[0] -= 32;

	unsigned int rem = s.size() - 1 ;
	string::iterator next;
	for (string::iterator iter = s.begin() + 1; iter != s.end();) {
		if (*iter == ' ' && rem > 1) {
			next = iter + 1;
			if (*next >= 'a' && *next <= 'z') {
				*next -= 32;
			}
			iter += 2;
			rem -= 2;
		}
		else {
			iter++;
			rem--;
		}
	}
	return s;
}


bool Util::loadConfigFile(const std::string& filename, std::map<std::string, std::string>& configParamsOut)
{
	ifstream fh;
	fh.open(filename);

	if (fh.is_open()) {
		std::string contents((std::istreambuf_iterator<char>(fh)),
			std::istreambuf_iterator<char>());

		vector<string> lines;
		vector<string> keyvalue;
		string line;
		keyvalue.reserve(2);

		Util::split(contents, '\n', lines);

		for (vector<string>::iterator iter = lines.begin(); iter != lines.end(); iter++) {

			keyvalue.clear();
			Util::split(*iter, '#', keyvalue);

			if (keyvalue.size() > 1) {
				line = keyvalue[0];
			}
			else
			{
				line = *iter;
			}

			keyvalue.clear();
			Util::split(line, ':', keyvalue);
			size_t pos = line.find_first_of(':');
			if(pos != string::npos && pos > 0 && pos < (line.size()-1)) {
				string key = line.substr(0, pos);
				string value = line.substr(pos + 1);
				configParamsOut[Util::trim(key)] = Util::trim(value);
			}
		}
	}
	else {
		return false;
	}

	return true;
}



unsigned char Util::checkSum(int messageLength, std::vector<unsigned char> bytes)
{
	unsigned char* pBytes = (unsigned char*)&messageLength;
	unsigned char cs = pBytes[0] ^ pBytes[1] ^ pBytes[2] ^ pBytes[3];

	for (vector<unsigned char>::iterator iter = bytes.begin(); iter != bytes.end(); iter++)
	{
		cs = cs ^ *iter;
	}
	return cs;

}


void Util::convertToAscii(const std::vector<unsigned char>& bytesIn, std::string& strOut, bool stripUnprintable)
{

	strOut.reserve(bytesIn.size());
	for (vector<unsigned char>::const_iterator iter = bytesIn.begin(); iter != bytesIn.end(); iter++)
	{
		if(!stripUnprintable || ((*iter) >= 32 && (*iter) < 127))
			strOut.push_back((unsigned char)*iter);
	}

}

void Util::convertFromAscii(const std::string& str, std::vector<unsigned char>& bytesOut)
{
	bytesOut.reserve(str.size());

	for (string::const_iterator iter = str.begin(); iter != str.end(); iter++)
	{
		bytesOut.push_back(*iter);
	}
}

void Util::stripChar(std::string& str, char toRemove)
{
	string b;
	b.reserve(str.size());
	for (string::iterator iter = str.begin(); iter != str.end(); iter++) {
		if (*iter != toRemove) {
			b.push_back(*iter);
		}
	}
	str.swap(b);
}


std::string Util::to_string_with_precision(float val, unsigned int precision)
{
	ostringstream stream;
	stream << fixed << setprecision(precision) << val;
	string out = stream.str();

	//remove instances of '-0' 
	if (out.size() > 0 && out[0] == '-') {
		return out.find_first_of("123456789") == out.npos ? out.substr(1) : out;
	}
	else {
		return out;
	}
	
}


bool Util::checkExtension(const std::string& filename, const char* szExt1, ...)
{
	va_list argp;
	string extTest = szExt1;

	size_t dotPos = filename.find_last_of('.');
	if (dotPos == string::npos && (dotPos != filename.size()-1) )
		return false;

	string fileExt = filename.substr(dotPos + 1, string::npos);
	lower(fileExt);

	bool r = false;
	va_start(argp, szExt1);
	do {
		
		lower(extTest);
		if (extTest == fileExt) {
			r = true;
			break;
		}
		char* arg = va_arg(argp, char*);
		extTest = arg ? arg : "";
	} while (!extTest.empty());


	va_end(argp);

	return r;
}



void Util::generateRandomBase36String(unsigned int length, std::string& strOut)
{
	static const string& base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	strOut.resize(length);

	srand((unsigned int)time(0));

	for (unsigned int i = 0; i < length; i++) {
		strOut[i] = base64[rand() % base64.size()];
	}

}

unsigned int Util::generateRandomUInt()
{
	srand((unsigned int)time(0));
	return rand();
}

std::string Util::formatString(const char* szText, ...)
{
	char szBuffer[4096];

	va_list argp;
	va_start(argp, szText);
	vsnprintf(szBuffer, 4096, szText, argp);
	va_end(argp);

	szBuffer[4095] = 0;

	return string(szBuffer);
}


std::string Util::threadId(std::thread::id id)
{
	stringstream ss;
	ss << id;
	return ss.str();
}



bool Util::parseByteString(const std::string& str, unsigned int& bytesOut)
{
	unsigned int multipler = 1;
	unsigned int size = str.size();
	string numberStr;
	if (size > 1 && str[size-1] == 'b') {
		numberStr = str.substr(0, size - 1);
	}
	else if (size > 3 && str.compare(size - 3, 3, "kiB") == 0) {
		multipler = 1024;
		numberStr = str.substr(0, size - 3);
	}
	else if (size > 3 && str.compare(size - 3, 3, "MiB") == 0) {
		multipler = 1048576;
		numberStr = str.substr(0, size - 3);
	}
	else {
		numberStr = str;
	}

	try {
		bytesOut = std::stoul(numberStr) * multipler;
	}
	catch (...) {
		return false;
	}
	return true;
}


std::string Util::padZeros(std::string s, unsigned int width)
{
	if (s.size() < width) {
		s.insert(0, width - s.size(), '0');
	}
	return s;
}

std::array<unsigned int, 256> generate_crc_lookup_table() noexcept
{
	const unsigned int reversed_polynomial = 0xEDB88320;

	// This is a function object that calculates the checksum for a value,
	// then increments the value, starting from zero.
	struct byte_checksum
	{
		unsigned int operator()() noexcept
		{
			auto checksum = n++;

			for (auto i = 0; i < 8; ++i)
				checksum = (checksum >> 1) ^ ((checksum & 0x1u) ? reversed_polynomial : 0);

			return checksum;
		}

		unsigned n = 0;
	};

	auto table = std::array<unsigned int, 256>{};
	std::generate(table.begin(), table.end(), byte_checksum{});

	return table;
}


unsigned int Util::crc32(const std::string& str)
{
	static auto const table = generate_crc_lookup_table();
	return 0xFFFFFFFF &
		~std::accumulate(str.begin(), str.end(),
			~0 &0xFFFFFFFF,
			[](unsigned int checksum, unsigned int value)
	{ return table[(checksum ^ value) & 0xFFu] ^ (checksum >> 8); });
}


unsigned int Util::folderSize(const std::string& folder)
{
	FolderInfo info;
	unsigned int total = 0;

	getFolderInfo(folder, info);
	
	for (FileInfo& f : info.contents) {
		if (f.type == FileType::FT_FILE)
			total += f.size;
		else if (f.type == FileType::FT_FOLDER && f.name.find("..") == string::npos)
			total += folderSize(folder + f.name + "/");
			
	}
	return total;
}

bool Util::stringCaseInsensitiveLessThan(const std::string& a, const std::string& b)
{
	unsigned int compareLength = min(a.size(), b.size());
	const char* pA = &a[0];
	const char* pB = &b[0];

	for (unsigned int i = 0; i < compareLength; i++) {
		if (*pA != *pB) {
			char ca = *pA, cb = *pB;
			if (ca >= 97 && ca <= 122) {
				ca -= 32;
			}
			if (cb >= 97 && cb <= 122) {
				cb -= 32;
			}
			return ca < cb;
		}
		pA++;
		pB++;
	}
	return a.size() < b.size();
}

void Util::checkFolderTrailingSlash(std::string& folder)
{
	if (!folder.empty()) {
		if (folder.back() == '\\')
			folder.back() = '/';
		else if (folder.back() != '/')
			folder += '/';
	}

}


void Util::escapeStringForBash(std::string& s)
{
	string r = regex_replace(s, regex("'"), "'\\''");

	s = "'" + r + "'";
}