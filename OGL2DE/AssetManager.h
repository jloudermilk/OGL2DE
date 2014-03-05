#ifndef _ASSET_MANAGER_H_
#define _ASSET_MANAGER_H_
class AssetManager
{
public:
	static AssetManager& Instance;
private:
	AssetManager(void);
	~AssetManager(void);
};

#endif //_ASSET_MANAGER_H_