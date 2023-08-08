#pragma once
#include "sbResource.h"

namespace sb
{
	class Resources
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& name)
		{
			auto iter = mResources.find(name);
			if (iter == mResources.end())
				return nullptr;

			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& name, const std::wstring& path)
		{
			T* resource = Resources::Find<T>(name);

			if (resource != nullptr)
				return resource;

			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				MessageBox(nullptr, L"Resource Load Failed!", L"Error", MB_OK);
				delete resource;
				return nullptr;
			}

			resource->SetName(name);
			resource->SetPath(path);
			mResources.insert(std::make_pair(name, resource));

			return resource;
		}

		template <typename T>
		static void Insert(const std::wstring& name, T* resource)
		{
			resource->SetName(name);
			mResources.insert(std::make_pair(name, resource));
		}

		static void Release()
		{
			for (auto iter : mResources)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}

	private:

		static std::map<std::wstring, Resource*> mResources;
	};
}

