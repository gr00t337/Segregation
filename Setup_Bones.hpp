void* Original_Setup_Bones_Caller;

__int8 __thiscall Redirected_Setup_Bones(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time)
{
	if (*(void**)Entity == (void*)((unsigned __int32)Client_Module + 5515204))
	{
		*(float*)((unsigned __int32)Entity + 840) = 0.f;

		*(float*)((unsigned __int32)Entity + 844) = Players_Data[*(__int32*)((unsigned __int32)Entity + 88)].Animation_Angle;

		*(float*)((unsigned __int32)Entity + 848) = 0.f;

		if (*(void**)((unsigned __int32)Engine_Module + 5302872) == Bones)
		{
			*(__int32*)((unsigned __int32)Entity + 1608) = *(__int32*)((unsigned __int32)Client_Module + 6841616) - 1;

			*(__int32*)((unsigned __int32)Entity + 2348) = -8388609;
		}
	}

	return (decltype(&Redirected_Setup_Bones)(Original_Setup_Bones_Caller))(Entity, Bones, Maximum_Bones, Mask, Current_Time);
}