
#ifndef FCUI_FILE_INFO
#define FCUI_FILE_INFO


#include <string>



namespace FCInterface {


	enum class FileType { FT_NONE, FT_FILE, FT_FOLDER };
	enum class FileMediaType { FMT_NONE,  FMT_PNG, FMT_JPEG, FMT_FIMAGE, FMT_UNKNOWN };

	struct FileInfo {
		FileInfo() { type = FileType::FT_NONE; size = 0; mediaType = FileMediaType::FMT_UNKNOWN; }
		FileInfo(std::string _name, FileType _type, unsigned int _size, FileMediaType _mediaType = FileMediaType::FMT_UNKNOWN) { type = _type; name = _name; size = _size; mediaType = _mediaType; }
		std::string name;
		FileType type;
		FileMediaType mediaType;
		unsigned int size;

	};

}


#endif //!defined FCUI_FILE_INFO

