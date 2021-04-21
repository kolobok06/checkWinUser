#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <lm.h>

#include <string>
#include "check.h"

std::u16string get_users()
{
	LPWSTR* users;

	LPUSER_INFO_0 pBuf = NULL;
	LPUSER_INFO_0 pTmpBuf;
	DWORD dwLevel = 0;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD dwResumeHandle = 0;
	DWORD i;
	DWORD dwTotalCount = 0;
	NET_API_STATUS nStatus;
	LPTSTR pszServerName = NULL;

	// Call the NetUserEnum function, specifying level 0;
	//   enumerate global user account types only.
	//
	do // begin do
	{
		nStatus = NetUserEnum((LPCWSTR)pszServerName,
		                      dwLevel,
		                      FILTER_NORMAL_ACCOUNT, // global users
		                      (LPBYTE*)&pBuf,
		                      dwPrefMaxLen,
		                      &dwEntriesRead,
		                      &dwTotalEntries,
		                      &dwResumeHandle);
		//
		// If the call succeeds,
		//
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			if ((pTmpBuf = pBuf) != NULL)
			{
				//
				// Loop through the entries.
				//

				users = new LPWSTR [dwEntriesRead];

				for (i = 0; (i < dwEntriesRead); i++)
				{
					assert(pTmpBuf != NULL);

					if (pTmpBuf == NULL)
					{
						fprintf(stderr, "An access violation has occurred\n");
						break;
					}
					//
					//  Print the name of the user account.
					//
					users[i] = pTmpBuf->usri0_name;
					pTmpBuf++;
					dwTotalCount++;
				}
			}
		}
			//
			// Otherwise, print the system error.
			//
		else
			fprintf(stderr, "A system error has occurred: %d\n", nStatus);
		//
		// Free the allocated buffer.
		//
		if (pBuf != NULL)
		{
			NetApiBufferFree(pBuf);
			pBuf = NULL;
		}
	}
	// Continue to call NetUserEnum while
	//  there are more entries.
	//
	while (nStatus == ERROR_MORE_DATA); // end do
	//
	// Check again for allocated memory.
	//
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);

	std::wstring resStr = L"";

	for (i = 0; i < dwEntriesRead; ++i)
	{
		resStr += users[i];
		resStr += L"&";
	}
	std::u16string res = std::u16string(resStr.begin(), resStr.end());
	return res;
}

