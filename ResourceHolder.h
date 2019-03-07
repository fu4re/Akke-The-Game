#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map> //��������� �� STL, ������� ������ �������� ����� � �������������� ��������
#include <string> //������
#include <memory> //������ � �������
#include <stdexcept> //����� �� ���������� ��������� ������
#include <cassert> //�� �� ��������� ������ assert

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename); //�������� �� ����� � �������� �����

	template <typename Parameter>
	void load(Identifier, const std::string& filename, const Parameter& secondParam); //�������� � ������������ ���������� (�� �����)

	Resource& get(Identifier id);				//�������� ����
	const Resource& get(Identifier id) const;

private:
	void insertResource(Identifier id, std::unique_ptr<Resource> resource); //������� �������� (unique_ptr - ���������� ����������� ��� ������ ������ � ������(����� ���������))

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap; //Identifier - ��� ����� ����(id), � unique_ptr - ��� �������� � ���������� mResourceMap

#include "/GameDev/Akke The Game/Akke The Game/Utilities/ResourceHolder.inl"
};
#endif // !RESOURCEHOLDER_H


