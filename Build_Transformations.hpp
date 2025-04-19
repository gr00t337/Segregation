void* Original_Build_Transformations_Caller;

void __thiscall Redirected_Build_Transformations(void* Animating, __int32 Unknown_Parameter_1, __int32 Unknown_Parameter_2, __int32 Unknown_Parameter_3, __int32 Unknown_Parameter_4, __int32 Unknown_Parameter_5, __int32 Unknown_Parameter_6) 
{
	void* Previous_Bone_Jiggle_Pointer = *(void**)((unsigned __int32)Animating + 2356);

	*(void**)((unsigned __int32)Animating + 2356) = nullptr;

	(decltype(&Redirected_Build_Transformations)(Original_Build_Transformations_Caller))(Animating, Unknown_Parameter_1, Unknown_Parameter_2, Unknown_Parameter_3, Unknown_Parameter_4, Unknown_Parameter_5, Unknown_Parameter_6);

	*(void**)((unsigned __int32)Animating + 2356) = Previous_Bone_Jiggle_Pointer;
}