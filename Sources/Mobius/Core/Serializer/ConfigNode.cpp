/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file ConfigHandler.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 03/05/2019.
 */

#include <Mobius/Core/Serializer/ConfigNode.hpp>
#include <Mobius/Core/Reflection/Factory.hpp>
#include <TinyXML/TinyXML2.h>

MOBJECT_DECLARE(Mobius::ConfigNode)
MOBJECT_DECLARE(Mobius::ConfigHelpers::FlagList)

namespace Mobius {

ConfigNode::ConfigNode() :
    _text(), _attrMap(AttributesMap::create()), _childMap(ChildrenMap::create())
{}

ConfigNode::~ConfigNode() {
    _attrMap->clear(); _childMap->clear();
}

std::string ConfigNode::getAttribute(const std::string name) {
    // Return the element.
    return _attrMap->find(name)->second;
}

template <>
float ConfigNode::getAttribute<float>(const std::string name) {
    float out;
    tinyxml2::XMLUtil::ToFloat(getAttribute(name).c_str(), &out);
    return out;
}

template <>
void ConfigNode::getAttribute<float>(const std::string name, float * out) {
    if (hasAttribute(name)) tinyxml2::XMLUtil::ToFloat(getAttribute(name).c_str(), out);
}

template <>
void ConfigNode::getAttribute<std::string>(const std::string name, std::string * out) {
    if (hasAttribute(name)) *out = getAttribute(name);
}

template <>
void ConfigNode::getAttribute<unsigned int>(const std::string name, unsigned int * out) {
    if (hasAttribute(name)) *out = tinyxml2::XMLUtil::ToUnsigned(getAttribute(name).c_str(), out);
}


bool ConfigNode::hasAttribute(std::string name) {
    // Return wether or not the attribute exists.
    return (_attrMap->find(name) != _attrMap->end());
}

ConfigNode::ChildrenMapIterator ConfigNode::getChildrenIterator(bool end) {
    return end ? _childMap->end() : _childMap->begin();
}

const ConfigNode::ChildrenMapIterator ConfigNode::getChildrenIterator(bool end) const {
    return end ? _childMap->end() : _childMap->begin();
}

ConfigNode::AttributesMapIterator ConfigNode::getAttributesIterator(bool end) {
    return end ? _attrMap->end() : _attrMap->begin();
}

const ConfigNode::AttributesMapIterator ConfigNode::getAttributesIterator(bool end) const {
    return end ? _attrMap->end() : _attrMap->begin();
}

const std::vector<ConfigNode::WeakReference> ConfigNode::getChildElementsByName(const std::string name) {
    // Create the out vector.
    std::vector<ConfigNode::WeakReference> out = std::vector<ConfigNode::WeakReference>();
    
    // Loop through all the children.
    for (ChildrenMapIterator it = getChildrenIterator(); it != getChildrenIterator(true); it++) {
        // Compare the name.
        if ((*it)->getName() == name) {
            // Add it to the list.
            out.push_back((*it));
        }
    }
    
    // Return the list.
    return out;
}

const ConfigNode::WeakReference ConfigNode::getChildElementByName(const std::string name) {
    // Get all the children with that name.
    std::vector<ConfigNode::WeakReference> children = getChildElementsByName(name);
    
    // If the length is at least one.
    if (children.size() > 0) {
        // Return the first element.
        return children[0];
    } else {
        return nullptr;
    }
}

std::string ConfigNode::getText() const {
    return _text;
}

std::string ConfigNode::getName() const {
    return _name;
}

void ConfigNode::addAttribute(const std::string name, const std::string value) {
    // Set the attribute.
    _attrMap->insert(std::make_pair(name, value));
}

void ConfigNode::setText(const std::string text) {
    _text = text;
}

void ConfigNode::setName(const std::string name) {
    _name = name;
}

void ConfigNode::addChild(ConfigNode::Reference child) {
    _childMap->push_back(child);
}

ConfigHelpers::FlagList::FlagList() :
    _flags(FlagMap::create())
{}

ConfigHelpers::FlagList::~FlagList() {
    _flags->clear();
}

ConfigHelpers::FlagList::FlagMapIterator ConfigHelpers::FlagList::getFlagIterator(bool end) {
    return end ? _flags->end() : _flags->begin();
}

const ConfigHelpers::FlagList::FlagMapIterator ConfigHelpers::FlagList::getFlagIterator(bool end) const {
    return end ? _flags->end() : _flags->begin();
}

void ConfigHelpers::FlagList::addChild(ConfigNode::Reference child) {
    _flags->push_back(child->getName());
}

}
