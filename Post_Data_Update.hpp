static float Local_Networked_Origin[3];

void* Original_Post_Data_Update_Caller;

void __thiscall Redirected_Post_Data_Update(void* Entity, void* Unknown_Parameter)
{
	Player_Data_Structure* Player_Data = &Players_Data[*(__int32*)((unsigned __int32)Entity + 84)];

	float* Origin = (float*)((unsigned __int32)Entity + 1040);

	float* Previous_Origin = (float*)((unsigned __int32)Entity + 824);

	if (*(float*)((unsigned __int32)Entity + 108) != *(float*)((unsigned __int32)Entity + 112))
	{
		Player_Data->Simulated = 1;

		if (Interface_Target_On_Simulation.Get_Integer() == 2)
		{
			if (__builtin_powf(Origin[0] - Previous_Origin[0], 2.f) + __builtin_powf(Origin[1] - Previous_Origin[1], 2.f) + __builtin_powf(Origin[2] - Previous_Origin[2], 2.f) > 4096.f)
			{
				Player_Data->Simulated = 0;
			}
		}
	}

	if (Interface_Bruteforce.Get_Integer() * (Interface_Bruteforce_Relative.Get_Integer() ^ 1) == 1)
	{
		if (Player_Data->Priority != -2)
		{
			if ((*(float*)((unsigned __int32)Entity + 108) != *(float*)((unsigned __int32)Entity + 112)) + (*(float*)((unsigned __int32)Entity + 40264) != Player_Data->Networked_Angle) + __builtin_memcmp(Origin, Previous_Origin, sizeof(float[3])) != 0)
			{
				float* Target_Origin = (float*)((unsigned __int32)Entity + 1040);

				float Direction[2] =
				{
					Target_Origin[0] - Local_Networked_Origin[0],

					Target_Origin[1] - Local_Networked_Origin[1]
				};

				*(float*)((unsigned __int32)Entity + 40264) = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f;
			}
		}
	}

	Player_Data->Networked_Angle = *(float*)((unsigned __int32)Entity + 40264);

	(decltype(&Redirected_Post_Data_Update)(Original_Post_Data_Update_Caller))(Entity, Unknown_Parameter);
}