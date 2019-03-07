#ifndef RESOURCEHOLDER_H
#define RESOURCEHOLDER_H

#include <map> //контейнер из STL, который хранит значение ключа и сопоставленное значение
#include <string> //строка
#include <memory> //работа с пам€тью
#include <stdexcept> //часть из библиотеки обработки ошибок
#include <cassert> //та же обработка ошибок assert

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void load(Identifier id, const std::string& filename); //загрузка по ключу и названию файла

	template <typename Parameter>
	void load(Identifier, const std::string& filename, const Parameter& secondParam); //загрузка с определенным параметром (не точно)

	Resource& get(Identifier id);				//ѕолучить ключ
	const Resource& get(Identifier id) const;

private:
	void insertResource(Identifier id, std::unique_ptr<Resource> resource); //вставка текстуры (unique_ptr - управление указател€ми дл€ сборки мусора в пам€ти(также указатели))

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap; //Identifier - тот самый ключ(id), а unique_ptr - его значение в переменной mResourceMap

#include "/GameDev/Akke The Game/Akke The Game/Utilities/ResourceHolder.inl"
};
#endif // !RESOURCEHOLDER_H


