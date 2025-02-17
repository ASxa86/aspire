#include <aspire/WriteFileQML.h>

#include <aspire/FactoryComponent.h>
#include <private/qqmlmetatype_p.h>
#include <fstream>
#include <set>

using aspire::FactoryComponent;

namespace
{
	auto WriteProperties(QObject& x, std::string& tabs, std::ofstream& ofs) -> void
	{
		const auto* metaObject = x.metaObject();

		if(metaObject == nullptr)
		{
			return;
		}

		tabs.push_back('\t');

		std::set<std::string> enumCache;

		for(auto i = 0; i < metaObject->enumeratorCount(); i++)
		{
			auto metaEnum = metaObject->enumerator(i);
			enumCache.insert(metaEnum.name());
		}

		for(auto i = 0; i < metaObject->propertyCount(); i++)
		{
			const auto property = metaObject->property(i);
			const auto variant = property.read(&x);
			std::string value;

			if(property.isEnumType() == true)
			{
				auto metaEnum = property.enumerator();

				if(enumCache.find(metaEnum.name()) != std::end(enumCache))
				{
					value += FactoryComponent::Instance()->findQmlName(metaEnum.enclosingMetaObject());

					if(metaEnum.isScoped() == true)
					{
						value += ".";
						value += metaEnum.name();
					}
				}
				else
				{
					value += metaEnum.enclosingMetaObject()->className();
				}

				value += ".";
				value += metaEnum.valueToKey(variant.toInt());
			}
			else if(property.userType() == QMetaType::QColor)
			{
				value = "\"" + variant.toString().toStdString() + "\"";
			}
			else
			{
				value = variant.toString().toStdString();
			}

			if(std::empty(value) == true)
			{
				continue;
			}

			ofs << tabs << property.name() << ": " << value << "\n";
		}

		tabs.pop_back();
	}

	auto WriteObject(QObject& x, std::string& tabs, std::ofstream& ofs) -> void
	{
		const auto elementName = FactoryComponent::Instance()->findQmlName(x.metaObject());

		if(std::empty(elementName) == true)
		{
			return;
		}

		ofs << tabs << elementName << " {\n";

		WriteProperties(x, tabs, ofs);

		if(std::empty(x.children()) == false)
		{
			ofs << "\n";
		}

		tabs.push_back('\t');

		for(auto* child : x.children())
		{
			WriteObject(*child, tabs, ofs);
		}

		tabs.pop_back();

		ofs << tabs << "}\n";
	}
}

auto aspire::WriteFileQML(QObject* x, const std::filesystem::path& file) -> void
{
	if(x == nullptr)
	{
		return;
	}

	std::ofstream ofs{file};

	if(ofs.is_open() == false)
	{
		return;
	}

	ofs << "import QtQuick\n";
	ofs << "\n";

	std::string tabs;
	WriteObject(*x, tabs, ofs);

	ofs << "\n";
}
