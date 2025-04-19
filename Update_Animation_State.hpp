float Update_Animation_Angles[2];

void* Original_Update_Animation_State_Caller;

void __thiscall Redirected_Update_Animation_State(void* Animation_State, float Yaw, float Pitch, float Unknown_Parameter)
{
	if (*(void**)((unsigned __int32)Animation_State + 96) == *(void**)((unsigned __int32)Client_Module + 7170160))
	{
		Pitch = Update_Animation_Angles[0];

		Yaw = Update_Animation_Angles[1];
	}

	(decltype(&Redirected_Update_Animation_State)(Original_Update_Animation_State_Caller))(Animation_State, Yaw, Pitch, Unknown_Parameter);
}