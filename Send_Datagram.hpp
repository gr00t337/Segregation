void* Original_Send_Datagram_Caller;

__int32 __thiscall Redirected_Send_Datagram(void* Network_Channel, void* Unknown_Parameter)
{
	__int32 Sequence_Number = (decltype(&Redirected_Send_Datagram)(Original_Send_Datagram_Caller))(Network_Channel, Unknown_Parameter);

	if (__builtin_return_address(0) == (void*)((unsigned __int32)Engine_Module + 2026548))
	{
		Sequence_Number = Sequences[Sequence_Number % 90] = *(__int32*)((unsigned __int32)Engine_Module + 5678668) + *(__int32*)((unsigned __int32)Engine_Module + 5678672) + 1;
	}

	return Sequence_Number;
}