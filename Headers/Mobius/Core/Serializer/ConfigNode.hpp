
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file ConfigHandler.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppConfigNode
#define _ProjectMobius_hppConfigNode

#include <Mobius/Core/Memory/StrongPointer.hpp>
#include <Mobius/Core/Reflection/Object.hpp>

#include <map>
#include <vector>
#include <string>

namespace Mobius {

// Forward declaration of the configuration manager class.
class ConfigManager;


/**
 * Single configuration handle object abstract class.
 * Used by the {@see ConfigurationManager} to handle configuration file.
 * This base object handles the deserialization of xml elements.
 */
class ConfigNode : public Object {
    MOBJECT_BODY(Mobius::ConfigNode, Mobius::Object)
    
    // Type alias for the children getter.
    typedef std::vector<ConfigNode::WeakReference> ChildrenList;
    // Type alias for the attributes list.
    typedef StrongPointer<std::map<std::string, std::string>> AttributesMap;
    // Type alias for the attributes iterator.
    typedef std::map<std::string, std::string>::iterator AttributesMapIterator;
    // Type alias for the children list.
    typedef StrongPointer<std::vector<ConfigNode::Reference>> ChildrenMap;
    // Type alias for the children list iterator.
    typedef std::vector<ConfigNode::Reference>::iterator ChildrenMapIterator;
    
    /** Allow the ConfigManager class to access this object's private members. */
    friend class ConfigManager;
    
    // ---  Methods ---
        // -- Public Methods --
            /**
             * Class constructor.
             */
            ConfigNode();
    
            /**
             * Class destructor.
             */
            virtual ~ConfigNode();
    
            /**
             * Attributes accessor.
             * Returns the value of the requested attribute.
             */
            std::string getAttribute(const std::string name);
    
            /**
             * Template attribute getter.
             * Returns the value of the requested attribute.
             */
            template <typename T>
            T getAttribute(const std::string name);
    
            /**
             * Template attribute getter.
             * Returns the value of the requested attribute in the given out value.
             */
            template <typename T>
            void getAttribute(const std::string name, T * out);
    
            /**
             * Checks wether or not the given attribute exists.
             */
            bool hasAttribute(std::string name);
    
            /**
             * Returns the children element iterator.
             */
            ChildrenMapIterator getChildrenIterator(bool end = false);
    
            /**
             * Returns a constant child iterator.
             */
            const ChildrenMapIterator getChildrenIterator(bool end = false) const;
    
            /**
             * Returns the attributes iterator.
             */
            AttributesMapIterator getAttributesIterator(bool end = false);
    
            /**
             * Returns a constant attributes iterator.
             */
            const AttributesMapIterator getAttributesIterator(bool end = false) const;
    
            /**
             * Returns a list containing all the children element with the given name.
             *
             * @param name The name of the child elements to get.
             * @return The list of children elements.
             */
            const ChildrenList getChildElementsByName(const std::string name);
    
            /**
             * Returns a single children element with the given name.
             *
             * @param name The name of the child elements to get.
             * @return The first child element with that name.
             */
            const ConfigNode::WeakReference getChildElementByName(const std::string name);
    
            /** Returns the text in the node. */
            std::string getText() const;
            /** Returns the name of the node. */
            std::string getName() const;
        // -- Protected Methods --
        protected:
            /**
             * Adds an attribute to the configuration node.
             *
             * @param name The name of the added attribute.
             * @param value The value
             */
            virtual void addAttribute(const std::string name, const std::string value);
    
            /**
             * Defines the text contents of the Node.
             *
             * @param text The text contents of the node.
             */
            virtual void setText(const std::string text);
    
            /**
             * Defines the name of the Node.
             *
             * @param name The name of the node.
             */
            virtual void setName(const std::string name);
    
            /**
             * Add a new child to this configuration node.
             *
             * @param child The child to be added into the config node.
             */
            virtual void addChild(ConfigNode::Reference child);
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
            /** List of all the attributes of the object. */
            AttributesMap _attrMap;
    
            /** Text contents of the object. */
            std::string _text;
    
            /** Name of the node. */
            std::string _name;
    
            /** List of children for the object. */
            ChildrenMap _childMap;
    // --- /Attributes ---
};

/**
 * List of helper classes that will simplify the handling of config files.
 * They can easily be overriden and configured by the user.
 */
namespace ConfigHelpers {
    class FlagList : public ConfigNode {
        MOBJECT_BODY(Mobius::ConfigHelpers::FlagList, Mobius::ConfigNode)
        
        // Type alias for the flag list.
        typedef StrongPointer<std::vector<std::string>> FlagMap;
        // Type alias for the children list iterator.
        typedef std::vector<std::string>::iterator FlagMapIterator;
        
        // ---  Methods ---
            // -- Public Methods --
            public:
                /**
                 * Class constructor.
                 */
                FlagList();
                
                /**
                 * Class destructor.
                 */
                virtual ~FlagList();
        
                /**
                 * Returns an iterator to the flags in the list.
                 */
                FlagMapIterator getFlagIterator(bool end = false);
        
                /**
                 * Const variant of the flag iterator getter.
                 */
                const FlagMapIterator getFlagIterator(bool end = false) const;
        
            // -- Protected Methods --
            protected:
                /**
                 * Override the AddChild method.
                 * Treats each child as a flag.
                 */
                virtual void addChild(ConfigNode::Reference child) override;
        // --- /Methods ---
        
        // ---  Attributes ---
            // -- Private Attributes --
                /** List of all the flags. */
                FlagMap _flags;
    };
};

}

#endif /* _ProjectMobius_hppConfigNode */
