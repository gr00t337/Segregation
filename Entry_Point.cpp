#include <Windows.h>

#include <TlHelp32.h>

#include <cstdio>

#include "Byte_Manager/Byte_Manager.hpp"

#include "Redirection_Manager/Redirection_Manager.hpp"

void* Engine_Module;

#include "Extended_Interface.hpp"

#include <unordered_map>

#include "Post_Network_Data_Received.hpp"

#include "Sounds.hpp"

#include "Event_Processor.hpp"

#include "Write_Events.hpp"

#include "Post_Data_Update.hpp"

#include "Build_Transformations.hpp"

#include "Setup_Bones.hpp"

#include "Update_Animation.hpp"

#include "Update_Animation_State.hpp"

#include "Compute_Torso_Rotation.hpp"

#include "Check_Jump.hpp"

#include "Setup_Move.hpp"

#include <algorithm>

#include "Finish_Move.hpp"

#include "Item_Post_Frame.hpp"

#include "Read_Packets.hpp"

#include "Move.hpp"

#include "Send_Datagram.hpp"

#include "Packet_Start.hpp"

#include <vector>

#include "Copy_Command.hpp"

#include "Draw_Crosshair.hpp"

#include "Precache.hpp"

__int32 __stdcall DllMain(HMODULE This_Module, unsigned __int32 Call_Reason, void* Reserved)
{
	if (Call_Reason == DLL_PROCESS_DETACH)
	{
		__fastfail(EXIT_SUCCESS);
	}
	else
	{
		if (Call_Reason == DLL_PROCESS_ATTACH)
		{
			if (GetModuleHandleW(L"hl2.exe") == nullptr)
			{
				void* Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

				PROCESSENTRY32W Snapshot_Entry;

				Snapshot_Entry.dwSize = sizeof(Snapshot_Entry);

				Traverse_Snapshot_Label:
				{
					if (Process32NextW(Snapshot, &Snapshot_Entry) == 0)
					{
						return 1;
					}

					if (wcscmp(Snapshot_Entry.szExeFile, L"hl2.exe") != 0)
					{
						goto Traverse_Snapshot_Label;
					}
				}

				void* Process = OpenProcess(PROCESS_ALL_ACCESS, 0, Snapshot_Entry.th32ProcessID);

				void* Remote_Path = VirtualAllocEx(Process, nullptr, 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

				wchar_t Local_Path[MAX_PATH];

				GetModuleFileNameW(This_Module, Local_Path, sizeof(Local_Path));

				WriteProcessMemory(Process, Remote_Path, Local_Path, sizeof(Local_Path), nullptr);

				WaitForSingleObject(CreateRemoteThread(Process, nullptr, 0, (LPTHREAD_START_ROUTINE)LoadLibraryW, Remote_Path, 0, nullptr), INFINITE);

				VirtualFreeEx(Process, Remote_Path, 0, MEM_RELEASE);
			}
			else
			{
				AllocConsole();

				SetConsoleTitleW(L"Segregation");

				_wfreopen(L"CONOUT$", L"w", stdout);

				SetConsoleOutputCP(65001);

				HANDLE Standard_Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

				CONSOLE_FONT_INFOEX Console_Font_Information = { sizeof(CONSOLE_FONT_INFOEX), 0, { 0, 12 }, FF_DONTCARE, FW_NORMAL, { L"Terminal" } };

				SetCurrentConsoleFontEx(Standard_Output_Handle, 0, &Console_Font_Information);

				CONSOLE_CURSOR_INFO Console_Cursor_Information = { sizeof(Console_Cursor_Information) };

				SetConsoleTextAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED);

				SetConsoleCursorInfo(Standard_Output_Handle, &Console_Cursor_Information);

				CONSOLE_SCREEN_BUFFER_INFO Console_Screen_Buffer_Information;

				GetConsoleScreenBufferInfo(Standard_Output_Handle, &Console_Screen_Buffer_Information);

				COORD Top_Left = { };

				DWORD Characters_Written;

				FillConsoleOutputAttribute(Standard_Output_Handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_RED, Console_Screen_Buffer_Information.dwSize.X * Console_Screen_Buffer_Information.dwSize.Y, Top_Left, &Characters_Written);

				Engine_Module = GetModuleHandleW(L"engine.dll");

				_putws(L"[ + ] Delimit Interface");
				{
					unsigned __int8 Cheat_Flag_Bytes[5] = { 254, 64, 48, 144, 235 };

					Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int32)Engine_Module + 1631348), sizeof(Cheat_Flag_Bytes), Cheat_Flag_Bytes);

					*(__int8*)((unsigned __int32)Engine_Module + 7621720) = 1;

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Engine_Module + 1849144), 1, 235);
				}

				_putws(L"[ + ] Extend Interface");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Engine_Module + 2750823), 2, 144);

					Implement_Extended_Interface();
				}

				_putws(L"[ + ] Events");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 1808096), 1, 195);

					Original_Post_Network_Data_Received_Caller = Redirection_Manager::Redirect_Function(3, (void*)((unsigned __int32)Client_Module + 1808192), (void*)Redirected_Post_Network_Data_Received);

					void* Event_Listener = (void*)__builtin_malloc(sizeof(void*));

					void* Event_Listener_Table = __builtin_malloc(sizeof(void*) * 2);

					*(void**)((unsigned __int32)Event_Listener_Table + 4) = (void*)Event_Processor;

					*(void**)Event_Listener = Event_Listener_Table;

					using Add_Listener_Type = __int8(__thiscall*)(void* Event_Manager, void* Listener, char* Event, void* Unknown_Parameter);

					Add_Listener_Type((unsigned __int32)Engine_Module + 1966272)((void*)((unsigned __int32)Engine_Module + 7750640), Event_Listener, (char*)"player_hurt", nullptr);

					Add_Listener_Type((unsigned __int32)Engine_Module + 1966272)((void*)((unsigned __int32)Engine_Module + 7750640), Event_Listener, (char*)"player_death", nullptr);

					Add_Listener_Type((unsigned __int32)Engine_Module + 1966272)((void*)((unsigned __int32)Engine_Module + 7750640), Event_Listener, (char*)"bullet_impact", nullptr);

					Original_Write_Events_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Engine_Module + 1973888), (void*)Redirected_Write_Events);

					Original_Post_Data_Update_Caller = Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 2228704), (void*)Redirected_Post_Data_Update);
				}

				_putws(L"[ + ] Interpolation");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 681803), 2, 0);
				}

				_putws(L"[ + ] Animations");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 700687), 1, 235);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 700701), 1, 89);

					Original_Build_Transformations_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Client_Module + 652272), (void*)Redirected_Build_Transformations);

					Original_Setup_Bones_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Client_Module + 697024), (void*)Redirected_Setup_Bones);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 699166), 1, 235);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 745070), 6, 144);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2235349), 145, 144);

					Original_Update_Animation_Caller = Redirection_Manager::Redirect_Function(1, (void*)((unsigned __int32)Client_Module + 2235264), (void*)Redirected_Update_Animation);
					
					Original_Check_Jump_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Client_Module + 1334448), (void*)Redirected_Check_Jump);

					Original_Update_Animation_State_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Client_Module + 2355616), (void*)Redirected_Update_Animation_State);

					Original_Compute_Torso_Rotation_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Client_Module + 2350960), (void*)Redirected_Compute_Torso_Rotation);
				
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2351193), 1, 139);
				}

				_putws(L"[ + ] Sound");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Engine_Module + 534700), 2, 144);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Engine_Module + 226850), 1, 235);
				}

				_putws(L"[ + ] Prediction");
				{
					static Prediction_Descriptor_Structure Original_Prediction_Descriptor;

					Prediction_Descriptor_Structure* Prediction_Descriptor = (Prediction_Descriptor_Structure*)((unsigned __int32)Client_Module + 6890952);

					Byte_Manager::Copy_Bytes(0, &Original_Prediction_Descriptor, sizeof(Prediction_Descriptor_Structure), Prediction_Descriptor);

					static Prediction_Field_Structure Prediction_Fields = { 1, (char*)"m_flVelocityModifier", { 40112 }, 1, 256, { }, nullptr, sizeof(float), { }, 0.005f };

					Prediction_Descriptor->Fields = &Prediction_Fields;

					Prediction_Descriptor->Size = sizeof(Prediction_Fields) / sizeof(Prediction_Field_Structure);

					Prediction_Descriptor->Parent = &Original_Prediction_Descriptor;

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 1813132), 1, 235);

					Original_Setup_Move_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Client_Module + 1811728), (void*)Redirected_Setup_Move);

					Original_Finish_Move_Caller = Redirection_Manager::Redirect_Function(2, (void*)((unsigned __int32)Client_Module + 1806880), (void*)Redirected_Finish_Move);

					Original_Item_Post_Frame_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Client_Module + 598256), (void*)Redirected_Item_Post_Frame);
				}

				_putws(L"[ + ] Network");
				{
					Original_Read_Packets_Caller = Redirection_Manager::Redirect_Function(4, (void*)((unsigned __int32)Engine_Module + 1006704), (void*)Redirected_Read_Packets);

					Original_Move_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Engine_Module + 1005520), (void*)Redirected_Move);

					//Original_Send_Datagram_Caller = Redirection_Manager::Redirect_Function(2, (void*)((unsigned __int32)Engine_Module + 2197744), (void*)Redirected_Send_Datagram);

					//Original_Packet_Start_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Engine_Module + 2357568), (void*)Redirected_Packet_Start);
				}

				_putws(L"[ + ] Input");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 1560243), 3, 144);

					Original_Copy_Command_Caller = Redirection_Manager::Redirect_Function(0, (void*)((unsigned __int32)Client_Module + 1392880), (void*)Redirected_Copy_Command);
				}

				_putws(L"[ + ] View Effects");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 594304), 40, 144);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 594367), 42, 144);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 595216), 1, 235);
				}

				_putws(L"[ + ] Crosshair");
				{
					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 1479888), 1, 195);

					Redirection_Manager::Redirect_Function((void*)((unsigned __int32)Client_Module + 2943808), (void*)Redirected_Draw_Crosshair);
				}

				_putws(L"[ + ] Materials");
				{
					Original_Precache_Caller = Redirection_Manager::Redirect_Function(5, (void*)((unsigned __int32)GetModuleHandleW(L"materialsystem.dll") + 243840), (void*)Redirected_Precache);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2035313), 1, 0);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2134168), 1, 235);

					unsigned __int8 Smoke_Bytes[3] = { 194, 4 };

					Byte_Manager::Copy_Bytes(0, (void*)((unsigned __int32)Client_Module + 3107056), sizeof(Smoke_Bytes), Smoke_Bytes);

					Byte_Manager::Set_Bytes(0, (void*)((unsigned __int32)Client_Module + 2229392), 1, 195);
				}
			}
		}
	}

	return 1;
}