#pragma once
#include <Windows.h>

enum class ClientFrameStage_t : int
{
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};

typedef void(__stdcall* FrameStageNotify)(ClientFrameStage_t curStage);