#include "AutoUpdate.hpp"

int AutoUpdate::CheckForUpdates(std::string currentVer)
{
	//const wchar_t* srcURL = L"http://23.94.190.113/Version";

	int major = MAKELPARAM(currentVer[0] - 0x30, currentVer[2] - 0x30);
	int minor = MAKEWPARAM(currentVer[0] - 0x30, currentVer[2] - 0x30);
	int Combined = major + minor;

	return Combined;
}

bool AutoUpdate::DownloadFile()
{
	bool nCompleted = false;
	//const wchar_t* srcURL = L"http://23.94.190.113/OKPOE";
	// the destination file 
	//const wchar_t* destFile = L"OKPOE.pkg";

	// URLDownloadToFile returns S_OK on success 
	//if (S_OK == URLDownloadToFile(NULL, srcURL, destFile, 0, NULL))
	//{
		//printf("Saved to 'OKPOE.pkg'");
		nCompleted = true;
	//}
	//else
	//{
		//printf("Failed");
	//}
//
	return nCompleted;
}