#pragma once
#include <string>
#include <map>

using std::string;
using std::map;

struct Events {
	virtual ~Events() {}
};

struct Types
{
	virtual ~Types() {}
};

#pragma region Network
namespace NetworkTypes {
	struct LoaderId : public Types {
		string loaderId;
		LoaderId(string xid) : loaderId(xid) {};
	};
}
#pragma endregion

#pragma region Page
namespace PageTypes {
	struct FrameId : public Types {
		string frameId;
		FrameId(string fid) : frameId(fid) {};
	};

	struct Clip : public Types {
		int x;
		int y;
		int width;
		int height;
		float scale;
		Clip(int x0, int y0, int width0, int height0, float sacle0) : x(x0), y(y0), width(width0), height(height0), scale(sacle0) {};
	};
}
#pragma endregion

