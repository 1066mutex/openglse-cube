#ifndef FOLDERINFO_H_
#define FOLDERINFO_H_

#ifndef FCUI_FOLDER_INFO
#define FCUI_FOLDER_INFO



#include "FileInfo.h"

#include <list>
#include <vector>

namespace FCInterface {
	
	enum FolderSort { FS_NAME_ASC, FS_NAME_DESC, FS_SIZE_ASC, FS_SIZE_DESC };

	struct FolderInfo {
		FolderInfo() { sortOrder = FS_NAME_ASC; }
		std::vector<FileInfo> contents;
		std::string path;
		FolderSort sortOrder;
		
		bool isEqual(FolderInfo& b);

		void sort(FolderSort order);
		bool removeItem(const std::string& name);

		struct doCompareOrderAlphaDesc {
			bool operator()(const FileInfo& f1, const FileInfo& f2);
		};
	};

}


#endif //!defined FCUI_FOLDER_INFO


#endif // FOLDERINFO_H_
