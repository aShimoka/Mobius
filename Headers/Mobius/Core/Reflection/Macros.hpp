
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Macros.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppMacros
#define _ProjectMobius_hppMacros

#define MOBJECT_HEADER_PROTOTYPE(CLASS, PARENT_CLASS) \
public: \
    class Prototype : public ::Mobius::Object::Prototype { \
    public: \
        typedef ::CLASS Reflected; \
        typedef ::PARENT_CLASS ReflectedParent; \
        static const ::Mobius::WeakPointer<const Prototype> instance(); \
        virtual const char * getClassName() const override { return # CLASS; } \
        virtual ::Mobius::Object::Reference makeEmptyObject() const override { return new ::CLASS(); } \
        virtual const ::Mobius::WeakPointer<const ::Mobius::PrototypeBase> getParent() const override { return ReflectedParent::Prototype::instance(); } \
    };

#define MOBJECT_HEADER_ABSTRACT_PROTOTYPE(CLASS, PARENT_CLASS) \
public: \
    class Prototype : public ::Mobius::Object::Prototype { \
    public: \
        typedef ::CLASS Reflected; \
        typedef ::PARENT_CLASS ReflectedParent; \
        static const ::Mobius::WeakPointer<const Prototype> instance(); \
        virtual const char * getClassName() const override { return # CLASS; } \
        virtual ::Mobius::Object::Reference makeEmptyObject() const override { assert(false); return nullptr; } \
        virtual const ::Mobius::WeakPointer<const ::Mobius::PrototypeBase> getParent() const override { return ReflectedParent::Prototype::instance(); } \
    };

#define MOBJECT_BASE_HEADER_PROTOTYPE() \
public: \
    class Prototype : public ::Mobius::PrototypeBase { \
    public: \
        typedef ::Mobius::Object Reflected; \
        static const ::Mobius::WeakPointer<const Prototype> instance(); \
        virtual const char * getClassName() const override { return "Mobius::Object"; } \
        virtual ::Mobius::Object::Reference makeEmptyObject() const { return new ::Mobius::Object(); } \
        virtual const ::Mobius::WeakPointer<const ::Mobius::PrototypeBase> getParent() const override { return WeakPointer<::Mobius::PrototypeBase>(); } \
    };

#define MOBJECT_HEADER_PROTOTYPE_ACCESSOR() \
public: \
    virtual const ::Mobius::WeakPointer<const ::Mobius::PrototypeBase> getPrototype() override;

#define MOBJECT_HEADER_PARENT_TYPE(PARENT_CLASS) \
public: \
    typedef PARENT_CLASS Parent;

#define MOBJECT_HEADER_REFERENCE_TYPE(CLASS) \
public: \
    typedef ::Mobius::StrongPointer<::CLASS> Reference; \
    typedef ::Mobius::WeakPointer<::CLASS> WeakReference;

#define MOBJECT_BASE_HEADER_REFERENCE_TYPE() \
public: \
    typedef ::Mobius::StrongPointer<::Mobius::Object> Reference; \
    typedef ::Mobius::WeakPointer<::Mobius::Object> WeakReference;

#define MOBJECT_HEADER_PROTOTYPE_INSTANCE() \
private: \
    static ::Mobius::WeakPointer<const Prototype> __staticPrototype;

#define MOBJECT_SOURCE_PROTOINSTANCE(CLASS) \
    const ::Mobius::WeakPointer<const CLASS::Prototype> CLASS::Prototype::instance() { \
        static ::Mobius::StrongPointer<const Prototype> instance = new Prototype(); \
        static ::Mobius::WeakPointer<const Prototype> instRef = ::Mobius::WeakPointer<const Prototype>(nullptr); \
        if (!instRef.isValid()) { \
            ::Mobius::Factory::registerPrototype(&instance, instance->getClassName()); \
            instRef = &instance; \
        } \
        return instRef; \
    }

#define MOBJECT_SOURCE_INSTANCEGETTER(CLASS) \
    const ::Mobius::WeakPointer<const ::Mobius::PrototypeBase> CLASS::getPrototype() { return ::CLASS::Prototype::instance(); }

#define MOBJECT_SOURCE_PROTOINSTINITER(CLASS) \
    ::Mobius::WeakPointer<const ::CLASS::Prototype> CLASS::__staticPrototype  = ::CLASS::Prototype::instance();

#define MOBJECT_BASE_BODY() \
    MOBJECT_BASE_HEADER_REFERENCE_TYPE() \
    MOBJECT_BASE_HEADER_PROTOTYPE() \
    MOBJECT_HEADER_PROTOTYPE_INSTANCE()

#define MOBJECT_ABSTRACT_BODY(CLASS, PARENT_CLASS) \
    MOBJECT_HEADER_REFERENCE_TYPE(CLASS) \
    MOBJECT_HEADER_ABSTRACT_PROTOTYPE(CLASS, PARENT_CLASS) \
    MOBJECT_HEADER_PROTOTYPE_ACCESSOR() \
    MOBJECT_HEADER_PROTOTYPE_INSTANCE() \
    MOBJECT_HEADER_PARENT_TYPE(PARENT_CLASS)

#define MOBJECT_BODY(CLASS, PARENT_CLASS) \
    MOBJECT_HEADER_REFERENCE_TYPE(CLASS) \
    MOBJECT_HEADER_PROTOTYPE(CLASS, PARENT_CLASS) \
    MOBJECT_HEADER_PROTOTYPE_ACCESSOR() \
    MOBJECT_HEADER_PROTOTYPE_INSTANCE() \
    MOBJECT_HEADER_PARENT_TYPE(PARENT_CLASS)

#define MOBJECT_DECLARE(CLASS) \
    MOBJECT_SOURCE_PROTOINSTANCE(CLASS) \
    MOBJECT_SOURCE_PROTOINSTINITER(CLASS) \
    MOBJECT_SOURCE_INSTANCEGETTER(CLASS)

#endif /* _ProjectMobius_hppMacros */
