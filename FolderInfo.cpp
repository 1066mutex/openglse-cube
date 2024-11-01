
#include "FolderInfo.h"

#include <algorithm>

#include "sgUtil.h"


using namespace FCInterface;
using namespace std;

bool FolderInfo::doCompareOrderAlphaDesc::operator()(const FileInfo& f1, const FileInfo& f2)
{
	if (f1.type == FileType::FT_FOLDER) {
		if (f2.type == FileType::FT_FILE)
			return true;
		else
			return Util::stringCaseInsensitiveLessThan(f1.name, f2.name);
	}
	else {
		if (f2.type == FileType::FT_FOLDER)
			return false;
		else
			return Util::stringCaseInsensitiveLessThan(f1.name, f2.name);
	}
}

void FolderInfo::sort(FolderSort order)
{

	std::sort(contents.begin(), contents.end(), doCompareOrderAlphaDesc());


}

bool FolderInfo::removeItem(const std::string& name)
{

	bool found = false;
	
	vector<FileInfo>::iterator iter;
	for (iter = contents.begin(); iter != contents.end(); iter++) {
		if (iter->name == name) {
			found = true;
			contents.erase(iter);
			break;
		}
	}
	
	return found;
}


bool FolderInfo::isEqual(FolderInfo& b)
{

	if (contents.size() != b.contents.size()) {
		return false;
	}

	bool equal = true;


	sort(FS_NAME_ASC);
	b.sort(FS_NAME_ASC);

	vector<FileInfo>::iterator iterA, iterB;
	iterA = contents.begin();
	iterB = b.contents.begin();

	for (unsigned int s = 0; s < contents.size(); s++) {
		if (iterA->name != iterB->name)
			return false;
		if (iterA->type != iterB->type)
			return false;
		if (iterA->type == FileType::FT_FILE && (iterA->size != iterB->size)) {
			return false;
		}

		iterA++;
		iterB++;
	}

	
	return true;

}