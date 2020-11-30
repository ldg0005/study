	try
	{
		m_pInternal = new NEWCLASS;
	}
	catch(const std::exception& e)
	{
		std::wstring wstr;
		std::string str(e.what());

		wstr.assign(str.begin(), str.end());

		OutputDebugStringW(L"NEWCLASS : ");
		OutputDebugStringW(wstr.c_str());
	}
