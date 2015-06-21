/* 
 * File:   ResourceHolder.h
 * Author: dorian
 *
 * Created on 12 de diciembre de 2014, 22:30
 */

#ifndef RESOURCEHOLDER_H
#define	RESOURCEHOLDER_H

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

/**
 * Gestor de recursos
 */
template <typename Identifier, typename Resource>
class ResourceHolder {
public:
    /**
     * Carga un recurso
     * @param id identificador usado para el recurso
     * @param filename ruta del recurso a cargar
     */
    void load(Identifier id, const std::string& filename);

    /**
     * Carga un recurso con parámetros extra
     * @param id identificador usado para el recurso
     * @param filename ruta del recurso a cargar
     * @param secondParam parámetro extra para la carga del fichero
     */
    template <typename Parameter>
    void load(Identifier id, const std::string& filename, const Parameter& secondParam);

    /**
     * Devuelve el recurso dado el identificador
     * @param id identificador
     * @return el recurso dado
     */
    Resource& get(Identifier id);
    /**
     * Devuelve el recurso dado el identificador
     * @param id identificador
     * @return el recurso dado
     */
    const Resource& get(Identifier id) const;


private:
    void insertResource(Identifier id, Resource* resource);


private:
    std::map<Identifier, Resource*> mResourceMap;
};



/**
 * Implementación de la clase
 * 
 */


template <typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const std::string& filename) {
    auto found = mResourceMap.find(id);
	if(found != mResourceMap.end()){
            return;
        }
    
	// Create and load resource
	Resource* resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Identifier, typename Resource>
template <typename Parameter>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const std::string& filename, const Parameter& secondParam) {
	// Create and load resource
	Resource* resource(new Resource());
	if (!resource->loadFromFile(filename, secondParam))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
	insertResource(id, std::move(resource));
}

template <typename Identifier, typename Resource>
Resource& ResourceHolder<Identifier, Resource>::get(Identifier id) {
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Identifier, typename Resource>
const Resource& ResourceHolder<Identifier, Resource>::get(Identifier id) const {
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());

	return *found->second;
}

template <typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::insertResource(Identifier id, Resource* resource) {
	// Insert and check success
	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second);
}

#endif	/* RESOURCEHOLDER_H */

