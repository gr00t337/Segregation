void* Original_Precache_Caller;

void __thiscall Redirected_Precache(void* Material)
{
	using Get_Group_Type = char*(__thiscall**)(void* Material);

	if (*(unsigned __int16*)(*Get_Group_Type(*(unsigned __int32*)Material + 4))(Material) == 'oW')
	{
		using Alpha_Modulate_Type = void(__thiscall**)(void* Material, float Alpha);

		(*Alpha_Modulate_Type(*(unsigned __int32*)Material + 108))(Material, 0.25f);

		using Color_Modulate_Type = void(__thiscall**)(void* Material, float Red, float Green, float Blue);

		(*Color_Modulate_Type(*(unsigned __int32*)Material + 112))(Material, 1.f, 0.5f, 0.5f);
	}

	(decltype(&Redirected_Precache)(Original_Precache_Caller))(Material);
}