#pragma once
#include "sbEntity.h"

namespace sb
{
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

		virtual HRESULT Load(const std::wstring& path) = 0;

		std::wstring& GethPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }


	private:
		std::wstring mPath;
	};

}
