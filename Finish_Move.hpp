void* Original_Finish_Move_Caller;

void __thiscall Redirected_Finish_Move(void* Unknown_Parameter_1, void* Player, void* Unknown_Parameter_2, void* Move_Data)
{
	float X = *(float*)((unsigned __int32)Move_Data + 92);

	if (X > 180.f)
	{
		X -= 360.f;
	}

	*(float*)((unsigned __int32)Move_Data + 92) = std::clamp(X, -90.f, 90.f);

	(decltype(&Redirected_Finish_Move)(Original_Finish_Move_Caller))(Unknown_Parameter_1, Player, Unknown_Parameter_2, Move_Data);
}