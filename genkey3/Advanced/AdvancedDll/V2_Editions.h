namespace SviFF_Edition
{
#pragma once  

#ifdef SVIFF_EDITION_EXPORTS  
#define SVIFF_EDITION __declspec(dllexport)   
#else  
#define SVIFF_EDITION __declspec(dllimport)   
#endif  // This class is exported from the MathLibrary.dll  
	class cV2_Editions
	{
	public:
		// Returns the custom key
		static SVIFF_EDITION unsigned int Custom(char *FnBtmp, int loFnBtmp, char *DvcId, int loDvcId);

		// Returns the key for Advanced Edition 
		static SVIFF_EDITION unsigned int Advanced(char *DvcId, int loDvcId);

		// Returns the key for standard Edition
		static SVIFF_EDITION unsigned int Standard(char *DvcId, int loDvcId);

	private:
		static unsigned short  calcFrst(size_t len, const unsigned char  *buf, unsigned short  FK);
		static unsigned short  calcScnd(size_t len, const unsigned char  *buf, unsigned short  FK);

	};
}
