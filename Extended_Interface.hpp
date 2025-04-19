struct Interface_Structure
{
	__int8 Additional_Bytes_1[36];

	char* String;

	__int8 Additional_Bytes_2[48];

	float Get_Floating_Point()
	{
		return *(float*)(*(unsigned __int32*)((unsigned __int32)this + 28) + 44);
	};

	__int32 Get_Integer()
	{
		return *(__int32*)(*(unsigned __int32*)((unsigned __int32)this + 28) + 48);
	};
};

Interface_Structure Interface_Commentator;

void* Client_Module;

Interface_Structure Interface_Get_Priorities;

#include "Priority.hpp"

Interface_Structure Interface_Set_Priority;

Interface_Structure Interface_Bruteforce_Memory_Tolerance;

Interface_Structure Interface_Bruteforce_Tolerance;

#include "Bruteforce.hpp"

Interface_Structure Interface_Bruteforce;

Interface_Structure Interface_Bruteforce_Angles;

Interface_Structure Interface_Bruteforce_Relative;

Interface_Structure Interface_Bruteforce_Perpendicular;

Interface_Structure Interface_Target_On_Simulation;

Interface_Structure Interface_High_Jump;

Interface_Structure Interface_Alternative;

Interface_Structure Interface_Minimum_Choked_Commands;

Interface_Structure Interface_Maximum_Choked_Commands;

Interface_Structure Interface_Aim_Intersection;

Interface_Structure Interface_Aim_Heights;

#include "Aim.hpp"

Interface_Structure Interface_Angle_X;

Interface_Structure Interface_Animated_Angle_Y;

Interface_Structure Interface_Angle_Y;

Interface_Structure Interface_Body_Update;

Interface_Structure Interface_Body_Angle_Y;

Interface_Structure Interface_Uber_Alles_Scale;

Interface_Structure Interface_Uber_Alles_Speed;

Interface_Structure Interface_sv_showhitboxes;

void Implement_Extended_Interface()
{
	Client_Module = GetModuleHandleW(L"client.dll");

	auto Create_Interface = [](Interface_Structure* Interface, char* Name, char* Value, void* Handler)
	{
		if (Value == nullptr)
		{
			using Create_Command_Type = void(__thiscall*)(Interface_Structure* Interface, char* Name, void* Handler, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Unknown_Parameter_3);

			Create_Command_Type((unsigned __int32)Client_Module + 4039808)(Interface, Name, Handler, nullptr, nullptr, nullptr);
		}
		else
		{
			using Create_Variable_Type = void(__thiscall*)(Interface_Structure* Interface, char* Name, char* Value, void* Unknown_Parameter_1, void* Unknown_Parameter_2, void* Handler);

			Create_Variable_Type((unsigned __int32)Engine_Module + 2752624)(Interface, Name, Value, nullptr, nullptr, Handler);
		}

		wprintf(L"[ + ] %hs -> %p\n", Name, Interface);
	};

	#define Pointer_Name(Interface) &Interface, (char*)#Interface + 10

	Create_Interface(Pointer_Name(Interface_Commentator), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Get_Priorities), nullptr, (void*)Get_Priorities);

	Create_Interface(Pointer_Name(Interface_Set_Priority), (char*)"1 0", (void*)Set_Priority);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Memory_Tolerance), (char*)"0", (void*)Bruteforce_Reset_Memory_Tolerance);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Tolerance), (char*)"0", (void*)Bruteforce_Reset_Tolerance);

	Create_Interface(Pointer_Name(Interface_Bruteforce), (char*)"1", (void*)Bruteforce_Reset);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Angles), (char*)"0, -60, 60", (void*)Bruteforce_Set_Angles);

	Bruteforce_Set_Angles((Interface_Structure*)((unsigned __int32)&Interface_Bruteforce_Angles + 24));

	Create_Interface(Pointer_Name(Interface_Bruteforce_Relative), (char*)"0", (void*)Bruteforce_Reset);

	Create_Interface(Pointer_Name(Interface_Bruteforce_Perpendicular), (char*)"2", (void*)Bruteforce_Reset);

	Create_Interface(Pointer_Name(Interface_Target_On_Simulation), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_High_Jump), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Alternative), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_Minimum_Choked_Commands), (char*)"2", nullptr);

	Create_Interface(Pointer_Name(Interface_Maximum_Choked_Commands), (char*)"14", nullptr);

	Create_Interface(Pointer_Name(Interface_Aim_Intersection), (char*)"0", nullptr);

	Create_Interface(Pointer_Name(Interface_Aim_Heights), (char*)"0.5, 0.7, 0.9", (void*)Aim_Set_Heights);

	Aim_Set_Heights((Interface_Structure*)((unsigned __int32)&Interface_Aim_Heights + 24));

	Create_Interface(Pointer_Name(Interface_Angle_X), (char*)"540", nullptr);

	Create_Interface(Pointer_Name(Interface_Animated_Angle_Y), (char*)"135", nullptr);

	Create_Interface(Pointer_Name(Interface_Angle_Y), (char*)"-45", nullptr);

	Create_Interface(Pointer_Name(Interface_Body_Update), (char*)"1", nullptr);

	Create_Interface(Pointer_Name(Interface_Body_Angle_Y), (char*)"180", nullptr);

	Create_Interface(Pointer_Name(Interface_Uber_Alles_Scale), (char*)"16", nullptr);

	Create_Interface(Pointer_Name(Interface_Uber_Alles_Speed), (char*)"192", nullptr);

	Create_Interface(Pointer_Name(Interface_sv_showhitboxes), (char*)"-1", nullptr);
}