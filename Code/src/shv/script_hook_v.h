#pragma once
#include <minwindef.h>

typedef void(*KeyboardHandler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);
typedef void(*PresentCallback)(void*);

enum eGameVersion : int
{
	VER_1_0_335_2_STEAM,
	VER_1_0_335_2_NOSTEAM,

	VER_1_0_350_1_STEAM,
	VER_1_0_350_2_NOSTEAM,

	VER_1_0_372_2_STEAM,
	VER_1_0_372_2_NOSTEAM,

	VER_1_0_393_2_STEAM,
	VER_1_0_393_2_NOSTEAM,

	VER_1_0_393_4_STEAM,
	VER_1_0_393_4_NOSTEAM,

	VER_1_0_463_1_STEAM,
	VER_1_0_463_1_NOSTEAM,

	VER_1_0_505_2_STEAM,
	VER_1_0_505_2_NOSTEAM,

	VER_1_0_573_1_STEAM,
	VER_1_0_573_1_NOSTEAM,

	VER_1_0_617_1_STEAM,
	VER_1_0_617_1_NOSTEAM,

	VER_1_0_678_1_STEAM,
	VER_1_0_678_1_NOSTEAM,

	VER_1_0_757_2_STEAM,
	VER_1_0_757_2_NOSTEAM,

	VER_1_0_757_4_STEAM,
	VER_1_0_757_4_NOSTEAM,

	VER_1_0_791_2_STEAM,
	VER_1_0_791_2_NOSTEAM,

	VER_1_0_877_1_STEAM,
	VER_1_0_877_1_NOSTEAM,

	VER_1_0_944_2_STEAM,
	VER_1_0_944_2_NOSTEAM,

	VER_1_0_1011_1_STEAM,
	VER_1_0_1011_1_NOSTEAM,

	VER_1_0_1032_1_STEAM,
	VER_1_0_1032_1_NOSTEAM,

	VER_1_0_1103_2_STEAM,
	VER_1_0_1103_2_NOSTEAM,

	VER_1_0_1180_2_STEAM,
	VER_1_0_1180_2_NOSTEAM,

	VER_1_0_1290_1_STEAM,
	VER_1_0_1290_1_NOSTEAM,

	VER_1_0_1365_1_STEAM,
	VER_1_0_1365_1_NOSTEAM,

	VER_1_0_1493_0_STEAM,
	VER_1_0_1493_0_NOSTEAM,

	VER_1_0_1493_1_STEAM,
	VER_1_0_1493_1_NOSTEAM,

	VER_SIZE,
	VER_UNK = -1
};
struct ModuleDetection {
	uint64_t m_base;
	uint64_t m_size;
	HMODULE m_module;
	char m_szName[100];

	ModuleDetection() {}

	ModuleDetection(uint64_t a, uint64_t b, const char* c, HMODULE hm)
		: m_base(a), m_size(b), m_module(hm) {
		strcpy(m_szName, c);
	}

	static friend bool operator==(const ModuleDetection& left, HMODULE module) {
		return left.m_module == module;
	}
};
class NativeContext2 : public Base::NativeCallContext
{
private:
	enum
	{
		max_native_params = 32,
		arg_size = sizeof(void*),
	};

	uint8_t m_temp_stack[max_native_params * arg_size];

public:
	inline NativeContext2()
	{
		Args = reinterpret_cast<rage::scrValue*>(&m_temp_stack);
		Return = reinterpret_cast<rage::scrValue*>(&m_temp_stack);

		ArgCount = 0;

		memset(m_temp_stack, 0, sizeof(m_temp_stack));
	}

	template <typename type>
	inline void push(type value)
	{
		if (sizeof(type) > arg_size)
			throw "Argument has an invalid size";

		else if (sizeof(type) < arg_size)
			*reinterpret_cast<uintptr_t*>(m_temp_stack + arg_size * ArgCount) = 0;

		*reinterpret_cast<type*>(m_temp_stack + arg_size * ArgCount) = value;
		ArgCount++;
	}

	inline void reverse()
	{
		uintptr_t temp_values[max_native_params];
		uintptr_t* args = (uintptr_t*)Args;

		for (uint32_t i = 0; i < ArgCount; i++)
		{
			int target = ArgCount - i - 1;
			temp_values[target] = args[i];
		}

		memcpy(m_temp_stack, temp_values, sizeof(m_temp_stack));
	}

	template <typename type>
	inline type getResult()
	{
		return *reinterpret_cast<type*>(m_temp_stack);
	}
};
class ScriptHookV {
public:
	static NativeContext2 Context;
	static uint64_t Hash;
	static std::vector<ModuleDetection> LoadedModuleMemory;

	static void scriptRegister(HMODULE module, void(*LP_SCRIPT_MAIN)());
	static void scriptRegisterAdditionalThread(HMODULE module, void(*LP_SCRIPT_MAIN)());
	static void scriptUnregister(HMODULE module);
	static BYTE* getScriptHandleBaseAddress(int handle);
	static void presentCallbackUnregister(PresentCallback cb);
	static void presentCallbackRegister(PresentCallback cb);
	static void nativeInit(uint64_t hash);
	static void nativePush64(uint64_t val);
	static uint64_t* nativeCall();
	static uint64_t* getGlobalPtr(int index);
	static int createTexture(const char* fileName);
	static void drawTexture(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a);
	static void scriptWait(unsigned long waitTime);
	static void keyboardHandlerRegister(KeyboardHandler function);
	static void keyboardHandlerUnregister(KeyboardHandler function);
	static int getGameVersion();

	static int worldGetAllVehicles(int* arr, int arrSize);
	static int worldGetAllPeds(int* arr, int arrSize);
	static int worldGetAllObjects(int* arr, int arrSize);
	static int worldGetAllPickups(int* arr, int arrSize);
};